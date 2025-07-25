#include <stdio.h>

#include "lcd_display.h"
#include "touch_i2c.h"
#include "ui.h"

void app_main(void)
{
    i2c_dev_init();
    init_lcd();
    ui_init(NULL);
}
