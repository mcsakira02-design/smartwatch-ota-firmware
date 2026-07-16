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




void setup_scr_QrCode(lv_ui *ui)
{
    //Write codes QrCode
    ui->QrCode = lv_obj_create(NULL);
    lv_obj_set_size(ui->QrCode, 240, 280);
    lv_obj_set_scrollbar_mode(ui->QrCode, LV_SCROLLBAR_MODE_OFF);

    //Write style for QrCode, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->QrCode, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->QrCode, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->QrCode, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes QrCode_btn_1
    ui->QrCode_btn_1 = lv_btn_create(ui->QrCode);
    ui->QrCode_btn_1_label = lv_label_create(ui->QrCode_btn_1);
    lv_label_set_text(ui->QrCode_btn_1_label, "< Menu");
    lv_label_set_long_mode(ui->QrCode_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->QrCode_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->QrCode_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->QrCode_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->QrCode_btn_1, 8, 7);
    lv_obj_set_size(ui->QrCode_btn_1, 70, 21);

    //Write style for QrCode_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->QrCode_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->QrCode_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->QrCode_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->QrCode_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->QrCode_btn_1, lv_color_hex(0x3eff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->QrCode_btn_1, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->QrCode_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->QrCode_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes QrCode_img_1
    ui->QrCode_img_1 = lv_img_create(ui->QrCode);
    lv_obj_add_flag(ui->QrCode_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->QrCode_img_1, &_qrcode32x32_alpha_32x32);
    lv_img_set_pivot(ui->QrCode_img_1, 50,50);
    lv_img_set_angle(ui->QrCode_img_1, 0);
    lv_obj_set_pos(ui->QrCode_img_1, 105, 32);
    lv_obj_set_size(ui->QrCode_img_1, 32, 32);

    //Write style for QrCode_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->QrCode_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->QrCode_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->QrCode_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->QrCode_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes QrCode_cont_1
    ui->QrCode_cont_1 = lv_obj_create(ui->QrCode);
    lv_obj_set_pos(ui->QrCode_cont_1, 35, 99);
    lv_obj_set_size(ui->QrCode_cont_1, 180, 120);
    lv_obj_set_scrollbar_mode(ui->QrCode_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for QrCode_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->QrCode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->QrCode_cont_1, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->QrCode_cont_1, 90, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->QrCode_cont_1, lv_color_hex(0x2a2a2a), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->QrCode_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->QrCode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->QrCode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->QrCode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->QrCode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->QrCode_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes QrCode_label_2
    ui->QrCode_label_2 = lv_label_create(ui->QrCode_cont_1);
    lv_label_set_text(ui->QrCode_label_2, "a721b32e217f9ea21");
    lv_label_set_long_mode(ui->QrCode_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->QrCode_label_2, 7, 47);
    lv_obj_set_size(ui->QrCode_label_2, 171, 19);

    //Write style for QrCode_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->QrCode_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->QrCode_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->QrCode_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->QrCode_label_2, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->QrCode_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->QrCode_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->QrCode_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->QrCode_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->QrCode_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->QrCode_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->QrCode_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->QrCode_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->QrCode_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->QrCode_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes QrCode_label_1
    ui->QrCode_label_1 = lv_label_create(ui->QrCode);
    lv_label_set_text(ui->QrCode_label_1, "二维码组网公�?");
    lv_label_set_long_mode(ui->QrCode_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->QrCode_label_1, 62, 73);
    lv_obj_set_size(ui->QrCode_label_1, 126, 15);

    //Write style for QrCode_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->QrCode_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->QrCode_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->QrCode_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->QrCode_label_1, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->QrCode_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->QrCode_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->QrCode_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->QrCode_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->QrCode_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->QrCode_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->QrCode_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->QrCode_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->QrCode_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->QrCode_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes QrCode_btn_2
    ui->QrCode_btn_2 = lv_btn_create(ui->QrCode);
    ui->QrCode_btn_2_label = lv_label_create(ui->QrCode_btn_2);
    lv_label_set_text(ui->QrCode_btn_2_label, "Connnect");
    lv_label_set_long_mode(ui->QrCode_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->QrCode_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->QrCode_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->QrCode_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->QrCode_btn_2, 54, 227);
    lv_obj_set_size(ui->QrCode_btn_2, 142, 43);

    //Write style for QrCode_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->QrCode_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->QrCode_btn_2, lv_color_hex(0xffa300), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->QrCode_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->QrCode_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->QrCode_btn_2, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->QrCode_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->QrCode_btn_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->QrCode_btn_2, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->QrCode_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->QrCode_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of QrCode.


    //Update current screen layout.
    lv_obj_update_layout(ui->QrCode);

    //Init events for screen.
    events_init_QrCode(ui);
}
