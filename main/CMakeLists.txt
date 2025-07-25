
file(GLOB_RECURSE EXAMPLES_SRCS "examples/*.c")

find_path(LVGL_INCLUDE_DIR 
    NAMES lvgl.h
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}/managed_components/lvgl__lvgl/src
)

if(LVGL_INCLUDE_DIR)
    target_include_directories(${COMPONENT_LIB} PRIVATE ${LVGL_INCLUDE_DIR})
endif()

idf_component_register(SRCS "main.c"
                            "lcd_display.c"
                            "touch_i2c.c"
                            ${EXAMPLES_SRCS}
                    INCLUDE_DIRS "."
                    "examples"
                    REQUIRES esp_lcd lvgl lvgl__lvgl)


target_compile_definitions(${COMPONENT_LIB} PRIVATE
    LV_LVGL_H_INCLUDE_SIMPLE=1
)