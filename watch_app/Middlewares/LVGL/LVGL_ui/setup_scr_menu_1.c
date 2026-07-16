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




void setup_scr_menu_1(lv_ui *ui)
{
    //Write codes menu_1
    ui->menu_1 = lv_obj_create(NULL);
    lv_obj_set_size(ui->menu_1, 240, 280);
    lv_obj_set_scrollbar_mode(ui->menu_1, LV_SCROLLBAR_MODE_ON);

    //Write style for menu_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_cont_1
    ui->menu_1_cont_1 = lv_obj_create(ui->menu_1);
    lv_obj_set_pos(ui->menu_1_cont_1, 0, 0);
    lv_obj_set_size(ui->menu_1_cont_1, 240, 651);
    lv_obj_set_scrollbar_mode(ui->menu_1_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for menu_1_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_cont_1, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_1_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_cont_2
    ui->menu_1_cont_2 = lv_obj_create(ui->menu_1_cont_1);
    lv_obj_set_pos(ui->menu_1_cont_2, 0, 40);
    lv_obj_set_size(ui->menu_1_cont_2, 240, 70);
    lv_obj_set_scrollbar_mode(ui->menu_1_cont_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for menu_1_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_1_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_cont_2, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_1_cont_2, 97, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_1_cont_2, lv_color_hex(0x2e2e2e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_1_cont_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_1_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_1_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_1_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_1_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_1_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_img_1
    ui->menu_1_img_1 = lv_img_create(ui->menu_1_cont_2);
    lv_obj_add_flag(ui->menu_1_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menu_1_img_1, &_heart16x16_alpha_16x16);
    lv_img_set_pivot(ui->menu_1_img_1, 0,0);
    lv_img_set_angle(ui->menu_1_img_1, 0);
    lv_obj_set_pos(ui->menu_1_img_1, 30, 20);
    lv_obj_set_size(ui->menu_1_img_1, 16, 16);
    lv_img_set_zoom(ui->menu_1_img_1,512);

    //Write style for menu_1_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menu_1_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_1_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_1_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_label_2
    ui->menu_1_label_2 = lv_label_create(ui->menu_1_cont_2);
    lv_label_set_text(ui->menu_1_label_2, "Heart rate");
    lv_label_set_long_mode(ui->menu_1_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_1_label_2, 83, 24);
    lv_obj_set_size(ui->menu_1_label_2, 127, 20);

    //Write style for menu_1_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_1_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_1_label_2, &lv_customer_font_interttf_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_1_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_1_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_1_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_cont_3
    ui->menu_1_cont_3 = lv_obj_create(ui->menu_1_cont_1);
    lv_obj_set_pos(ui->menu_1_cont_3, 0, 130);
    lv_obj_set_size(ui->menu_1_cont_3, 240, 70);
    lv_obj_set_scrollbar_mode(ui->menu_1_cont_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for menu_1_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_1_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_cont_3, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_1_cont_3, 97, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_1_cont_3, lv_color_hex(0x2e2e2e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_1_cont_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_1_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_1_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_1_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_1_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_1_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_img_2
    ui->menu_1_img_2 = lv_img_create(ui->menu_1_cont_3);
    lv_obj_add_flag(ui->menu_1_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menu_1_img_2, &_location32x32_alpha_16x16);
    lv_img_set_pivot(ui->menu_1_img_2, 0,0);
    lv_img_set_angle(ui->menu_1_img_2, 0);
    lv_obj_set_pos(ui->menu_1_img_2, 30, 20);
    lv_obj_set_size(ui->menu_1_img_2, 16, 16);
    lv_img_set_zoom(ui->menu_1_img_2,512);

    //Write style for menu_1_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menu_1_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_1_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_1_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_label_3
    ui->menu_1_label_3 = lv_label_create(ui->menu_1_cont_3);
    lv_label_set_text(ui->menu_1_label_3, "Electronic fence");
    lv_label_set_long_mode(ui->menu_1_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_1_label_3, 86, 27);
    lv_obj_set_size(ui->menu_1_label_3, 127, 20);

    //Write style for menu_1_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_1_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_1_label_3, &lv_customer_font_interttf_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_1_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_1_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_1_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_cont_4
    ui->menu_1_cont_4 = lv_obj_create(ui->menu_1_cont_1);
    lv_obj_set_pos(ui->menu_1_cont_4, 0, 220);
    lv_obj_set_size(ui->menu_1_cont_4, 240, 70);
    lv_obj_set_scrollbar_mode(ui->menu_1_cont_4, LV_SCROLLBAR_MODE_OFF);

    //Write style for menu_1_cont_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_1_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_cont_4, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_1_cont_4, 97, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_1_cont_4, lv_color_hex(0x2e2e2e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_1_cont_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_1_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_1_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_1_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_1_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_1_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_img_3
    ui->menu_1_img_3 = lv_img_create(ui->menu_1_cont_4);
    lv_obj_add_flag(ui->menu_1_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menu_1_img_3, &_NFC32x32_alpha_32x32);
    lv_img_set_pivot(ui->menu_1_img_3, 50,50);
    lv_img_set_angle(ui->menu_1_img_3, 0);
    lv_obj_set_pos(ui->menu_1_img_3, 30, 20);
    lv_obj_set_size(ui->menu_1_img_3, 32, 32);

    //Write style for menu_1_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menu_1_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_1_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_1_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_label_4
    ui->menu_1_label_4 = lv_label_create(ui->menu_1_cont_4);
    lv_label_set_text(ui->menu_1_label_4, "NFC Card");
    lv_label_set_long_mode(ui->menu_1_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_1_label_4, 83, 24);
    lv_obj_set_size(ui->menu_1_label_4, 127, 20);

    //Write style for menu_1_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_1_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_1_label_4, &lv_customer_font_interttf_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_1_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_1_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_1_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_cont_5
    ui->menu_1_cont_5 = lv_obj_create(ui->menu_1_cont_1);
    lv_obj_set_pos(ui->menu_1_cont_5, 0, 310);
    lv_obj_set_size(ui->menu_1_cont_5, 240, 70);
    lv_obj_set_scrollbar_mode(ui->menu_1_cont_5, LV_SCROLLBAR_MODE_OFF);

    //Write style for menu_1_cont_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_1_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_cont_5, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_1_cont_5, 97, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_1_cont_5, lv_color_hex(0x2e2e2e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_1_cont_5, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_1_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_1_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_1_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_1_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_1_cont_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_img_4
    ui->menu_1_img_4 = lv_img_create(ui->menu_1_cont_5);
    lv_obj_add_flag(ui->menu_1_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menu_1_img_4, &_qrcode32x32_alpha_32x32);
    lv_img_set_pivot(ui->menu_1_img_4, 50,50);
    lv_img_set_angle(ui->menu_1_img_4, 0);
    lv_obj_set_pos(ui->menu_1_img_4, 30, 20);
    lv_obj_set_size(ui->menu_1_img_4, 32, 32);

    //Write style for menu_1_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menu_1_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_1_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_1_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_label_5
    ui->menu_1_label_5 = lv_label_create(ui->menu_1_cont_5);
    lv_label_set_text(ui->menu_1_label_5, "Qr Code");
    lv_label_set_long_mode(ui->menu_1_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_1_label_5, 83, 24);
    lv_obj_set_size(ui->menu_1_label_5, 127, 20);

    //Write style for menu_1_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_1_label_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_1_label_5, &lv_customer_font_interttf_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_1_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_1_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_1_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_cont_6
    ui->menu_1_cont_6 = lv_obj_create(ui->menu_1_cont_1);
    lv_obj_set_pos(ui->menu_1_cont_6, 0, 400);
    lv_obj_set_size(ui->menu_1_cont_6, 240, 70);
    lv_obj_set_scrollbar_mode(ui->menu_1_cont_6, LV_SCROLLBAR_MODE_OFF);

    //Write style for menu_1_cont_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_1_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_cont_6, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_1_cont_6, 97, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_1_cont_6, lv_color_hex(0x2e2e2e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_1_cont_6, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_1_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_1_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_1_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_1_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_1_cont_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_img_5
    ui->menu_1_img_5 = lv_img_create(ui->menu_1_cont_6);
    lv_obj_add_flag(ui->menu_1_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menu_1_img_5, &_syteam32x32_alpha_32x32);
    lv_img_set_pivot(ui->menu_1_img_5, 50,50);
    lv_img_set_angle(ui->menu_1_img_5, 0);
    lv_obj_set_pos(ui->menu_1_img_5, 30, 20);
    lv_obj_set_size(ui->menu_1_img_5, 32, 32);

    //Write style for menu_1_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menu_1_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_1_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_1_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_label_6
    ui->menu_1_label_6 = lv_label_create(ui->menu_1_cont_6);
    lv_label_set_text(ui->menu_1_label_6, "System Update");
    lv_label_set_long_mode(ui->menu_1_label_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_1_label_6, 83, 24);
    lv_obj_set_size(ui->menu_1_label_6, 127, 20);

    //Write style for menu_1_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_1_label_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_1_label_6, &lv_customer_font_interttf_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_1_label_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_1_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_1_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_cont_7
    ui->menu_1_cont_7 = lv_obj_create(ui->menu_1_cont_1);
    lv_obj_set_pos(ui->menu_1_cont_7, 0, 490);
    lv_obj_set_size(ui->menu_1_cont_7, 240, 70);
    lv_obj_set_scrollbar_mode(ui->menu_1_cont_7, LV_SCROLLBAR_MODE_OFF);

    //Write style for menu_1_cont_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_1_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_cont_7, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_1_cont_7, 97, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_1_cont_7, lv_color_hex(0x2e2e2e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_1_cont_7, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_1_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_1_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_1_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_1_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_1_cont_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_img_6
    ui->menu_1_img_6 = lv_img_create(ui->menu_1_cont_7);
    lv_obj_add_flag(ui->menu_1_img_6, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menu_1_img_6, &_wather16x16_alpha_16x16);
    lv_img_set_pivot(ui->menu_1_img_6, 0,0);
    lv_img_set_angle(ui->menu_1_img_6, 0);
    lv_obj_set_pos(ui->menu_1_img_6, 30, 20);
    lv_obj_set_size(ui->menu_1_img_6, 16, 16);
    lv_img_set_zoom(ui->menu_1_img_6,512);

    //Write style for menu_1_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menu_1_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_1_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_1_img_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_label_7
    ui->menu_1_label_7 = lv_label_create(ui->menu_1_cont_7);
    lv_label_set_text(ui->menu_1_label_7, "Weather");
    lv_label_set_long_mode(ui->menu_1_label_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_1_label_7, 83, 24);
    lv_obj_set_size(ui->menu_1_label_7, 127, 20);

    //Write style for menu_1_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_1_label_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_1_label_7, &lv_customer_font_interttf_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_1_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_1_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_1_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_cont_8
    ui->menu_1_cont_8 = lv_obj_create(ui->menu_1_cont_1);
    lv_obj_set_pos(ui->menu_1_cont_8, 0, 580);
    lv_obj_set_size(ui->menu_1_cont_8, 240, 70);
    lv_obj_set_scrollbar_mode(ui->menu_1_cont_8, LV_SCROLLBAR_MODE_OFF);

    //Write style for menu_1_cont_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_1_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_cont_8, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_1_cont_8, 97, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_1_cont_8, lv_color_hex(0x2e2e2e), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_1_cont_8, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_1_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_1_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_1_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_1_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_1_cont_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_img_7
    ui->menu_1_img_7 = lv_img_create(ui->menu_1_cont_8);
    lv_obj_add_flag(ui->menu_1_img_7, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menu_1_img_7, &_set32x32_alpha_32x32);
    lv_img_set_pivot(ui->menu_1_img_7, 50,50);
    lv_img_set_angle(ui->menu_1_img_7, 0);
    lv_obj_set_pos(ui->menu_1_img_7, 30, 20);
    lv_obj_set_size(ui->menu_1_img_7, 32, 32);

    //Write style for menu_1_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menu_1_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_1_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_1_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_label_8
    ui->menu_1_label_8 = lv_label_create(ui->menu_1_cont_8);
    lv_label_set_text(ui->menu_1_label_8, "Set");
    lv_label_set_long_mode(ui->menu_1_label_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_1_label_8, 83, 24);
    lv_obj_set_size(ui->menu_1_label_8, 127, 20);

    //Write style for menu_1_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_1_label_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_1_label_8, &lv_customer_font_interttf_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_1_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_1_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_1_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_1_btn_1
    ui->menu_1_btn_1 = lv_btn_create(ui->menu_1);
    ui->menu_1_btn_1_label = lv_label_create(ui->menu_1_btn_1);
    lv_label_set_text(ui->menu_1_btn_1_label, "< Home");
    lv_label_set_long_mode(ui->menu_1_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->menu_1_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->menu_1_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->menu_1_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->menu_1_btn_1, 7, 4);
    lv_obj_set_size(ui->menu_1_btn_1, 70, 21);

    //Write style for menu_1_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_1_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_1_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_1_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_1_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_1_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_1_btn_1, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_1_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_1_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of menu_1.
    static lv_style_t style_custom_scrollbar;
    lv_style_init(&style_custom_scrollbar);
    lv_style_set_width(&style_custom_scrollbar, 4);  // 垂直滚动条宽�?
    lv_style_set_max_height(&style_custom_scrollbar, 5); // 滑块最大高�?
    lv_style_set_min_height(&style_custom_scrollbar, 5); // 滑块最小高�?
    lv_obj_add_style(guider_ui.menu_1, &style_custom_scrollbar, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    lv_obj_set_scroll_dir(guider_ui.menu_1,LV_DIR_VER);

    //Update current screen layout.
    lv_obj_update_layout(ui->menu_1);

    //Init events for screen.
    events_init_menu_1(ui);
}
