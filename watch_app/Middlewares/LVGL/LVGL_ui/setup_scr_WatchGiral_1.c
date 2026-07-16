/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"



void setup_scr_WatchGiral_1(lv_ui *ui)
{
    //Write codes WatchGiral_1
    ui->WatchGiral_1 = lv_obj_create(NULL);
    lv_obj_set_size(ui->WatchGiral_1, 240, 280);
    lv_obj_set_scrollbar_mode(ui->WatchGiral_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for WatchGiral_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->WatchGiral_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->WatchGiral_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->WatchGiral_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_1_label_1
    ui->WatchGiral_1_label_1 = lv_label_create(ui->WatchGiral_1);
    lv_label_set_text(ui->WatchGiral_1_label_1, "ETERNLCHIP");
    lv_label_set_long_mode(ui->WatchGiral_1_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->WatchGiral_1_label_1, 37, 19);
    lv_obj_set_size(ui->WatchGiral_1_label_1, 170, 23);

    //Write style for WatchGiral_1_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->WatchGiral_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->WatchGiral_1_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->WatchGiral_1_label_1, &lv_customer_font_interttf_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->WatchGiral_1_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->WatchGiral_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->WatchGiral_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->WatchGiral_1_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->WatchGiral_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_1_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_1_arc_1
    ui->WatchGiral_1_arc_1 = lv_arc_create(ui->WatchGiral_1);
    lv_arc_set_mode(ui->WatchGiral_1_arc_1, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->WatchGiral_1_arc_1, 0, 100);
    lv_arc_set_bg_angles(ui->WatchGiral_1_arc_1, 135, 45);
    lv_arc_set_value(ui->WatchGiral_1_arc_1, 100);
    lv_arc_set_rotation(ui->WatchGiral_1_arc_1, 240);
    lv_obj_set_pos(ui->WatchGiral_1_arc_1, 24, 66);
    lv_obj_set_size(ui->WatchGiral_1_arc_1, 36, 36);

    //Write style for WatchGiral_1_arc_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->WatchGiral_1_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->WatchGiral_1_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->WatchGiral_1_arc_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->WatchGiral_1_arc_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->WatchGiral_1_arc_1, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_1_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_1_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_1_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_1_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_1_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_1_arc_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for WatchGiral_1_arc_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->WatchGiral_1_arc_1, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->WatchGiral_1_arc_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->WatchGiral_1_arc_1, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for WatchGiral_1_arc_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->WatchGiral_1_arc_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->WatchGiral_1_arc_1, 5, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes WatchGiral_1_arc_2
    ui->WatchGiral_1_arc_2 = lv_arc_create(ui->WatchGiral_1);
    lv_arc_set_mode(ui->WatchGiral_1_arc_2, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->WatchGiral_1_arc_2, 0, 100);
    lv_arc_set_bg_angles(ui->WatchGiral_1_arc_2, 135, 45);
    lv_arc_set_value(ui->WatchGiral_1_arc_2, 100);
    lv_arc_set_rotation(ui->WatchGiral_1_arc_2, 240);
    lv_obj_set_pos(ui->WatchGiral_1_arc_2, 24, 119);
    lv_obj_set_size(ui->WatchGiral_1_arc_2, 36, 36);

    //Write style for WatchGiral_1_arc_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->WatchGiral_1_arc_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->WatchGiral_1_arc_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->WatchGiral_1_arc_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->WatchGiral_1_arc_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->WatchGiral_1_arc_2, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_1_arc_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_1_arc_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_1_arc_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_1_arc_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_1_arc_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_1_arc_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for WatchGiral_1_arc_2, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->WatchGiral_1_arc_2, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->WatchGiral_1_arc_2, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->WatchGiral_1_arc_2, lv_color_hex(0xff003b), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for WatchGiral_1_arc_2, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->WatchGiral_1_arc_2, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->WatchGiral_1_arc_2, 5, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes WatchGiral_1_arc_3
    ui->WatchGiral_1_arc_3 = lv_arc_create(ui->WatchGiral_1);
    lv_arc_set_mode(ui->WatchGiral_1_arc_3, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->WatchGiral_1_arc_3, 0, 100);
    lv_arc_set_bg_angles(ui->WatchGiral_1_arc_3, 135, 45);
    lv_arc_set_value(ui->WatchGiral_1_arc_3, 100);
    lv_arc_set_rotation(ui->WatchGiral_1_arc_3, 240);
    lv_obj_set_pos(ui->WatchGiral_1_arc_3, 24, 177);
    lv_obj_set_size(ui->WatchGiral_1_arc_3, 36, 36);

    //Write style for WatchGiral_1_arc_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->WatchGiral_1_arc_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->WatchGiral_1_arc_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->WatchGiral_1_arc_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->WatchGiral_1_arc_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->WatchGiral_1_arc_3, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_1_arc_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_1_arc_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_1_arc_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_1_arc_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_1_arc_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_1_arc_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for WatchGiral_1_arc_3, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->WatchGiral_1_arc_3, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->WatchGiral_1_arc_3, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->WatchGiral_1_arc_3, lv_color_hex(0xff7300), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for WatchGiral_1_arc_3, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->WatchGiral_1_arc_3, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->WatchGiral_1_arc_3, 5, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes WatchGiral_1_arc_4
    ui->WatchGiral_1_arc_4 = lv_arc_create(ui->WatchGiral_1);
    lv_arc_set_mode(ui->WatchGiral_1_arc_4, LV_ARC_MODE_NORMAL);
    lv_arc_set_range(ui->WatchGiral_1_arc_4, 0, 100);
    lv_arc_set_bg_angles(ui->WatchGiral_1_arc_4, 135, 45);
    lv_arc_set_value(ui->WatchGiral_1_arc_4, 100);
    lv_arc_set_rotation(ui->WatchGiral_1_arc_4, 240);
    lv_obj_set_pos(ui->WatchGiral_1_arc_4, 24, 233);
    lv_obj_set_size(ui->WatchGiral_1_arc_4, 36, 36);

    //Write style for WatchGiral_1_arc_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->WatchGiral_1_arc_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->WatchGiral_1_arc_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_width(ui->WatchGiral_1_arc_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->WatchGiral_1_arc_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->WatchGiral_1_arc_4, lv_color_hex(0xe6e6e6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_1_arc_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_1_arc_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_1_arc_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_1_arc_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_1_arc_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_1_arc_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for WatchGiral_1_arc_4, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_arc_width(ui->WatchGiral_1_arc_4, 2, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_opa(ui->WatchGiral_1_arc_4, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_arc_color(ui->WatchGiral_1_arc_4, lv_color_hex(0x44ff00), LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for WatchGiral_1_arc_4, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->WatchGiral_1_arc_4, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(ui->WatchGiral_1_arc_4, 5, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes WatchGiral_1_img_1
    ui->WatchGiral_1_img_1 = lv_img_create(ui->WatchGiral_1);
    lv_obj_add_flag(ui->WatchGiral_1_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->WatchGiral_1_img_1, &_heart16x16_alpha_16x16);
    lv_img_set_pivot(ui->WatchGiral_1_img_1, 50,50);
    lv_img_set_angle(ui->WatchGiral_1_img_1, 0);
    lv_obj_set_pos(ui->WatchGiral_1_img_1, 51, 119);
    lv_obj_set_size(ui->WatchGiral_1_img_1, 16, 16);


    //Write style for WatchGiral_1_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->WatchGiral_1_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->WatchGiral_1_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_1_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->WatchGiral_1_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_1_img_2
    ui->WatchGiral_1_img_2 = lv_img_create(ui->WatchGiral_1);
    lv_obj_add_flag(ui->WatchGiral_1_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->WatchGiral_1_img_2, &_wather16x16_alpha_16x16);
    lv_img_set_pivot(ui->WatchGiral_1_img_2, 50,50);
    lv_img_set_angle(ui->WatchGiral_1_img_2, 0);
    lv_obj_set_pos(ui->WatchGiral_1_img_2, 51, 66);
    lv_obj_set_size(ui->WatchGiral_1_img_2, 16, 16);

    //Write style for WatchGiral_1_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->WatchGiral_1_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->WatchGiral_1_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_1_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->WatchGiral_1_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_1_img_3
    ui->WatchGiral_1_img_3 = lv_img_create(ui->WatchGiral_1);
    lv_obj_add_flag(ui->WatchGiral_1_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->WatchGiral_1_img_3, &_foot16x16_alpha_16x16);
    lv_img_set_pivot(ui->WatchGiral_1_img_3, 50,50);
    lv_img_set_angle(ui->WatchGiral_1_img_3, 0);
    lv_obj_set_pos(ui->WatchGiral_1_img_3, 51, 233);
    lv_obj_set_size(ui->WatchGiral_1_img_3, 16, 16);

    //Write style for WatchGiral_1_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->WatchGiral_1_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->WatchGiral_1_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_1_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->WatchGiral_1_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_1_img_4
    ui->WatchGiral_1_img_4 = lv_img_create(ui->WatchGiral_1);
    lv_obj_add_flag(ui->WatchGiral_1_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->WatchGiral_1_img_4, &_KLL16x16_alpha_16x16);
    lv_img_set_pivot(ui->WatchGiral_1_img_4, 50,50);
    lv_img_set_angle(ui->WatchGiral_1_img_4, 0);
    lv_obj_set_pos(ui->WatchGiral_1_img_4, 51, 177);
    lv_obj_set_size(ui->WatchGiral_1_img_4, 16, 16);

    //Write style for WatchGiral_1_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->WatchGiral_1_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->WatchGiral_1_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_1_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->WatchGiral_1_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_1_label_2
    ui->WatchGiral_1_label_2 = lv_label_create(ui->WatchGiral_1);
    lv_label_set_text(ui->WatchGiral_1_label_2, "24");
    lv_label_set_long_mode(ui->WatchGiral_1_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->WatchGiral_1_label_2, 29, 82);
    lv_obj_set_size(ui->WatchGiral_1_label_2, 20, 11);

    //Write style for WatchGiral_1_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->WatchGiral_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->WatchGiral_1_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->WatchGiral_1_label_2, &lv_customer_font_interttf_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->WatchGiral_1_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->WatchGiral_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->WatchGiral_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->WatchGiral_1_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->WatchGiral_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_1_img_5
    ui->WatchGiral_1_img_5 = lv_img_create(ui->WatchGiral_1);
    lv_obj_add_flag(ui->WatchGiral_1_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->WatchGiral_1_img_5, &_sheshidu_alpha_10x10);
    lv_img_set_pivot(ui->WatchGiral_1_img_5, 50,50);
    lv_img_set_angle(ui->WatchGiral_1_img_5, 0);
    lv_obj_set_pos(ui->WatchGiral_1_img_5, 43, 77);
    lv_obj_set_size(ui->WatchGiral_1_img_5, 10, 10);

    //Write style for WatchGiral_1_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->WatchGiral_1_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->WatchGiral_1_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_1_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->WatchGiral_1_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_1_label_3
    ui->WatchGiral_1_label_3 = lv_label_create(ui->WatchGiral_1);
    lv_label_set_text(ui->WatchGiral_1_label_3, "72");
    lv_label_set_long_mode(ui->WatchGiral_1_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->WatchGiral_1_label_3, 33, 132);
    lv_obj_set_size(ui->WatchGiral_1_label_3, 18, 10);

    //Write style for WatchGiral_1_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->WatchGiral_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->WatchGiral_1_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->WatchGiral_1_label_3, &lv_customer_font_interttf_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->WatchGiral_1_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->WatchGiral_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->WatchGiral_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->WatchGiral_1_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->WatchGiral_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_1_label_4
    ui->WatchGiral_1_label_4 = lv_label_create(ui->WatchGiral_1);
    lv_label_set_text(ui->WatchGiral_1_label_4, "304");
    lv_label_set_long_mode(ui->WatchGiral_1_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->WatchGiral_1_label_4, 29, 190);
    lv_obj_set_size(ui->WatchGiral_1_label_4, 22, 10);

    //Write style for WatchGiral_1_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->WatchGiral_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->WatchGiral_1_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->WatchGiral_1_label_4, &lv_customer_font_interttf_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->WatchGiral_1_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->WatchGiral_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->WatchGiral_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->WatchGiral_1_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->WatchGiral_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_1_label_5
    ui->WatchGiral_1_label_5 = lv_label_create(ui->WatchGiral_1);
    lv_label_set_text(ui->WatchGiral_1_label_5, "9046");
    lv_label_set_long_mode(ui->WatchGiral_1_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->WatchGiral_1_label_5, 21, 246);
    lv_obj_set_size(ui->WatchGiral_1_label_5, 37, 10);

    //Write style for WatchGiral_1_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->WatchGiral_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->WatchGiral_1_label_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->WatchGiral_1_label_5, &lv_customer_font_interttf_10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->WatchGiral_1_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->WatchGiral_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->WatchGiral_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->WatchGiral_1_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->WatchGiral_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_1_label_6
    ui->WatchGiral_1_label_6 = lv_label_create(ui->WatchGiral_1);
    lv_label_set_text(ui->WatchGiral_1_label_6, "09");
    lv_label_set_long_mode(ui->WatchGiral_1_label_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->WatchGiral_1_label_6, 94, 66);
    lv_obj_set_size(ui->WatchGiral_1_label_6, 116, 79);

    //Write style for WatchGiral_1_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->WatchGiral_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->WatchGiral_1_label_6, lv_color_hex(0xff0050), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->WatchGiral_1_label_6, &lv_customer_font_interttf_82, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->WatchGiral_1_label_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->WatchGiral_1_label_6, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->WatchGiral_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->WatchGiral_1_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->WatchGiral_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_1_label_7
    ui->WatchGiral_1_label_7 = lv_label_create(ui->WatchGiral_1);
    lv_label_set_text(ui->WatchGiral_1_label_7, "28");
    lv_label_set_long_mode(ui->WatchGiral_1_label_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->WatchGiral_1_label_7, 94, 149);
    lv_obj_set_size(ui->WatchGiral_1_label_7, 116, 79);

    //Write style for WatchGiral_1_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->WatchGiral_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->WatchGiral_1_label_7, lv_color_hex(0xc2ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->WatchGiral_1_label_7, &lv_customer_font_interttf_82, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->WatchGiral_1_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->WatchGiral_1_label_7, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->WatchGiral_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->WatchGiral_1_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->WatchGiral_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_1_label_8
    ui->WatchGiral_1_label_8 = lv_label_create(ui->WatchGiral_1);
    lv_label_set_text(ui->WatchGiral_1_label_8, "PM");
    lv_label_set_long_mode(ui->WatchGiral_1_label_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->WatchGiral_1_label_8, 84, 249);
    lv_obj_set_size(ui->WatchGiral_1_label_8, 41, 23);

    //Write style for WatchGiral_1_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->WatchGiral_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->WatchGiral_1_label_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->WatchGiral_1_label_8, &lv_customer_font_interttf_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->WatchGiral_1_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->WatchGiral_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->WatchGiral_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->WatchGiral_1_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->WatchGiral_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_1_label_9
    ui->WatchGiral_1_label_9 = lv_label_create(ui->WatchGiral_1);
    lv_label_set_text(ui->WatchGiral_1_label_9, "03/18");
    lv_label_set_long_mode(ui->WatchGiral_1_label_9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->WatchGiral_1_label_9, 131, 249);
    lv_obj_set_size(ui->WatchGiral_1_label_9, 75, 23);

    //Write style for WatchGiral_1_label_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->WatchGiral_1_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_1_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->WatchGiral_1_label_9, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->WatchGiral_1_label_9, &lv_customer_font_interttf_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->WatchGiral_1_label_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->WatchGiral_1_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->WatchGiral_1_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->WatchGiral_1_label_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->WatchGiral_1_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_1_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_1_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_1_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_1_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_1_label_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of WatchGiral_1.
    lv_obj_clear_flag(guider_ui.WatchGiral_1_arc_1,LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(guider_ui.WatchGiral_1_arc_2,LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(guider_ui.WatchGiral_1_arc_3,LV_OBJ_FLAG_CLICKABLE);
    lv_obj_clear_flag(guider_ui.WatchGiral_1_arc_4,LV_OBJ_FLAG_CLICKABLE);

    //Update current screen layout.
    lv_obj_update_layout(ui->WatchGiral_1);

    //Init events for screen.
    events_init_WatchGiral_1(ui);
}
