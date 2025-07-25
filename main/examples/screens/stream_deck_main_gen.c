/**
 * @file stream_deck_main_gen.c
 * @description Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/
#include "stream_deck_main_gen.h"
#include "ui.h"

/*********************
 *      DEFINES
 *********************/



/**********************
 *      TYPEDEFS
 **********************/

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * stream_deck_main_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");


    static bool style_inited = false;

    if (!style_inited) {

        style_inited = true;
    }

    lv_obj_t * lv_obj_0 = lv_obj_create(NULL);
    lv_obj_set_width(lv_obj_0, 800);
    lv_obj_set_height(lv_obj_0, 420);
    lv_obj_set_style_bg_color(lv_obj_0, lv_color_hex(0x1a1a1a), 0);
    lv_obj_set_style_border_width(lv_obj_0, 0, 0);
    lv_obj_set_style_pad_all(lv_obj_0, 0, 0);

    lv_obj_t * lv_obj_1 = lv_obj_create(lv_obj_0);
    lv_obj_set_width(lv_obj_1, 800);
    lv_obj_set_height(lv_obj_1, 420);
    lv_obj_set_style_bg_color(lv_obj_1, lv_color_hex(0x1a1a1a), 0);
    lv_obj_set_style_border_width(lv_obj_1, 0, 0);
    lv_obj_set_style_pad_all(lv_obj_1, 24, 0);
    lv_obj_set_flex_flow(lv_obj_1, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flag(lv_obj_1, LV_OBJ_FLAG_SCROLLABLE, false);

    lv_obj_t * lv_obj_2 = lv_obj_create(lv_obj_1);
    lv_obj_set_width(lv_obj_2, lv_pct(100));
    lv_obj_set_height(lv_obj_2, 80);
    lv_obj_set_style_bg_color(lv_obj_2, lv_color_hex(0x1a1a1a), 0);
    lv_obj_set_style_border_width(lv_obj_2, 0, 0);
    lv_obj_set_style_pad_all(lv_obj_2, 0, 0);

    lv_obj_t * lv_label_0 = lv_label_create(lv_obj_2);
    lv_label_set_text(lv_label_0, "Stream Deck LVGL");
    lv_obj_set_style_text_color(lv_label_0, lv_color_hex(0xffffff), 0);
    lv_obj_set_style_text_align(lv_label_0, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_set_align(lv_label_0, LV_ALIGN_CENTER);



    lv_obj_t * lv_obj_3 = lv_obj_create(lv_obj_1);
    lv_obj_set_width(lv_obj_3, lv_pct(100));
    lv_obj_set_height(lv_obj_3, 300);
    lv_obj_set_style_bg_color(lv_obj_3, lv_color_hex(0x1a1a1a), 0);
    lv_obj_set_style_border_width(lv_obj_3, 0, 0);
    lv_obj_set_style_pad_all(lv_obj_3, 0, 0);
    lv_obj_set_style_layout(lv_obj_3, LV_LAYOUT_FLEX, 0);
    lv_obj_set_flex_flow(lv_obj_3, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_style_flex_main_place(lv_obj_3, LV_FLEX_ALIGN_SPACE_EVENLY, 0);
    lv_obj_set_style_flex_cross_place(lv_obj_3, LV_FLEX_ALIGN_SPACE_EVENLY, 0);
    lv_obj_set_flag(lv_obj_3, LV_OBJ_FLAG_SCROLLABLE, false);

    lv_obj_t * contatiner_top = lv_obj_create(lv_obj_3);
    lv_obj_set_name(contatiner_top, "contatiner_top");
    lv_obj_set_width(contatiner_top, lv_pct(100));
    lv_obj_set_height(contatiner_top, 150);
    lv_obj_set_style_bg_color(contatiner_top, lv_color_hex(0x1a1a1a), 0);
    lv_obj_set_style_border_width(contatiner_top, 0, 0);
    lv_obj_set_style_pad_all(contatiner_top, 0, 0);
    lv_obj_set_flex_flow(contatiner_top, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_flex_main_place(contatiner_top, LV_FLEX_ALIGN_SPACE_EVENLY, 0);
    lv_obj_set_style_flex_cross_place(contatiner_top, LV_FLEX_ALIGN_SPACE_EVENLY, 0);
    lv_obj_set_flag(contatiner_top, LV_OBJ_FLAG_SCROLLABLE, false);

    lv_obj_t * deck_btn_0 = deck_btn_create(contatiner_top, power_icon, "Power", lv_color_hex(0xFFFFFF), lv_color_hex(0x4CAF50), 64, "lv_font_default_36", 0, 0);
    lv_obj_add_event_cb(deck_btn_0, button_cb, LV_EVENT_CLICKED, NULL);


    lv_obj_t * deck_btn_1 = deck_btn_create(contatiner_top, media_icon, "Media", lv_color_hex(0xFFFFFF), lv_color_hex(0x9C27B0), 64, "lv_font_default_36", 0, 0);
    lv_obj_add_event_cb(deck_btn_1, button_cb, LV_EVENT_CLICKED, NULL);


    lv_obj_t * deck_btn_2 = deck_btn_create(contatiner_top, game_icon, "Media", lv_color_hex(0xFFFFFF), lv_color_hex(0x00BCD4), 64, "lv_font_default_36", 0, 0);
    lv_obj_add_event_cb(deck_btn_2, button_cb, LV_EVENT_CLICKED, NULL);



    lv_obj_t * contatiner_bottom = lv_obj_create(lv_obj_3);
    lv_obj_set_name(contatiner_bottom, "contatiner_bottom");
    lv_obj_set_width(contatiner_bottom, lv_pct(100));
    lv_obj_set_height(contatiner_bottom, 150);
    lv_obj_set_style_bg_color(contatiner_bottom, lv_color_hex(0x1a1a1a), 0);
    lv_obj_set_style_border_width(contatiner_bottom, 0, 0);
    lv_obj_set_style_pad_all(contatiner_bottom, 0, 0);
    lv_obj_set_flex_flow(contatiner_bottom, LV_FLEX_FLOW_ROW);
    lv_obj_set_style_flex_main_place(contatiner_bottom, LV_FLEX_ALIGN_SPACE_EVENLY, 0);
    lv_obj_set_style_flex_cross_place(contatiner_bottom, LV_FLEX_ALIGN_SPACE_EVENLY, 0);
    lv_obj_set_flag(contatiner_bottom, LV_OBJ_FLAG_SCROLLABLE, false);

    lv_obj_t * deck_btn_3 = deck_btn_create(contatiner_bottom, social_icon, "Social", lv_color_hex(0xFFFFFF), lv_color_hex(0xFF5722), 64, "lv_font_default_36", 0, 0);
    lv_obj_add_event_cb(deck_btn_3, button_cb, LV_EVENT_CLICKED, NULL);


    lv_obj_t * deck_btn_4 = deck_btn_create(contatiner_bottom, work_icon, "Social", lv_color_hex(0xFFFFFF), lv_color_hex(0x2196F3), 64, "lv_font_default_36", 0, 0);
    lv_obj_add_event_cb(deck_btn_4, button_cb, LV_EVENT_CLICKED, NULL);


    lv_obj_t * deck_btn_5 = deck_btn_create(contatiner_bottom, settings_icon, "Settings", lv_color_hex(0xFFFFFF), lv_color_hex(0x607D8B), 64, "lv_font_default_36", 0, 0);
    lv_obj_add_event_cb(deck_btn_5, button_cb, LV_EVENT_CLICKED, NULL);






    LV_TRACE_OBJ_CREATE("finished");

    lv_obj_set_name(lv_obj_0, "stream_deck_main");

    return lv_obj_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/