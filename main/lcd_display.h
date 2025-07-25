#ifndef LCD_H
#define LCD_H

#include "esp_check.h"
#include "esp_err.h"
#include "driver/gpio.h"
#include "esp_lcd_panel_rgb.h"
#include "esp_lcd_touch_gt911.h"

#define LCD_BK_LIGHT_ON_LEVEL 1
#define LCD_BK_LIGHT_OFF_LEVEL (!LCD_BK_LIGHT_ON_LEVEL)
#define LCD_GPIO_BK_LIGHT       GPIO_NUM_2
#define LCD_GPIO_DISP GPIO_NUM_NC
// #define LCD_7_INCH

#ifdef LCD_7_INCH

#define LCD_GPIO_HSYNC          GPIO_NUM_39
#define LCD_GPIO_VSYNC          GPIO_NUM_40
#define LCD_GPIO_DE             GPIO_NUM_41
#define LCD_GPIO_PCLK           GPIO_NUM_42

#define LCD_H_RES 800
#define LCD_V_RES 480

#define LCD_GPIO_DATA() { \
    GPIO_NUM_15,                 \
    GPIO_NUM_7,                  \
    GPIO_NUM_6,                  \
    GPIO_NUM_5,                  \
    GPIO_NUM_4,                  \
    GPIO_NUM_9,                  \
    GPIO_NUM_46,                 \
    GPIO_NUM_3,                  \
    GPIO_NUM_8,                  \
    GPIO_NUM_16,                 \
    GPIO_NUM_1,                  \
    GPIO_NUM_14,                 \
    GPIO_NUM_21,                 \
    GPIO_NUM_47,                 \
    GPIO_NUM_48,                 \
    GPIO_NUM_45,                 \
}

#define LCD_PANEL_TIMING()         \
    (esp_lcd_rgb_timing_t)             \
    {                                  \
        .pclk_hz = 16000000,           \
        .h_res = LCD_H_RES,        \
        .v_res = LCD_V_RES,        \
        .hsync_pulse_width = 30,       \
        .hsync_back_porch = 16,        \
        .hsync_front_porch = 20,       \
        .vsync_pulse_width = 13,       \
        .vsync_back_porch = 10,        \
        .vsync_front_porch = 22,       \
        .flags.pclk_active_neg = true, \
    }
#else

#define TOUCH_H_RES_MIN 0
#define TOUCH_H_RES_MAX 477
#define TOUCH_V_RES_MIN 0
#define TOUCH_V_RES_MAX 269

#define LCD_GPIO_HSYNC          GPIO_NUM_39
#define LCD_GPIO_VSYNC          GPIO_NUM_41
#define LCD_GPIO_DE             GPIO_NUM_40
#define LCD_GPIO_PCLK           GPIO_NUM_42

#define LCD_GPIO_DATA() { \
    GPIO_NUM_8,                 \
    GPIO_NUM_3,                  \
    GPIO_NUM_46,                  \
    GPIO_NUM_9,                  \
    GPIO_NUM_1,                  \
    GPIO_NUM_5,                  \
    GPIO_NUM_6,                 \
    GPIO_NUM_7,                  \
    GPIO_NUM_15,                  \
    GPIO_NUM_16,                 \
    GPIO_NUM_4,                  \
    GPIO_NUM_45,                 \
    GPIO_NUM_48,                 \
    GPIO_NUM_47,                 \
    GPIO_NUM_21,                 \
    GPIO_NUM_14,                 \
}

#define LCD_H_RES 800
#define LCD_V_RES 480

#define LCD_PANEL_TIMING()              \
    (esp_lcd_rgb_timing_t)              \
    {                                   \
        .pclk_hz = 18000000,             \
        .h_res = LCD_H_RES,             \
        .v_res = LCD_V_RES,             \
        .hsync_pulse_width = 30,        \
        .hsync_back_porch = 16,         \
        .hsync_front_porch = 20,        \
        .vsync_pulse_width = 13,        \
        .vsync_back_porch = 10,         \
        .vsync_front_porch = 22,        \
        .flags.pclk_active_neg = true,  \
    }

#endif

#define TOUCH_GPIO_SCL GPIO_NUM_20
#define TOUCH_GPIO_SDA GPIO_NUM_19
#define TOUCH_GPIO_INT GPIO_NUM_NC
#define TOUCH_GPIO_RST GPIO_NUM_38
typedef enum 
{
    LCD_SCREEN_CONFIG = 1 << 0,
    LCD_SCREEN_VENDING = 1 << 1,
    LCD_SCREEN_CONFIG_DELETE = 1 << 2,
}lcd_screen_e;

esp_err_t init_lcd(void);
esp_err_t lcd_set_event(lcd_screen_e screen);
#endif