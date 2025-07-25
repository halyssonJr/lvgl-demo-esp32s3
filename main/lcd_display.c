#include "lcd_display.h"
#include "esp_lvgl_port.h"

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

#define LCD_LVGL_FULL_REFRESH           (0)
#define LCD_LVGL_DIRECT_MODE            (1)
#define LCD_LVGL_AVOID_TEAR             (1)
#define LCD_RGB_BOUNCE_BUFFER_MODE      (1)
#define LCD_DRAW_BUFF_DOUBLE            (0)
#define LCD_DRAW_BUFF_HEIGHT            (100)
#define LCD_RGB_BUFFER_NUMS             (2)
#define LCD_RGB_BOUNCE_BUFFER_HEIGHT    (10)

#define LVGL_PRIOR      4
#define LVGL_STATCK     8192
#define LVGL_TASK_SLEEP 500
#define LVGL_TIMER_MS   5

#define LCD_MANAGER_TASK_NAME "lcd"
#define LCD_MANAGER_TASK_PRIOR (4)
#define LCD_MANEGER_STACK_SIZE (1024 * 6)

#define LEDC_SET_DUTY(x)        (((1 << LEDC_DUTY_RES) * (x)) / 100)
#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (2)
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT
#define LEDC_DUTY               (4096) // Set duty to 50%. (2 ** 13) * 50% = 4096
#define LEDC_FREQUENCY          (4000)

#define LEDC_MAX_DUTY           (85)
#define LEDC_MIN_DUTY           (0)
    
static esp_lcd_panel_handle_t lcd_panel = NULL;
static esp_lcd_panel_io_handle_t touch_io_handle = NULL;
static esp_lcd_touch_handle_t touch_handle = NULL;

static lv_display_t *lvgl_disp = NULL;
static lv_indev_t *lvgl_touch_indev = NULL;

#define TAG "LCD"

#ifndef LCD_7_INCH

static uint16_t map(long x, long in_min, long in_max, long out_min, long out_max) 
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

static void touch_process_coordinates(esp_lcd_touch_handle_t tp, uint16_t *x, uint16_t *y, uint16_t *strength, uint8_t *point_num, uint8_t max_point_num)
{
  *x = map(*x, TOUCH_H_RES_MIN, TOUCH_H_RES_MAX, 0, LCD_H_RES);
  *y = map(*y, TOUCH_V_RES_MIN, TOUCH_V_RES_MAX, 0, LCD_V_RES);
} 
#endif

static esp_err_t lcd_panel_init(esp_lcd_panel_handle_t *handle)
{
    ESP_LOGI(TAG, "Initialize RGB panel");
    const esp_lcd_rgb_panel_config_t conf =
    {
        .clk_src = LCD_CLK_SRC_DEFAULT,
        .timings = LCD_PANEL_TIMING(),
        .data_width = 16,
        .num_fbs = LCD_RGB_BUFFER_NUMS,
        .bounce_buffer_size_px = LCD_H_RES * LCD_RGB_BOUNCE_BUFFER_HEIGHT,
        .hsync_gpio_num = LCD_GPIO_HSYNC,
        .vsync_gpio_num = LCD_GPIO_VSYNC,
        .de_gpio_num = LCD_GPIO_DE,
        .pclk_gpio_num = LCD_GPIO_PCLK,
        .disp_gpio_num = LCD_GPIO_DISP,
        .data_gpio_nums = LCD_GPIO_DATA(),
        .flags.fb_in_psram = 1,
    };

    esp_err_t err = esp_lcd_new_rgb_panel(&conf, handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "RGB init failed");
    }

    err = esp_lcd_panel_init(*handle);
    if (err != ESP_OK)
    {
        ESP_LOGE(TAG, "LCD init failed");
    }
    return err;
}

