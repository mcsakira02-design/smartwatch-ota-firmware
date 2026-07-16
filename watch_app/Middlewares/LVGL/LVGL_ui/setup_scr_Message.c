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
#include "UI_Resource.h"
extern lv_obj_t* Watch_giral_2_big_img;

void setup_scr_Message(lv_ui *ui)
{
    //Write codes Message
    ui->Message = lv_obj_create(NULL);
    lv_obj_set_size(ui->Message, 240, 280);
    lv_obj_set_scrollbar_mode(ui->Message, LV_SCROLLBAR_MODE_OFF);

    //Write style for Message, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->Message, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Message, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Message, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);


//         if(ui->WatchGiral_2 != NULL)
//         {
//             lv_obj_del(ui->WatchGiral_2);
//         }
//     memset(lvgl_data,0,sizeof(lvgl_data));

// //     //add exet img
// //    externflash_read(0x3765E,20000,lvgl_data);
//   Read_LvglData(0x3765E,20000);

    //Write codes Message_img_1
    ui->Message_img_1 = lv_img_create(ui->Message);
    lv_obj_add_flag(ui->Message_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Message_img_1, &_Frame_50x50);
    lv_img_set_pivot(ui->Message_img_1, 0,0);
    lv_img_set_angle(ui->Message_img_1, 0);
    lv_obj_set_pos(ui->Message_img_1, 70, 90);
    lv_obj_set_size(ui->Message_img_1, 50, 50);
    lv_img_set_zoom(ui->Message_img_1,512);

    //Write style for Message_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Message_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Message_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Message_img_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Message_img_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Message_cont_1
    ui->Message_cont_1 = lv_obj_create(ui->Message);
    lv_obj_set_pos(ui->Message_cont_1, 29, 39);
    lv_obj_set_size(ui->Message_cont_1, 50, 50);
    lv_obj_set_scrollbar_mode(ui->Message_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for Message_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Message_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->Message_cont_1, 53, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->Message_cont_1, lv_color_hex(0xf00000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->Message_cont_1, LV_BORDER_SIDE_TOP, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Message_cont_1, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Message_cont_1, 109, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Message_cont_1, lv_color_hex(0xf00000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Message_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Message_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Message_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Message_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Message_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Message_cont_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->Message_cont_1, lv_color_hex(0xff0027), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->Message_cont_1, 102, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->Message_cont_1, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->Message_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->Message_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Message_cont_2
    ui->Message_cont_2 = lv_obj_create(ui->Message);
    lv_obj_set_pos(ui->Message_cont_2, 29, 197);
    lv_obj_set_size(ui->Message_cont_2, 50, 50);
    lv_obj_set_scrollbar_mode(ui->Message_cont_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for Message_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Message_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->Message_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->Message_cont_2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->Message_cont_2, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Message_cont_2, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Message_cont_2, 109, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Message_cont_2, lv_color_hex(0xdce43b), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Message_cont_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Message_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Message_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Message_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Message_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Message_cont_2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->Message_cont_2, lv_color_hex(0xd7ff00), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->Message_cont_2, 104, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->Message_cont_2, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->Message_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->Message_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Message_cont_3
    ui->Message_cont_3 = lv_obj_create(ui->Message);
    lv_obj_set_pos(ui->Message_cont_3, 166, 197);
    lv_obj_set_size(ui->Message_cont_3, 50, 50);
    lv_obj_set_scrollbar_mode(ui->Message_cont_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for Message_cont_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Message_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->Message_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->Message_cont_3, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->Message_cont_3, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Message_cont_3, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Message_cont_3, 109, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Message_cont_3, lv_color_hex(0x1fe625), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Message_cont_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Message_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Message_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Message_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Message_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Message_cont_3, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->Message_cont_3, lv_color_hex(0x00ff16), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->Message_cont_3, 104, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->Message_cont_3, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->Message_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->Message_cont_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Message_cont_4
    ui->Message_cont_4 = lv_obj_create(ui->Message);
    lv_obj_set_pos(ui->Message_cont_4, 162, 39);
    lv_obj_set_size(ui->Message_cont_4, 50, 50);
    lv_obj_set_scrollbar_mode(ui->Message_cont_4, LV_SCROLLBAR_MODE_OFF);

    //Write style for Message_cont_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Message_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->Message_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->Message_cont_4, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->Message_cont_4, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Message_cont_4, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Message_cont_4, 109, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->Message_cont_4, lv_color_hex(0x00e7ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->Message_cont_4, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Message_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Message_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Message_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Message_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Message_cont_4, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_color(ui->Message_cont_4, lv_color_hex(0x00d9ff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_opa(ui->Message_cont_4, 104, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_spread(ui->Message_cont_4, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_x(ui->Message_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_ofs_y(ui->Message_cont_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Message_img_4
    ui->Message_img_4 = lv_img_create(ui->Message);
    lv_obj_add_flag(ui->Message_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Message_img_4, &_location32x32_alpha_16x16);
    lv_img_set_pivot(ui->Message_img_4, 0,0);
    lv_img_set_angle(ui->Message_img_4, 0);
    lv_obj_set_pos(ui->Message_img_4, 170, 43);
    lv_obj_set_size(ui->Message_img_4, 16, 16);

    //Write style for Message_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Message_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Message_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Message_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Message_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Message_img_6
    ui->Message_img_6 = lv_img_create(ui->Message);
    lv_obj_add_flag(ui->Message_img_6, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Message_img_6, &_heart16x16_alpha_16x16);
    lv_img_set_pivot(ui->Message_img_6, 0,0);
    lv_img_set_angle(ui->Message_img_6, 0);
    lv_obj_set_pos(ui->Message_img_6, 38, 43);
    lv_obj_set_size(ui->Message_img_6, 16, 16);

    //Write style for Message_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Message_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Message_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Message_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Message_img_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Message_img_7
    ui->Message_img_7 = lv_img_create(ui->Message);
    lv_obj_add_flag(ui->Message_img_7, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Message_img_7, &_tiwen_alpha_16x16);
    lv_img_set_pivot(ui->Message_img_7, 0,0);
    lv_img_set_angle(ui->Message_img_7, 0);
    lv_obj_set_pos(ui->Message_img_7, 38, 202);
    lv_obj_set_size(ui->Message_img_7, 16, 16);

    //Write style for Message_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Message_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Message_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Message_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Message_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Message_img_8
    ui->Message_img_8 = lv_img_create(ui->Message);
    lv_obj_add_flag(ui->Message_img_8, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->Message_img_8, &_pa_alpha_16x16);
    lv_img_set_pivot(ui->Message_img_8, 0,0);
    lv_img_set_angle(ui->Message_img_8, 0);
    lv_obj_set_pos(ui->Message_img_8, 178, 202);
    lv_obj_set_size(ui->Message_img_8, 16, 16);

    //Write style for Message_img_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->Message_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->Message_img_8, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Message_img_8, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->Message_img_8, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Message_label_1
    ui->Message_label_1 = lv_label_create(ui->Message);
    lv_label_set_text(ui->Message_label_1, "心率64/min");
    lv_label_set_long_mode(ui->Message_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Message_label_1, 24, 78);
    lv_obj_set_size(ui->Message_label_1, 59, 11);

    //Write style for Message_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Message_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Message_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Message_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Message_label_1, &lv_customer_font_alimama_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Message_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Message_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Message_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Message_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Message_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Message_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Message_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Message_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Message_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Message_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Message_label_2
    ui->Message_label_2 = lv_label_create(ui->Message);
    lv_label_set_text(ui->Message_label_2, "224m");
    lv_label_set_long_mode(ui->Message_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Message_label_2, 162, 78);
    lv_obj_set_size(ui->Message_label_2, 56, 11);

    //Write style for Message_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Message_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Message_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Message_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Message_label_2, &lv_customer_font_alimama_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Message_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Message_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Message_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Message_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Message_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Message_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Message_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Message_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Message_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Message_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Message_label_3
    ui->Message_label_3 = lv_label_create(ui->Message);
    lv_label_set_text(ui->Message_label_3, "体温30/1");
    lv_label_set_long_mode(ui->Message_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Message_label_3, 24, 238);
    lv_obj_set_size(ui->Message_label_3, 62, 12);

    //Write style for Message_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Message_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Message_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Message_label_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Message_label_3, &lv_customer_font_alimama_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Message_label_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Message_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Message_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Message_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Message_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Message_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Message_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Message_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Message_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Message_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes Message_label_4
    ui->Message_label_4 = lv_label_create(ui->Message);
    lv_label_set_text(ui->Message_label_4, "爬行720ppm");
    lv_label_set_long_mode(ui->Message_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->Message_label_4, 144, 238);
    lv_obj_set_size(ui->Message_label_4, 100, 15);

    //Write style for Message_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->Message_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->Message_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->Message_label_4, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->Message_label_4, &lv_customer_font_alimama_12, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->Message_label_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->Message_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->Message_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->Message_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->Message_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->Message_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->Message_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->Message_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->Message_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->Message_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of Message.
    lv_img_set_zoom(guider_ui.Message_img_6,512);
    lv_img_set_zoom(guider_ui.Message_img_4,512);
    lv_img_set_zoom(guider_ui.Message_img_7,512);
    lv_img_set_zoom(guider_ui.Message_img_8,512);

    //Update current screen layout.
    lv_obj_update_layout(ui->Message);

    //Init events for screen.
    events_init_Message(ui);
}
