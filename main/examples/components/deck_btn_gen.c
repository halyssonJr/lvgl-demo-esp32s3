/**
 * @file deck_btn_gen.c
 * @description Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/
#include "deck_btn_gen.h"
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

lv_obj_t * deck_btn_create(lv_obj_t * parent, void * button_image, const char * button_text, lv_color_t text_color, lv_color_t bg_color, int32_t image_size, const char * text_font, int32_t text_x_offset, int32_t text_y_offset)
{
    LV_TRACE_OBJ_CREATE("begin");


    lv_obj_t * lv_button_0 = lv_button_create(parent);
    lv_obj_set_height(lv_button_0, 140);
    lv_obj_set_width(lv_button_0, 140);
    lv_obj_set_style_radius(lv_button_0, 24, 0);
    lv_obj_set_style_shadow_opa(lv_button_0, 0, 0);
    lv_obj_set_style_bg_color(lv_button_0, bg_color, 0);
    lv_obj_set_style_border_width(lv_button_0, 0, 0);
    lv_obj_set_style_pad_all(lv_button_0, 16, 0);
    lv_obj_set_style_flex_flow(lv_button_0, LV_FLEX_FLOW_COLUMN, 0);
    lv_obj_set_style_flex_main_place(lv_button_0, LV_FLEX_ALIGN_SPACE_EVENLY, 0);
    lv_obj_set_style_flex_cross_place(lv_button_0, LV_FLEX_ALIGN_CENTER, 0);

    lv_obj_t * lv_obj_0 = lv_obj_create(lv_button_0);
    lv_obj_set_width(lv_obj_0, image_size);
    lv_obj_set_height(lv_obj_0, image_size);
    lv_obj_set_style_bg_opa(lv_obj_0, 0, 0);
    lv_obj_set_style_border_width(lv_obj_0, 0, 0);
    lv_obj_set_style_pad_all(lv_obj_0, 0, 0);
    lv_obj_set_flag(lv_obj_0, LV_OBJ_FLAG_SCROLLABLE, false);
    lv_obj_set_align(lv_obj_0, LV_ALIGN_CENTER);

    lv_obj_t * lv_image_0 = lv_image_create(lv_obj_0);
    lv_image_set_src(lv_image_0, button_image);
    lv_obj_set_align(lv_image_0, LV_ALIGN_CENTER);



    lv_obj_t * lv_label_0 = lv_label_create(lv_button_0);
    lv_label_set_text(lv_label_0, button_text);
    lv_obj_set_align(lv_label_0, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_x(lv_label_0, text_x_offset);
    lv_obj_set_y(lv_label_0, text_y_offset);
    lv_obj_set_style_text_color(lv_label_0, text_color, 0);
    lv_obj_set_style_text_align(lv_label_0, LV_TEXT_ALIGN_CENTER, 0);



    LV_TRACE_OBJ_CREATE("finished");

    lv_obj_set_name(lv_button_0, "deck_btn_#");

    return lv_button_0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/