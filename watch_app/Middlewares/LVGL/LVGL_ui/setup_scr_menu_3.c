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
#include "User_ExternflashManage.h"



void setup_scr_menu_3(lv_ui *ui)
{
    //Write codes menu_3
    ui->menu_3 = lv_obj_create(NULL);
    lv_obj_set_size(ui->menu_3, 240, 280);
    lv_obj_set_scrollbar_mode(ui->menu_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for menu_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->menu_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->menu_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_3_btn_1
    ui->menu_3_btn_1 = lv_btn_create(ui->menu_3);
    ui->menu_3_btn_1_label = lv_label_create(ui->menu_3_btn_1);
    lv_label_set_text(ui->menu_3_btn_1_label, "< Home");
    lv_label_set_long_mode(ui->menu_3_btn_1_label, LV_LABEL_LONG_WRAP);
    lv_obj_align(ui->menu_3_btn_1_label, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_pad_all(ui->menu_3_btn_1, 0, LV_STATE_DEFAULT);
    lv_obj_set_width(ui->menu_3_btn_1_label, LV_PCT(100));
    lv_obj_set_pos(ui->menu_3_btn_1, 7, 4);
    lv_obj_set_size(ui->menu_3_btn_1, 70, 21);

    //Write style for menu_3_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->menu_3_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->menu_3_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_3_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_3_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_3_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_3_btn_1, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_3_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_3_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_3_img_2
    ui->menu_3_img_2 = lv_img_create(ui->menu_3);
    lv_obj_add_flag(ui->menu_3_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menu_3_img_2, &_heart16x16_alpha_16x16);
    lv_img_set_pivot(ui->menu_3_img_2, 0,0);
    lv_img_set_angle(ui->menu_3_img_2, 0);
    lv_obj_set_pos(ui->menu_3_img_2, 100, 30);
    lv_obj_set_size(ui->menu_3_img_2,16, 16);
    lv_img_set_zoom(ui->menu_3_img_2,512);

    //Write style for menu_3_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menu_3_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_3_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_3_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_3_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_3_label_1
    ui->menu_3_label_1 = lv_label_create(ui->menu_3);
    lv_label_set_text(ui->menu_3_label_1, "^");
    lv_label_set_long_mode(ui->menu_3_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_3_label_1, 112, 76);
    lv_obj_set_size(ui->menu_3_label_1, 14, 12);

    //Write style for menu_3_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->menu_3_label_1, lv_color_hex(0xff6500), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->menu_3_label_1, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->menu_3_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->menu_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->menu_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->menu_3_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_3_img_3
    ui->menu_3_img_3 = lv_img_create(ui->menu_3);
    lv_obj_add_flag(ui->menu_3_img_3, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menu_3_img_3, &_wather16x16_alpha_16x16);
    lv_img_set_pivot(ui->menu_3_img_3, 0,0);
    lv_img_set_angle(ui->menu_3_img_3, 0);
    lv_obj_set_pos(ui->menu_3_img_3, 190, 80);
    lv_obj_set_size(ui->menu_3_img_3, 16, 16);
    lv_img_set_zoom(ui->menu_3_img_3,512);

    //Write style for menu_3_img_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menu_3_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_3_img_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_3_img_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_3_img_3, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_3_img_4
    ui->menu_3_img_4 = lv_img_create(ui->menu_3);
    lv_obj_add_flag(ui->menu_3_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menu_3_img_4, &_set32x32_alpha_32x32);
    lv_img_set_pivot(ui->menu_3_img_4, 50,50);
    lv_img_set_angle(ui->menu_3_img_4, 0);
    lv_obj_set_pos(ui->menu_3_img_4, 190, 170);
    lv_obj_set_size(ui->menu_3_img_4, 32, 32);

    //Write style for menu_3_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menu_3_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_3_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_3_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_3_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_3_img_5
    ui->menu_3_img_5 = lv_img_create(ui->menu_3);
    lv_obj_add_flag(ui->menu_3_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menu_3_img_5, &_syteam32x32_alpha_32x32);
    lv_img_set_pivot(ui->menu_3_img_5, 50,50);
    lv_img_set_angle(ui->menu_3_img_5, 0);
    lv_obj_set_pos(ui->menu_3_img_5, 150, 220);
    lv_obj_set_size(ui->menu_3_img_5, 32, 32);

    //Write style for menu_3_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menu_3_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_3_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_3_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_3_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_3_img_6
    ui->menu_3_img_6 = lv_img_create(ui->menu_3);
    lv_obj_add_flag(ui->menu_3_img_6, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menu_3_img_6, &_NFC32x32_alpha_32x32);
    lv_img_set_pivot(ui->menu_3_img_6, 50,50);
    lv_img_set_angle(ui->menu_3_img_6, 0);
    lv_obj_set_pos(ui->menu_3_img_6, 70, 220);
    lv_obj_set_size(ui->menu_3_img_6, 32, 32);

    //Write style for menu_3_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menu_3_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_3_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_3_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_3_img_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_3_img_7
    ui->menu_3_img_7 = lv_img_create(ui->menu_3);
    lv_obj_add_flag(ui->menu_3_img_7, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menu_3_img_7, &_location32x32_alpha_16x16);
    lv_img_set_pivot(ui->menu_3_img_7, 0,0);
    lv_img_set_angle(ui->menu_3_img_7, 0);
    lv_obj_set_pos(ui->menu_3_img_7, 20, 170);
    lv_obj_set_size(ui->menu_3_img_7, 16, 16);
    lv_img_set_zoom(ui->menu_3_img_7,512);

    //Write style for menu_3_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menu_3_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_3_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_3_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_3_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_3_img_8
    ui->menu_3_img_8 = lv_img_create(ui->menu_3);
    lv_obj_add_flag(ui->menu_3_img_8, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menu_3_img_8, &_qrcode32x32_alpha_32x32);
    lv_img_set_pivot(ui->menu_3_img_8, 50,50);
    lv_img_set_angle(ui->menu_3_img_8, 0);
    lv_obj_set_pos(ui->menu_3_img_8, 20, 80);
    lv_obj_set_size(ui->menu_3_img_8, 32, 32);

    //Write style for menu_3_img_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menu_3_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_3_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_3_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_3_img_8, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes menu_3_cont_1
    ui->menu_3_cont_1 = lv_obj_create(ui->menu_3);
    lv_obj_set_pos(ui->menu_3_cont_1, 0, 26);
    lv_obj_set_size(ui->menu_3_cont_1, 239, 248);
    lv_obj_set_scrollbar_mode(ui->menu_3_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for menu_3_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->menu_3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_3_cont_1, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->menu_3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->menu_3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->menu_3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->menu_3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->menu_3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->menu_3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    // //Write codes menu_3_btn_2
    // ui->menu_3_btn_2 = lv_btn_create(ui->menu_3);
    // ui->menu_3_btn_2_label = lv_label_create(ui->menu_3_btn_2);
    // lv_label_set_text(ui->menu_3_btn_2_label, "");
    // lv_label_set_long_mode(ui->menu_3_btn_2_label, LV_LABEL_LONG_WRAP);
    // lv_obj_align(ui->menu_3_btn_2_label, LV_ALIGN_CENTER, 0, 0);
    // lv_obj_set_style_pad_all(ui->menu_3_btn_2, 0, LV_STATE_DEFAULT);
    // lv_obj_set_width(ui->menu_3_btn_2_label, LV_PCT(100));
    // lv_obj_set_pos(ui->menu_3_btn_2, 70, 95);
    // lv_obj_set_size(ui->menu_3_btn_2, 100, 100);

    // //Write style for menu_3_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    // lv_obj_set_style_bg_opa(ui->menu_3_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_border_width(ui->menu_3_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_radius(ui->menu_3_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_shadow_width(ui->menu_3_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_img_src(ui->menu_3_btn_2, &_Frame_100x100, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_img_opa(ui->menu_3_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_bg_img_recolor_opa(ui->menu_3_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_text_color(ui->menu_3_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_text_font(ui->menu_3_btn_2, &lv_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_text_opa(ui->menu_3_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    // lv_obj_set_style_text_align(ui->menu_3_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

     //Write codes menu_3_img_9
    ui->menu_3_img_9 = lv_img_create(ui->menu_3);
    lv_obj_add_flag(ui->menu_3_img_9, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->menu_3_img_9, &_logo_100x100);
    lv_img_set_pivot(ui->menu_3_img_9, 0,0);
    lv_img_set_angle(ui->menu_3_img_9, 0);
    lv_obj_set_pos(ui->menu_3_img_9, 70, 95);
    lv_obj_set_size(ui->menu_3_img_9, 100, 100);
//    lv_img_set_zoom(ui->menu_3_img_9,512);

    //Write style for menu_3_img_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->menu_3_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->menu_3_img_9, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->menu_3_img_9, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->menu_3_img_9, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of menu_3.
    lv_obj_clear_flag(guider_ui.menu_3_cont_1,LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(guider_ui.menu_3,LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_flag(guider_ui.menu_3_img_9,LV_OBJ_FLAG_CLICKABLE);

    //Update current screen layout.
    lv_obj_update_layout(ui->menu_3);

    //Init events for screen.
    events_init_menu_3(ui);
}
