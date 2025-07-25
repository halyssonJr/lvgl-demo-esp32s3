

#ifdef __has_include

#if __has_include("lvgl.h")

#ifndef LV_LVGL_H_INCLUDE_SIMPLE

#define LV_LVGL_H_INCLUDE_SIMPLE

#endif

#endif

#endif

#if defined(LV_LVGL_H_INCLUDE_SIMPLE)

#include "lvgl.h"

#else

#include "lvgl/lvgl.h"

#endif

extern const lv_image_dsc_t game;
extern const lv_image_dsc_t media;
extern const lv_image_dsc_t power;
extern const lv_image_dsc_t work;
extern const lv_image_dsc_t settings;
extern const lv_image_dsc_t social;