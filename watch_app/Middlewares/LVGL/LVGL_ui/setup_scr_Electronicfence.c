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




void setup_scr_Electronicfence(lv_ui *ui)
{
    //Write codes Electronicfence
    ui->Electronicfence = lv_obj_create(NULL);
    lv_obj_set_size(ui->Electronicfence, 240, 280);
    lv_obj_set_scrollbar_mode(ui->Electronicfence, LV_SCROLLBAR_MODE_OFF);

    //Write style for Electronicfence, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Electronicfence, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Electronicfence, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Electronicfence, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Electronicfence_btn_1
    ui->Electronicfence_btn_1 = lv_btn_create(ui->Electronicfence);
    ui->Electronicfence_btn_1_label = lv_label_create(ui->Electronicfence_btn_1);
    lv_label_set_text(ui->Electronicfence_btn_1_label, "< Menu");
    lv_label_set_long_mode(ui->Electronicfence_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->Electronicfence_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->Electronicfence_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->Electronicfence_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->Electronicfence_btn_1, 7, 4);
    lv_obj_set_size(ui->Electronicfence_btn_1, 70, 21);

    //Write style for Electronicfence_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Electronicfence_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->Electronicfence_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Electronicfence_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Electronicfence_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Electronicfence_btn_1, lv_color_hex(0x007fff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Electronicfence_btn_1, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Electronicfence_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Electronicfence_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Electronicfence_cont_1
    ui->Electronicfence_cont_1 = lv_obj_create(ui->Electronicfence);
    lv_obj_set_pos(ui->Electronicfence_cont_1, 16, 79);
    lv_obj_set_size(ui->Electronicfence_cont_1, 200, 200);
    lv_obj_set_scrollbar_mode(ui->Electronicfence_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for Electronicfence_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Electronicfence_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Electronicfence_cont_1, 100, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Electronicfence_cont_1, 111, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Electronicfence_cont_1, lv_color_hex(0x333333), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Electronicfence_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Electronicfence_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Electronicfence_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Electronicfence_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Electronicfence_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Electronicfence_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Electronicfence_cont_2
    ui->Electronicfence_cont_2 = lv_obj_create(ui->Electronicfence_cont_1);
    lv_obj_set_pos(ui->Electronicfence_cont_2, 15, 57);
    lv_obj_set_size(ui->Electronicfence_cont_2, 50, 50);
    lv_obj_set_scrollbar_mode(ui->Electronicfence_cont_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for Electronicfence_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Electronicfence_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Electronicfence_cont_2, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Electronicfence_cont_2, 125, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Electronicfence_cont_2, lv_color_hex(0xffbf00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Electronicfence_cont_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Electronicfence_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Electronicfence_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Electronicfence_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Electronicfence_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Electronicfence_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Electronicfence_cont_3
    ui->Electronicfence_cont_3 = lv_obj_create(ui->Electronicfence_cont_1);
    lv_obj_set_pos(ui->Electronicfence_cont_3, 117, 24);
    lv_obj_set_size(ui->Electronicfence_cont_3, 50, 50);
    lv_obj_set_scrollbar_mode(ui->Electronicfence_cont_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for Electronicfence_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Electronicfence_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Electronicfence_cont_3, 25, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Electronicfence_cont_3, 125, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Electronicfence_cont_3, lv_color_hex(0xff0027), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Electronicfence_cont_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Electronicfence_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Electronicfence_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Electronicfence_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Electronicfence_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Electronicfence_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Electronicfence_img_1
    ui->Electronicfence_img_1 = lv_img_create(ui->Electronicfence_cont_1);
    lv_obj_add_flag(ui->Electronicfence_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Electronicfence_img_1, &_location20x20_alpha_20x20);
    lv_img_set_pivot(ui->Electronicfence_img_1, 50,50);
    lv_img_set_angle(ui->Electronicfence_img_1, 0);
    lv_obj_set_pos(ui->Electronicfence_img_1, 67, 147);
    lv_obj_set_size(ui->Electronicfence_img_1, 20, 20);

    //Write style for Electronicfence_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Electronicfence_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Electronicfence_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Electronicfence_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Electronicfence_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Electronicfence_label_1
    ui->Electronicfence_label_1 = lv_label_create(ui->Electronicfence);
    lv_label_set_text(ui->Electronicfence_label_1, "电子围栏预警");
    lv_label_set_long_mode(ui->Electronicfence_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Electronicfence_label_1, 69, 54);
    lv_obj_set_size(ui->Electronicfence_label_1, 100, 17);

    //Write style for Electronicfence_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Electronicfence_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Electronicfence_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Electronicfence_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Electronicfence_label_1, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Electronicfence_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Electronicfence_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Electronicfence_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Electronicfence_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Electronicfence_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Electronicfence_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Electronicfence_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Electronicfence_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Electronicfence_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Electronicfence_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Electronicfence_img_2
    ui->Electronicfence_img_2 = lv_img_create(ui->Electronicfence);
    lv_obj_add_flag(ui->Electronicfence_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Electronicfence_img_2, &_location32x32_alpha_16x16);
    lv_img_set_pivot(ui->Electronicfence_img_2, 0,0);
    lv_img_set_angle(ui->Electronicfence_img_2, 0);
    lv_obj_set_pos(ui->Electronicfence_img_2, 103, 22);
    lv_obj_set_size(ui->Electronicfence_img_2, 16, 16);
    lv_img_set_zoom(ui->Electronicfence_img_2,512);

    //Write style for Electronicfence_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Electronicfence_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Electronicfence_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Electronicfence_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Electronicfence_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of Electronicfence.


    //Update current screen layout.
    lv_obj_update_layout(ui->Electronicfence);

    //Init events for screen.
    events_init_Electronicfence(ui);
}
