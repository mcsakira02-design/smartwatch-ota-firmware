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




void setup_scr_NFCCard(lv_ui *ui)
{
    //Write codes NFCCard
    ui->NFCCard = lv_obj_create(NULL);
    lv_obj_set_size(ui->NFCCard, 240, 280);
    lv_obj_set_scrollbar_mode(ui->NFCCard, LV_SCROLLBAR_MODE_OFF);

    //Write style for NFCCard, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->NFCCard, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->NFCCard, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->NFCCard, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NFCCard_btn_1
    ui->NFCCard_btn_1 = lv_btn_create(ui->NFCCard);
    ui->NFCCard_btn_1_label = lv_label_create(ui->NFCCard_btn_1);
    lv_label_set_text(ui->NFCCard_btn_1_label, "< Menu");
    lv_label_set_long_mode(ui->NFCCard_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->NFCCard_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->NFCCard_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->NFCCard_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->NFCCard_btn_1, 11, 9);
    lv_obj_set_size(ui->NFCCard_btn_1, 70, 21);

    //Write style for NFCCard_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->NFCCard_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->NFCCard_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NFCCard_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NFCCard_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NFCCard_btn_1, lv_color_hex(0xff6500), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NFCCard_btn_1, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NFCCard_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NFCCard_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NFCCard_img_1
    ui->NFCCard_img_1 = lv_img_create(ui->NFCCard);
    lv_obj_add_flag(ui->NFCCard_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->NFCCard_img_1, &_NFC32x32_alpha_32x32);
    lv_img_set_pivot(ui->NFCCard_img_1, 50,50);
    lv_img_set_angle(ui->NFCCard_img_1, 0);
    lv_obj_set_pos(ui->NFCCard_img_1, 107, 27);
    lv_obj_set_size(ui->NFCCard_img_1, 32, 32);

    //Write style for NFCCard_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->NFCCard_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->NFCCard_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NFCCard_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->NFCCard_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NFCCard_label_1
    ui->NFCCard_label_1 = lv_label_create(ui->NFCCard);
    lv_label_set_text(ui->NFCCard_label_1, "ID Card Check");
    lv_label_set_long_mode(ui->NFCCard_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->NFCCard_label_1, 35, 62);
    lv_obj_set_size(ui->NFCCard_label_1, 178, 17);

    //Write style for NFCCard_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NFCCard_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NFCCard_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NFCCard_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NFCCard_label_1, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NFCCard_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NFCCard_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NFCCard_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NFCCard_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NFCCard_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NFCCard_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NFCCard_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NFCCard_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NFCCard_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NFCCard_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NFCCard_label_2
    ui->NFCCard_label_2 = lv_label_create(ui->NFCCard);
    lv_label_set_text(ui->NFCCard_label_2, "请紧靠感应区刷卡");
    lv_label_set_long_mode(ui->NFCCard_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->NFCCard_label_2, 71, 84);
    lv_obj_set_size(ui->NFCCard_label_2, 100, 13);

    //Write style for NFCCard_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NFCCard_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NFCCard_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NFCCard_label_2, lv_color_hex(0x777777), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NFCCard_label_2, &lv_customer_font_alimama_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NFCCard_label_2, 238, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NFCCard_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NFCCard_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NFCCard_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NFCCard_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NFCCard_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NFCCard_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NFCCard_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NFCCard_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NFCCard_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NFCCard_cont_1
    ui->NFCCard_cont_1 = lv_obj_create(ui->NFCCard);
    lv_obj_set_pos(ui->NFCCard_cont_1, 23, 104);
    lv_obj_set_size(ui->NFCCard_cont_1, 200, 171);
    lv_obj_set_scrollbar_mode(ui->NFCCard_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for NFCCard_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NFCCard_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NFCCard_cont_1, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NFCCard_cont_1, 217, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->NFCCard_cont_1, lv_color_hex(0x111111), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->NFCCard_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NFCCard_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NFCCard_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NFCCard_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NFCCard_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NFCCard_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NFCCard_label_3
    ui->NFCCard_label_3 = lv_label_create(ui->NFCCard_cont_1);
    lv_label_set_text(ui->NFCCard_label_3, "ID:");
    lv_label_set_long_mode(ui->NFCCard_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->NFCCard_label_3, 20, 32);
    lv_obj_set_size(ui->NFCCard_label_3, 29, 16);

    //Write style for NFCCard_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NFCCard_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NFCCard_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NFCCard_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NFCCard_label_3, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NFCCard_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NFCCard_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NFCCard_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NFCCard_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NFCCard_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NFCCard_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NFCCard_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NFCCard_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NFCCard_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NFCCard_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NFCCard_label_4
    ui->NFCCard_label_4 = lv_label_create(ui->NFCCard_cont_1);
    lv_label_set_text(ui->NFCCard_label_4, "98587844524");
    lv_label_set_long_mode(ui->NFCCard_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->NFCCard_label_4, 63, 34);
    lv_obj_set_size(ui->NFCCard_label_4, 115, 13);

    //Write style for NFCCard_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NFCCard_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NFCCard_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NFCCard_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NFCCard_label_4, &lv_customer_font_alimama_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NFCCard_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NFCCard_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NFCCard_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NFCCard_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NFCCard_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NFCCard_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NFCCard_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NFCCard_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NFCCard_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NFCCard_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NFCCard_label_5
    ui->NFCCard_label_5 = lv_label_create(ui->NFCCard_cont_1);
    lv_label_set_text(ui->NFCCard_label_5, "Name:");
    lv_label_set_long_mode(ui->NFCCard_label_5, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->NFCCard_label_5, 8, 83);
    lv_obj_set_size(ui->NFCCard_label_5, 54, 16);

    //Write style for NFCCard_label_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NFCCard_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NFCCard_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NFCCard_label_5, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NFCCard_label_5, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NFCCard_label_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NFCCard_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NFCCard_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NFCCard_label_5, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NFCCard_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NFCCard_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NFCCard_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NFCCard_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NFCCard_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NFCCard_label_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NFCCard_label_6
    ui->NFCCard_label_6 = lv_label_create(ui->NFCCard_cont_1);
    lv_label_set_text(ui->NFCCard_label_6, "eason");
    lv_label_set_long_mode(ui->NFCCard_label_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->NFCCard_label_6, 79, 86);
    lv_obj_set_size(ui->NFCCard_label_6, 100, 13);

    //Write style for NFCCard_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NFCCard_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NFCCard_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NFCCard_label_6, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NFCCard_label_6, &lv_customer_font_alimama_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NFCCard_label_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NFCCard_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NFCCard_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NFCCard_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NFCCard_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NFCCard_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NFCCard_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NFCCard_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NFCCard_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NFCCard_label_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NFCCard_label_7
    ui->NFCCard_label_7 = lv_label_create(ui->NFCCard_cont_1);
    lv_label_set_text(ui->NFCCard_label_7, "Key:");
    lv_label_set_long_mode(ui->NFCCard_label_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->NFCCard_label_7, 13, 132);
    lv_obj_set_size(ui->NFCCard_label_7, 48, 19);

    //Write style for NFCCard_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NFCCard_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NFCCard_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NFCCard_label_7, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NFCCard_label_7, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NFCCard_label_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NFCCard_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NFCCard_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NFCCard_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NFCCard_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NFCCard_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NFCCard_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NFCCard_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NFCCard_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NFCCard_label_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes NFCCard_label_8
    ui->NFCCard_label_8 = lv_label_create(ui->NFCCard_cont_1);
    lv_label_set_text(ui->NFCCard_label_8, "a721b32e217f9ea21");
    lv_label_set_long_mode(ui->NFCCard_label_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->NFCCard_label_8, 65, 136);
    lv_obj_set_size(ui->NFCCard_label_8, 128, 14);

    //Write style for NFCCard_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->NFCCard_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->NFCCard_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->NFCCard_label_8, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->NFCCard_label_8, &lv_customer_font_alimama_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->NFCCard_label_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->NFCCard_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->NFCCard_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->NFCCard_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->NFCCard_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->NFCCard_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->NFCCard_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->NFCCard_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->NFCCard_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->NFCCard_label_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of NFCCard.


    //Update current screen layout.
    lv_obj_update_layout(ui->NFCCard);

    //Init events for screen.
    events_init_NFCCard(ui);
}
