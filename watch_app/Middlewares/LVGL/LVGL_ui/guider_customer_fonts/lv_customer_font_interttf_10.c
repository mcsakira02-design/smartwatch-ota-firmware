/*******************************************************************************
 * Size: 10 px
 * Bpp: 4
 * Opts: undefined
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef LV_CUSTOMER_FONT_INTERTTF_10
#define LV_CUSTOMER_FONT_INTERTTF_10 1
#endif

#if LV_CUSTOMER_FONT_INTERTTF_10

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0030 "0" */
    0x0, 0x9e, 0xb0, 0x9, 0xc4, 0xe7, 0x1f, 0x40,
    0xc9, 0x5f, 0x0, 0xd8, 0x8d, 0x0, 0xf5, 0x9b,
    0x4, 0xf1, 0x7e, 0x4c, 0x90, 0x1c, 0xfa, 0x0,

    /* U+0031 "1" */
    0x2, 0x8f, 0x80, 0x4b, 0xf5, 0x0, 0x4f, 0x20,
    0x7, 0xf0, 0x0, 0x9d, 0x0, 0xc, 0xb0, 0x24,
    0xfa, 0x3b, 0xff, 0xfc,

    /* U+0032 "2" */
    0x0, 0x4d, 0xfb, 0x0, 0xb, 0x66, 0xf5, 0x0,
    0x0, 0x1f, 0x50, 0x0, 0x8, 0xe0, 0x0, 0x4,
    0xf5, 0x0, 0x4, 0xf7, 0x0, 0x5, 0xfb, 0x44,
    0x1, 0xff, 0xff, 0xe0,

    /* U+0033 "3" */
    0x0, 0x5d, 0xfc, 0x20, 0x7, 0x65, 0xf7, 0x0,
    0x0, 0x6f, 0x30, 0x1, 0xff, 0x50, 0x0, 0x3,
    0xbe, 0x0, 0x0, 0x6, 0xf1, 0xc, 0x75, 0xdc,
    0x0, 0x8e, 0xfa, 0x10,

    /* U+0034 "4" */
    0x0, 0x0, 0xaf, 0x50, 0x0, 0x5e, 0xf3, 0x0,
    0x2f, 0x9f, 0x0, 0xc, 0x97, 0xe0, 0x7, 0xe0,
    0xab, 0x0, 0xff, 0xff, 0xf7, 0x2, 0x22, 0xf7,
    0x0, 0x0, 0x2f, 0x30,

    /* U+0035 "5" */
    0x0, 0x5f, 0xff, 0xa0, 0x8, 0xd4, 0x42, 0x0,
    0xc8, 0x0, 0x0, 0xf, 0xee, 0x90, 0x0, 0x53,
    0x9f, 0x20, 0x0, 0x5, 0xf2, 0xa, 0x65, 0xdc,
    0x0, 0x8e, 0xfa, 0x10,

    /* U+0036 "6" */
    0x0, 0x7e, 0xf7, 0x7, 0xe6, 0x75, 0xf, 0x50,
    0x0, 0x4f, 0x9e, 0xa0, 0x7f, 0x65, 0xf4, 0x8c,
    0x1, 0xf4, 0x6f, 0x49, 0xd0, 0xa, 0xfc, 0x10,

    /* U+0037 "7" */
    0xe, 0xff, 0xff, 0x0, 0x44, 0x5e, 0x80, 0x0,
    0x8, 0xb0, 0x0, 0x2, 0xf2, 0x0, 0x0, 0xab,
    0x0, 0x0, 0x1f, 0x50, 0x0, 0x5, 0xf1, 0x0,
    0x0, 0x9d, 0x0, 0x0,

    /* U+0038 "8" */
    0x1, 0xbf, 0xd2, 0xa, 0xc2, 0xd8, 0xd, 0x80,
    0xd5, 0x7, 0xfc, 0xa0, 0x1c, 0x8e, 0xc0, 0xa9,
    0x4, 0xf2, 0xcb, 0x19, 0xe0, 0x3d, 0xfc, 0x20,

    /* U+0039 "9" */
    0x2, 0xcf, 0xa0, 0xd, 0x94, 0xf6, 0x4f, 0x10,
    0xc8, 0x5f, 0x23, 0xe7, 0x1d, 0xfb, 0xf4, 0x0,
    0x15, 0xe0, 0x56, 0x6e, 0x60, 0x8e, 0xe6, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 94, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 44, .adv_w = 94, .box_w = 7, .box_h = 8, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 94, .box_w = 7, .box_h = 8, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 94, .box_w = 7, .box_h = 8, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 94, .box_w = 7, .box_h = 8, .ofs_x = -1, .ofs_y = 0},
    {.bitmap_index = 156, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 180, .adv_w = 94, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 94, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 48, .range_length = 10, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};



/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t lv_customer_font_interttf_10 = {
#else
lv_font_t lv_customer_font_interttf_10 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 10,          /*The maximum line height required by the font*/
    .base_line = 1,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
#if LV_VERSION_CHECK(8, 2, 0) || LVGL_VERSION_MAJOR >= 9
    .fallback = NULL,
#endif
    .user_data = NULL,
};



#endif /*#if LV_CUSTOMER_FONT_INTERTTF_10*/

