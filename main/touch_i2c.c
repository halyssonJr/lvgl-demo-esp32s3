#include "touch_i2c.h"
#include "esp_log.h"

#define I2C_MASTER_FREQ_HZ  400000
#define I2C_MASTER_TIMEOUT  50

#define I2C_MASTER_BUS          1
#define I2C_GPIO_SCL            GPIO_NUM_20
#define I2C_GPIO_SDA            GPIO_NUM_19
#define TAG_I2C "I2C DEV"
static bool i2c_is_init = false;

esp_err_t i2c_dev_init(void)
{
    i2c_config_t i2c_config = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_GPIO_SDA,
        .scl_io_num = I2C_GPIO_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };

    i2c_param_config(I2C_MASTER_BUS, &i2c_config);

    if (i2c_driver_install(I2C_MASTER_BUS, i2c_config.mode, 0, 0, 0) != ESP_OK)
    {
        ESP_LOGE(TAG_I2C, "Failed to instal I2C driver");
        return ESP_FAIL;
    }
    i2c_is_init = true;
    ESP_LOGI(TAG_I2C, "I2C driver install");
    return ESP_OK;
}