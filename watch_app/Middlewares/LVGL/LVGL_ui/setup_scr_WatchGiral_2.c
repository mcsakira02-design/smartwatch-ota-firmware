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

lv_obj_t *Watch_giral_2_big_img;

void setup_scr_WatchGiral_2(lv_ui *ui)
{
    // Write codes WatchGiral_2
    ui->WatchGiral_2 = lv_obj_create(NULL);
    lv_obj_set_size(ui->WatchGiral_2, 240, 280);
    lv_obj_set_scrollbar_mode(ui->WatchGiral_2, LV_SCROLLBAR_MODE_OFF);

    // Write style for WatchGiral_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->WatchGiral_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->WatchGiral_2, lv_color_hex(0xD80C24), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->WatchGiral_2, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes WatchGiral_2_cont_1
    ui->WatchGiral_2_cont_1 = lv_obj_create(ui->WatchGiral_2);
    lv_obj_set_pos(ui->WatchGiral_2_cont_1, 70, 0);
    lv_obj_set_size(ui->WatchGiral_2_cont_1, 169, 133);
    lv_obj_set_scrollbar_mode(ui->WatchGiral_2_cont_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for WatchGiral_2_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->WatchGiral_2_cont_1, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->WatchGiral_2_cont_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->WatchGiral_2_cont_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->WatchGiral_2_cont_1, LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_2_cont_1, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->WatchGiral_2_cont_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->WatchGiral_2_cont_1, lv_color_hex(0xffb900), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->WatchGiral_2_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_2_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_2_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_2_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_2_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_2_cont_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes WatchGiral_2_label_1
    ui->WatchGiral_2_label_1 = lv_label_create(ui->WatchGiral_2);
    lv_label_set_text(ui->WatchGiral_2_label_1, "19周日");
    lv_label_set_long_mode(ui->WatchGiral_2_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->WatchGiral_2_label_1, 92, 34);
    lv_obj_set_size(ui->WatchGiral_2_label_1, 139, 36);

    // Write style for WatchGiral_2_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->WatchGiral_2_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_2_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->WatchGiral_2_label_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->WatchGiral_2_label_1, &lv_customer_font_alimama_36, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->WatchGiral_2_label_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->WatchGiral_2_label_1, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->WatchGiral_2_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->WatchGiral_2_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->WatchGiral_2_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_2_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_2_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_2_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_2_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_2_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes WatchGiral_2_label_2
    ui->WatchGiral_2_label_2 = lv_label_create(ui->WatchGiral_2);
    lv_label_set_text(ui->WatchGiral_2_label_2, "13:24");
    lv_label_set_long_mode(ui->WatchGiral_2_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->WatchGiral_2_label_2, 98, 81);
    lv_obj_set_size(ui->WatchGiral_2_label_2, 127, 32);

    // Write style for WatchGiral_2_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->WatchGiral_2_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_2_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->WatchGiral_2_label_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->WatchGiral_2_label_2, &lv_customer_font_digitaldreamfatnarrow_36, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->WatchGiral_2_label_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->WatchGiral_2_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->WatchGiral_2_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->WatchGiral_2_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->WatchGiral_2_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_2_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_2_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_2_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_2_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_2_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes WatchGiral_2_img_1
    ui->WatchGiral_2_img_1 = lv_img_create(ui->WatchGiral_2);
    lv_obj_add_flag(ui->WatchGiral_2_img_1, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->WatchGiral_2_img_1, &_wtime_30x50);
    lv_img_set_pivot(ui->WatchGiral_2_img_1, 0, 0);
    lv_img_set_angle(ui->WatchGiral_2_img_1, 0);
    lv_obj_set_pos(ui->WatchGiral_2_img_1, 1, 96);
    lv_obj_set_size(ui->WatchGiral_2_img_1, 30, 50);
    lv_img_set_zoom(ui->WatchGiral_2_img_1,512);

    // Write style for WatchGiral_2_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->WatchGiral_2_img_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->WatchGiral_2_img_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_2_img_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->WatchGiral_2_img_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    // // add exet img
    // if (ui->Message != NULL)
    // {
    //     lv_obj_del(ui->Message);
    // }
    // memset(lvgl_data, 0, sizeof(lvgl_data));
    // Read_LvglData(0x3C47E, 20000);
    //
    // externflash_read(0x3C47E,20000,lvgl_data);
    // Write codes WatchGiral_2_img_2
    ui->WatchGiral_2_img_2 = lv_img_create(ui->WatchGiral_2);
    lv_obj_add_flag(ui->WatchGiral_2_img_2, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->WatchGiral_2_img_2, &_M_50x50);
    lv_img_set_pivot(ui->WatchGiral_2_img_2, 0,0);
    lv_img_set_angle(ui->WatchGiral_2_img_2, 0);
    lv_obj_set_pos(ui->WatchGiral_2_img_2, 98, 153);
    lv_obj_set_size(ui->WatchGiral_2_img_2, 50, 50);
    lv_img_set_zoom(ui->WatchGiral_2_img_2,512);

    //Write style for WatchGiral_2_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->WatchGiral_2_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->WatchGiral_2_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_2_img_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->WatchGiral_2_img_2, true, LV_PART_MAIN|LV_STATE_DEFAULT);


    // The custom code of WatchGiral_2.

    // Update current screen layout.
    lv_obj_update_layout(ui->WatchGiral_2);

    // Init events for screen.
    events_init_WatchGiral_2(ui);
}