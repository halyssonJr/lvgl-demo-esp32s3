/**
 * @file examples_gen.c
 */

/*********************
 *      INCLUDES
 *********************/
#include "examples_gen.h"

#if LV_USE_XML
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

/*----------------
 * Translations
 *----------------*/

/**********************
 *  GLOBAL VARIABLES
 **********************/

/*--------------------
 *  Permanent screens
 *-------------------*/

/*----------------
 * Global styles
 *----------------*/

/*----------------
 * Fonts
 *----------------*/


/*----------------
 * Images
 *----------------*/
const void * power_icon;
const void * settings_icon;
const void * social_icon;
const void * game_icon;
const void * media_icon;
const void * work_icon;

/*----------------
 * Subjects
 *----------------*/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void examples_init_gen(const char * asset_path)
{
    char buf[256];

    /*----------------
     * Global styles
     *----------------*/

    /*----------------
     * Fonts
     *----------------*/

    /*----------------
     * Images
     *----------------*/
    lv_snprintf(buf, 256, "%s%s", asset_path, "images/power.png");
    power_icon = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "images/settings.png");
    settings_icon = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "images/social.png");
    social_icon = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "images/game.png");
    game_icon = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "images/media.png");
    media_icon = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "images/work.png");
    work_icon = lv_strdup(buf);


    /*----------------
     * Subjects
     *----------------*/

    /*----------------
     * Translations
     *----------------*/


#if LV_USE_XML
    /*Register widgets*/

    /* Register fonts */

    /* Register subjects */

    /* Register callbacks */
    lv_xml_register_event_cb(NULL, "button_cb", button_cb);
#endif

    /* Register all the global assets so that they won't be created again when globals.xml is parsed.
     * While running in the editor skip this step to update the preview when the XML changes */
#if LV_USE_XML && !defined(LV_EDITOR_PREVIEW)

    /* Register images */
    lv_xml_register_image(NULL, "power_icon", power_icon);
    lv_xml_register_image(NULL, "settings_icon", settings_icon);
    lv_xml_register_image(NULL, "social_icon", social_icon);
    lv_xml_register_image(NULL, "game_icon", game_icon);
    lv_xml_register_image(NULL, "media_icon", media_icon);
    lv_xml_register_image(NULL, "work_icon", work_icon);
#endif

#if LV_USE_XML == 0
    /*--------------------
    *  Permanent screens
    *-------------------*/

    /*If XML is enabled it's assumed that the permanent screens are created
     *manaully from XML using lv_xml_create()*/

#endif
}

/* callbacks */
#if defined(LV_EDITOR_PREVIEW)
void __attribute__((weak)) button_cb(lv_event_t * e)
{
   LV_UNUSED(e);
   LV_LOG("button_cb was called\n");
}
#endif

/**********************
 *   STATIC FUNCTIONS
 **********************/