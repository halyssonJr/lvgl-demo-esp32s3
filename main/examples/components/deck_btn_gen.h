/**
 * @file deck_btn_gen.h
 */

#ifndef DECK_BTN_H
#define DECK_BTN_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
    #include "lvgl.h"
#else
    #include "lvgl/lvgl.h"
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/


lv_obj_t * deck_btn_create(lv_obj_t * parent, void * button_image, const char * button_text, lv_color_t text_color, lv_color_t bg_color, int32_t image_size, const char * text_font, int32_t text_x_offset, int32_t text_y_offset);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*DECK_BTN_H*/