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




void setup_scr_top_lap(lv_ui *ui)
{
    //Write codes top_lap
    ui->top_lap = lv_obj_create(NULL);
    lv_obj_set_size(ui->top_lap, 240, 280);
    lv_obj_set_scrollbar_mode(ui->top_lap, LV_SCROLLBAR_MODE_OFF);

    //Write style for top_lap, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->top_lap, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->top_lap, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->top_lap, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes top_lap_slider_1
    ui->top_lap_slider_1 = lv_slider_create(ui->top_lap);
    lv_slider_set_range(ui->top_lap_slider_1, 0, 100);
    lv_slider_set_mode(ui->top_lap_slider_1, LV_SLIDER_MODE_NORMAL);
    lv_slider_set_value(ui->top_lap_slider_1, 50, LV_ANIM_OFF);
    lv_obj_set_pos(ui->top_lap_slider_1, 20, 220);
    lv_obj_set_size(ui->top_lap_slider_1, 199, 41);

    //Write style for top_lap_slider_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->top_lap_slider_1, 97, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->top_lap_slider_1, lv_color_hex(0xff9600), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->top_lap_slider_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->top_lap_slider_1, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui->top_lap_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->top_lap_slider_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for top_lap_slider_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->top_lap_slider_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->top_lap_slider_1, lv_color_hex(0xff6500), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->top_lap_slider_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->top_lap_slider_1, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

    //Write style for top_lap_slider_1, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->top_lap_slider_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->top_lap_slider_1, lv_color_hex(0xff6500), LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->top_lap_slider_1, LV_GRAD_DIR_NONE, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui->top_lap_slider_1, &_liangdu_40x40, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_opa(ui->top_lap_slider_1, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_recolor_opa(ui->top_lap_slider_1, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->top_lap_slider_1, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

    //Write codes top_lap_cont_1
    ui->top_lap_cont_1 = lv_obj_create(ui->top_lap);
    lv_obj_set_pos(ui->top_lap_cont_1, 37, 46);
    lv_obj_set_size(ui->top_lap_cont_1, 60, 60);
    lv_obj_set_scrollbar_mode(ui->top_lap_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for top_lap_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->top_lap_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->top_lap_cont_1, 30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->top_lap_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->top_lap_cont_1, lv_color_hex(0x525252), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->top_lap_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->top_lap_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->top_lap_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->top_lap_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->top_lap_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->top_lap_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes top_lap_img_1
    ui->top_lap_img_1 = lv_img_create(ui->top_lap_cont_1);
    lv_obj_add_flag(ui->top_lap_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->top_lap_img_1, &_BT32_alpha_32x32);
    lv_img_set_pivot(ui->top_lap_img_1, 50,50);
    lv_img_set_angle(ui->top_lap_img_1, 0);
    lv_obj_set_pos(ui->top_lap_img_1, 15, 15);
    lv_obj_set_size(ui->top_lap_img_1, 32, 32);

    //Write style for top_lap_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->top_lap_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->top_lap_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->top_lap_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->top_lap_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes top_lap_cont_2
    ui->top_lap_cont_2 = lv_obj_create(ui->top_lap);
    lv_obj_set_pos(ui->top_lap_cont_2, 138, 46);
    lv_obj_set_size(ui->top_lap_cont_2, 60, 60);
    lv_obj_set_scrollbar_mode(ui->top_lap_cont_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for top_lap_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->top_lap_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->top_lap_cont_2, 30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->top_lap_cont_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->top_lap_cont_2, lv_color_hex(0xff006c), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->top_lap_cont_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->top_lap_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->top_lap_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->top_lap_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->top_lap_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->top_lap_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes top_lap_img_2
    ui->top_lap_img_2 = lv_img_create(ui->top_lap_cont_2);
    lv_obj_add_flag(ui->top_lap_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->top_lap_img_2, &_location_alpha_32x32);
    lv_img_set_pivot(ui->top_lap_img_2, 50,50);
    lv_img_set_angle(ui->top_lap_img_2, 0);
    lv_obj_set_pos(ui->top_lap_img_2, 15, 15);
    lv_obj_set_size(ui->top_lap_img_2, 32, 32);

    //Write style for top_lap_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->top_lap_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->top_lap_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->top_lap_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->top_lap_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes top_lap_cont_3
    ui->top_lap_cont_3 = lv_obj_create(ui->top_lap);
    lv_obj_set_pos(ui->top_lap_cont_3, 37, 132);
    lv_obj_set_size(ui->top_lap_cont_3, 60, 60);
    lv_obj_set_scrollbar_mode(ui->top_lap_cont_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for top_lap_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->top_lap_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->top_lap_cont_3, 30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->top_lap_cont_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->top_lap_cont_3, lv_color_hex(0xc200ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->top_lap_cont_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->top_lap_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->top_lap_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->top_lap_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->top_lap_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->top_lap_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes top_lap_img_3
    ui->top_lap_img_3 = lv_img_create(ui->top_lap_cont_3);
    lv_obj_add_flag(ui->top_lap_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->top_lap_img_3, &_taiwan_alpha_32x32);
    lv_img_set_pivot(ui->top_lap_img_3, 50,50);
    lv_img_set_angle(ui->top_lap_img_3, 0);
    lv_obj_set_pos(ui->top_lap_img_3, 15, 15);
    lv_obj_set_size(ui->top_lap_img_3, 32, 32);

    //Write style for top_lap_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->top_lap_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->top_lap_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->top_lap_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->top_lap_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes top_lap_cont_4
    ui->top_lap_cont_4 = lv_obj_create(ui->top_lap);
    lv_obj_set_pos(ui->top_lap_cont_4, 138, 132);
    lv_obj_set_size(ui->top_lap_cont_4, 60, 60);
    lv_obj_set_scrollbar_mode(ui->top_lap_cont_4, LV_SCROLLBAR_MODE_OFF);

    //Write style for top_lap_cont_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->top_lap_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->top_lap_cont_4, 30, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->top_lap_cont_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->top_lap_cont_4, lv_color_hex(0xff6500), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->top_lap_cont_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->top_lap_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->top_lap_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->top_lap_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->top_lap_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->top_lap_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes top_lap_img_4
    ui->top_lap_img_4 = lv_img_create(ui->top_lap_cont_4);
    lv_obj_add_flag(ui->top_lap_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->top_lap_img_4, &_nfc_alpha_32x32);
    lv_img_set_pivot(ui->top_lap_img_4, 50,50);
    lv_img_set_angle(ui->top_lap_img_4, 0);
    lv_obj_set_pos(ui->top_lap_img_4, 15, 15);
    lv_obj_set_size(ui->top_lap_img_4, 32, 32);

    //Write style for top_lap_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->top_lap_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->top_lap_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->top_lap_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->top_lap_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes top_lap_label_1
    ui->top_lap_label_1 = lv_label_create(ui->top_lap);
    lv_label_set_text(ui->top_lap_label_1, "10.30AM");
    lv_label_set_long_mode(ui->top_lap_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->top_lap_label_1, 11, 17);
    lv_obj_set_size(ui->top_lap_label_1, 70, 17);

    //Write style for top_lap_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->top_lap_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->top_lap_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->top_lap_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->top_lap_label_1, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->top_lap_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->top_lap_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->top_lap_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->top_lap_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->top_lap_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->top_lap_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->top_lap_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->top_lap_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->top_lap_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->top_lap_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes top_lap_img_5
    ui->top_lap_img_5 = lv_img_create(ui->top_lap);
    lv_obj_add_flag(ui->top_lap_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->top_lap_img_5, &_power_hight_alpha_32x32);
    lv_img_set_pivot(ui->top_lap_img_5, 50,50);
    lv_img_set_angle(ui->top_lap_img_5, 0);
    lv_obj_set_pos(ui->top_lap_img_5, 183, 8);
    lv_obj_set_size(ui->top_lap_img_5, 32, 32);

    //Write style for top_lap_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->top_lap_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->top_lap_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->top_lap_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->top_lap_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of top_lap.


    //Update current screen layout.
    lv_obj_update_layout(ui->top_lap);

    //Init events for screen.
    events_init_top_lap(ui);
}
