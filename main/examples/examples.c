/**
 * @file examples.c
 */

/*********************
 *      INCLUDES
 *********************/
#include "examples.h"

#if LV_USE_XML == 0

#include "image_converted/image_converted.h"
#include "esp_log.h"

#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/
static lv_obj_t* stream_deck_home = NULL;
static const char *demo_tag = "DEMO";
    
/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void examples_init(const char * asset_path)
{
    
#if LV_USE_XML == 0
    ESP_LOGI(demo_tag,"Creating Stream Deck screen");

    work_icon = &work;
    game_icon = &game;
    power_icon = &power;
    social_icon = &social;
    media_icon  = &media;
    settings_icon = &settings;

    stream_deck_home = stream_deck_main_create();
    lv_screen_load(stream_deck_home);

#else
    examples_init_gen(asset_path);
#endif

}

#if LV_USE_XML == 0

void button_cb(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *deck_btn = lv_event_get_target(e);

    if (code == LV_EVENT_CLICKED)
    {
        lv_obj_t *btn_label = lv_obj_get_child(deck_btn, 1);
        ESP_LOGI(demo_tag,"Button Name : %s", lv_label_get_text(btn_label));
    }
}
#endif
/**********************
 *   STATIC FUNCTIONS
 **********************/