static esp_err_t lcd_lvgl_init(esp_lcd_panel_handle_t handle, esp_lcd_touch_handle_t tp,
                               lv_display_t **lv_disp, lv_indev_t **lv_touch_indev)
{
    const lvgl_port_cfg_t lvgl_cfg = {
        .task_priority = LVGL_PRIOR,
        .task_stack = LVGL_STATCK,
        .task_affinity = -1,
        .task_max_sleep_ms = LVGL_TASK_SLEEP,
        .timer_period_ms = LVGL_TIMER_MS
    };

    if (lvgl_port_init(&lvgl_cfg) != ESP_OK)
        ESP_LOGE(TAG, "LVGL port initialization failed");

    uint32_t buff_size = LCD_H_RES * LCD_V_RES;

    ESP_LOGD(TAG, "Add LCD screen");
    const lvgl_port_display_cfg_t disp_cfg = {
        .panel_handle = handle,
        .buffer_size = buff_size,
        .double_buffer = LCD_DRAW_BUFF_DOUBLE,
        .hres = LCD_H_RES,
        .vres = LCD_V_RES,
        .monochrome = false,
        .color_format = LV_COLOR_FORMAT_RGB565,
        .rotation = {
            .swap_xy = false,
            .mirror_x = false,
            .mirror_y = false,
        },
        .flags = {
            .buff_dma = false,
            .buff_spiram = false,
            .direct_mode = true,
            .swap_bytes = false,
        }
    };
    const lvgl_port_display_rgb_cfg_t rgb_cfg = {
        .flags = {
            .bb_mode = true,
            .avoid_tearing = true,
        }
    };
    *lv_disp = lvgl_port_add_disp_rgb(&disp_cfg, &rgb_cfg);

    const lvgl_port_touch_cfg_t touch_cfg = {
        .disp = *lv_disp,
        .handle = tp,
    };
    *lv_touch_indev = lvgl_port_add_touch(&touch_cfg);

    return ESP_OK;
}

static esp_err_t touch_init(esp_lcd_panel_io_handle_t *tp_io, esp_lcd_touch_handle_t *tp)
{
    if (!*tp_io)
    {
        ESP_LOGI(TAG, "creating touch panel io");
        esp_lcd_panel_io_i2c_config_t tp_io_cfg = ESP_LCD_TOUCH_IO_I2C_GT911_CONFIG();
        if (esp_lcd_new_panel_io_i2c((esp_lcd_i2c_bus_handle_t)1, &tp_io_cfg, tp_io) != ESP_OK)
        {
            ESP_LOGE(TAG, "Failed to crate touch panel io");
            return ESP_FAIL;
        }
    }

    const esp_lcd_touch_config_t tp_cfg = 
    {
        .x_max = LCD_H_RES,
        .y_max = LCD_V_RES,
        .rst_gpio_num = TOUCH_GPIO_RST,
        .int_gpio_num = TOUCH_GPIO_INT,
#ifndef LCD_7_INCH
        .process_coordinates = touch_process_coordinates,
#endif
    };

    return esp_lcd_touch_new_i2c_gt911(*tp_io, &tp_cfg, tp);
}

// static void click_create (lv_event_code_t *e)
// {

// }

void create_ui()
{
    lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
    // lv_obj_add_screen_create_event(lv_obj_0, LV_EVENT_CLICKED, click_create, LV_SCREEN_LOAD_ANIM_FADE_OUT, 500, 0)
}

esp_err_t init_lcd (void)
{
    esp_err_t ret = ESP_OK;
    ret = lcd_panel_init(&lcd_panel);
    if (ret != ESP_OK)
    {
        esp_lcd_panel_del(lcd_panel);
        return ret;
    }
    touch_init(&touch_io_handle, &touch_handle);
    ret = lcd_lvgl_init(lcd_panel, touch_handle, &lvgl_disp, &lvgl_touch_indev);
    if (ret != ESP_OK)
    {
        return ret;
    }

    const gpio_config_t bk_light = {
        .pin_bit_mask = (1 << LCD_GPIO_BK_LIGHT),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE,
    };
    ESP_ERROR_CHECK(gpio_config(&bk_light));
    gpio_set_level(LCD_GPIO_BK_LIGHT, LCD_BK_LIGHT_ON_LEVEL);

    return ret;
}
