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




void setup_scr_Systeamupdate(lv_ui *ui)
{
    //Write codes Systeamupdate
    ui->Systeamupdate = lv_obj_create(NULL);
    lv_obj_set_size(ui->Systeamupdate, 240, 280);
    lv_obj_set_scrollbar_mode(ui->Systeamupdate, LV_SCROLLBAR_MODE_OFF);

    //Write style for Systeamupdate, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Systeamupdate, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Systeamupdate, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Systeamupdate, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Systeamupdate_btn_1
    ui->Systeamupdate_btn_1 = lv_btn_create(ui->Systeamupdate);
    ui->Systeamupdate_btn_1_label = lv_label_create(ui->Systeamupdate_btn_1);
    lv_label_set_text(ui->Systeamupdate_btn_1_label, "< Menu");
    lv_label_set_long_mode(ui->Systeamupdate_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Systeamupdate_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Systeamupdate_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Systeamupdate_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->Systeamupdate_btn_1, 8, 7);
    lv_obj_set_size(ui->Systeamupdate_btn_1, 70, 21);

    //Write style for Systeamupdate_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Systeamupdate_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Systeamupdate_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Systeamupdate_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Systeamupdate_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Systeamupdate_btn_1, lv_color_hex(0xffbf00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Systeamupdate_btn_1, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Systeamupdate_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Systeamupdate_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Systeamupdate_img_1
    ui->Systeamupdate_img_1 = lv_img_create(ui->Systeamupdate);
    lv_obj_add_flag(ui->Systeamupdate_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Systeamupdate_img_1, &_syteam32x32_alpha_32x32);
    lv_img_set_pivot(ui->Systeamupdate_img_1, 50,50);
    lv_img_set_angle(ui->Systeamupdate_img_1, 0);
    lv_obj_set_pos(ui->Systeamupdate_img_1, 41, 51);
    lv_obj_set_size(ui->Systeamupdate_img_1, 32, 32);

    //Write style for Systeamupdate_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Systeamupdate_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Systeamupdate_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Systeamupdate_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Systeamupdate_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Systeamupdate_label_1
    ui->Systeamupdate_label_1 = lv_label_create(ui->Systeamupdate);
    lv_label_set_text(ui->Systeamupdate_label_1, "System Update");
    lv_label_set_long_mode(ui->Systeamupdate_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Systeamupdate_label_1, 78, 61);
    lv_obj_set_size(ui->Systeamupdate_label_1, 127, 21);

    //Write style for Systeamupdate_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Systeamupdate_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Systeamupdate_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Systeamupdate_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Systeamupdate_label_1, &lv_customer_font_interttf_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Systeamupdate_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Systeamupdate_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Systeamupdate_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Systeamupdate_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Systeamupdate_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Systeamupdate_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Systeamupdate_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Systeamupdate_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Systeamupdate_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Systeamupdate_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Systeamupdate_label_2
    ui->Systeamupdate_label_2 = lv_label_create(ui->Systeamupdate);
    lv_label_set_text(ui->Systeamupdate_label_2, "现在进行版本检测，请确认在连接局域网环境下进�?");
    lv_label_set_long_mode(ui->Systeamupdate_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Systeamupdate_label_2, 34, 123);
    lv_obj_set_size(ui->Systeamupdate_label_2, 174, 25);

    //Write style for Systeamupdate_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Systeamupdate_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Systeamupdate_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Systeamupdate_label_2, lv_color_hex(0x9c9c9c), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Systeamupdate_label_2, &lv_customer_font_alimama_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Systeamupdate_label_2, 149, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Systeamupdate_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Systeamupdate_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Systeamupdate_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Systeamupdate_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Systeamupdate_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Systeamupdate_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Systeamupdate_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Systeamupdate_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Systeamupdate_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Systeamupdate_btn_2
    ui->Systeamupdate_btn_2 = lv_btn_create(ui->Systeamupdate);
    ui->Systeamupdate_btn_2_label = lv_label_create(ui->Systeamupdate_btn_2);
    lv_label_set_text(ui->Systeamupdate_btn_2_label, "版本检�?");
    lv_label_set_long_mode(ui->Systeamupdate_btn_2_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Systeamupdate_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Systeamupdate_btn_2, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Systeamupdate_btn_2_label, LV_PCT(100));
    lv_obj_set_pos(ui->Systeamupdate_btn_2, 34, 190);
    lv_obj_set_size(ui->Systeamupdate_btn_2, 175, 51);

    //Write style for Systeamupdate_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Systeamupdate_btn_2, 195, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Systeamupdate_btn_2, lv_color_hex(0x303030), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Systeamupdate_btn_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Systeamupdate_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Systeamupdate_btn_2, 15, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Systeamupdate_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Systeamupdate_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Systeamupdate_btn_2, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Systeamupdate_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Systeamupdate_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of Systeamupdate.


    //Update current screen layout.
    lv_obj_update_layout(ui->Systeamupdate);

    //Init events for screen.
    events_init_Systeamupdate(ui);
}
