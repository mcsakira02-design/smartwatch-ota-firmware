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



int WatchGiral_3_analog_clock_1_hour_value = 3;
int WatchGiral_3_analog_clock_1_min_value = 20;
int WatchGiral_3_analog_clock_1_sec_value = 50;
lv_timer_t *WatchGiral_3_analog_clock_1_timer_hd;
bool WatchGiral_3_analog_clock_1_timer_enabled = false;
void setup_scr_WatchGiral_3(lv_ui *ui)
{
    //Write codes WatchGiral_3
    ui->WatchGiral_3 = lv_obj_create(NULL);
    lv_obj_set_size(ui->WatchGiral_3, 240, 280);
    lv_obj_set_scrollbar_mode(ui->WatchGiral_3, LV_SCROLLBAR_MODE_OFF);

    //Write style for WatchGiral_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->WatchGiral_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->WatchGiral_3, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->WatchGiral_3, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

         //Write codes WatchGiral_3_img_7
    //  Read_LvglData(0x3C47E,20000);
    ui->WatchGiral_3_img_7 = lv_img_create(ui->WatchGiral_3);
    lv_obj_add_flag(ui->WatchGiral_3_img_7, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->WatchGiral_3_img_7, &_biaopan1_100x100);
    lv_img_set_pivot(ui->WatchGiral_3_img_7, 0,0);
    lv_img_set_angle(ui->WatchGiral_3_img_7, 0);
    lv_obj_set_pos(ui->WatchGiral_3_img_7, 22, 44);
    lv_obj_set_size(ui->WatchGiral_3_img_7, 100, 100);
    lv_img_set_zoom(ui->WatchGiral_3_img_7,512);

    //Write style for WatchGiral_3_img_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->WatchGiral_3_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->WatchGiral_3_img_7, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_3_img_7, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->WatchGiral_3_img_7, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_3_analog_clock_1

        ui->WatchGiral_3_analog_clock_1 = lv_analogclock_create(ui->WatchGiral_3);
    lv_analogclock_hide_digits(ui->WatchGiral_3_analog_clock_1, true);
    lv_analogclock_set_major_ticks(ui->WatchGiral_3_analog_clock_1, 0, 0, lv_color_hex(0x555555), 10);
    lv_analogclock_set_ticks(ui->WatchGiral_3_analog_clock_1, 0, 0, lv_color_hex(0x333333));
    lv_analogclock_set_hour_needle_img(ui->WatchGiral_3_analog_clock_1, &_time_alpha_40x5, 0, 2);
    lv_analogclock_set_min_needle_img(ui->WatchGiral_3_analog_clock_1, &_fen_alpha_70x5, 0, 2);
    lv_analogclock_set_sec_needle_line(ui->WatchGiral_3_analog_clock_1, 2, lv_color_hex(0xff0027), -10);

    lv_analogclock_set_time(ui->WatchGiral_3_analog_clock_1, WatchGiral_3_analog_clock_1_hour_value, WatchGiral_3_analog_clock_1_min_value,WatchGiral_3_analog_clock_1_sec_value);
    // create timer
    if (!WatchGiral_3_analog_clock_1_timer_enabled) {
        WatchGiral_3_analog_clock_1_timer_hd= lv_timer_create(WatchGiral_3_analog_clock_1_timer, 1000, NULL);
        WatchGiral_3_analog_clock_1_timer_enabled = true;
    }
    lv_obj_set_pos(ui->WatchGiral_3_analog_clock_1, 22, 44);
    lv_obj_set_size(ui->WatchGiral_3_analog_clock_1, 200, 200);

    //Write style for WatchGiral_3_analog_clock_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->WatchGiral_3_analog_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->WatchGiral_3_analog_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_3_analog_clock_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write style for WatchGiral_3_analog_clock_1, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->WatchGiral_3_analog_clock_1, lv_color_hex(0xffffff), LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->WatchGiral_3_analog_clock_1, &lv_customer_font_alimama_12, LV_PART_TICKS|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->WatchGiral_3_analog_clock_1, 255, LV_PART_TICKS|LV_STATE_DEFAULT);

    //Write style for WatchGiral_3_analog_clock_1, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->WatchGiral_3_analog_clock_1, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->WatchGiral_3_analog_clock_1, lv_color_hex(0x4b4b4b), LV_PART_INDICATOR|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->WatchGiral_3_analog_clock_1, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);


    //Write codes WatchGiral_3_cont_1
    ui->WatchGiral_3_cont_1 = lv_obj_create(ui->WatchGiral_3);
    lv_obj_set_pos(ui->WatchGiral_3_cont_1, 197, 50);
    lv_obj_set_size(ui->WatchGiral_3_cont_1, 10, 10);
    lv_obj_set_scrollbar_mode(ui->WatchGiral_3_cont_1, LV_SCROLLBAR_MODE_OFF);

    //Write style for WatchGiral_3_cont_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->WatchGiral_3_cont_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->WatchGiral_3_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->WatchGiral_3_cont_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->WatchGiral_3_cont_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_3_cont_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->WatchGiral_3_cont_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->WatchGiral_3_cont_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->WatchGiral_3_cont_1, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_3_cont_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_3_cont_2
    ui->WatchGiral_3_cont_2 = lv_obj_create(ui->WatchGiral_3);
    lv_obj_set_pos(ui->WatchGiral_3_cont_2, 27, 220);
    lv_obj_set_size(ui->WatchGiral_3_cont_2, 10, 10);
    lv_obj_set_scrollbar_mode(ui->WatchGiral_3_cont_2, LV_SCROLLBAR_MODE_OFF);

    //Write style for WatchGiral_3_cont_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->WatchGiral_3_cont_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->WatchGiral_3_cont_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->WatchGiral_3_cont_2, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->WatchGiral_3_cont_2, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_3_cont_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->WatchGiral_3_cont_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->WatchGiral_3_cont_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->WatchGiral_3_cont_2, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_3_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_3_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_3_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_3_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_3_cont_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_3_label_1
    ui->WatchGiral_3_label_1 = lv_label_create(ui->WatchGiral_3);
    lv_label_set_text(ui->WatchGiral_3_label_1, "20");
    lv_label_set_long_mode(ui->WatchGiral_3_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->WatchGiral_3_label_1, 197, 29);
    lv_obj_set_size(ui->WatchGiral_3_label_1, 29, 18);

    //Write style for WatchGiral_3_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->WatchGiral_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->WatchGiral_3_label_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->WatchGiral_3_label_1, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->WatchGiral_3_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->WatchGiral_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->WatchGiral_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->WatchGiral_3_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->WatchGiral_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_3_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_3_label_2
    ui->WatchGiral_3_label_2 = lv_label_create(ui->WatchGiral_3);
    lv_label_set_text(ui->WatchGiral_3_label_2, "深圳");
    lv_label_set_long_mode(ui->WatchGiral_3_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->WatchGiral_3_label_2, 176, 235);
    lv_obj_set_size(ui->WatchGiral_3_label_2, 40, 18);

    //Write style for WatchGiral_3_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->WatchGiral_3_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_3_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->WatchGiral_3_label_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->WatchGiral_3_label_2, &lv_customer_font_alimama_16, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->WatchGiral_3_label_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->WatchGiral_3_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->WatchGiral_3_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->WatchGiral_3_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->WatchGiral_3_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->WatchGiral_3_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->WatchGiral_3_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->WatchGiral_3_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->WatchGiral_3_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->WatchGiral_3_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);



    //Write codes WatchGiral_3_img_4
    ui->WatchGiral_3_img_4 = lv_img_create(ui->WatchGiral_3);
    lv_obj_add_flag(ui->WatchGiral_3_img_4, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->WatchGiral_3_img_4, &_Ellipse_40x40);
    lv_img_set_pivot(ui->WatchGiral_3_img_4, 50,50);
    lv_img_set_angle(ui->WatchGiral_3_img_4, 0);
    lv_obj_set_pos(ui->WatchGiral_3_img_4, 8, 9);
    lv_obj_set_size(ui->WatchGiral_3_img_4, 40, 40);

    //Write style for WatchGiral_3_img_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->WatchGiral_3_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->WatchGiral_3_img_4, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_3_img_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->WatchGiral_3_img_4, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_3_img_5
    ui->WatchGiral_3_img_5 = lv_img_create(ui->WatchGiral_3);
    lv_obj_add_flag(ui->WatchGiral_3_img_5, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->WatchGiral_3_img_5, &_Stime_alpha_16x8);
    lv_img_set_pivot(ui->WatchGiral_3_img_5, 8,4);
    lv_img_set_angle(ui->WatchGiral_3_img_5, -100);
    lv_obj_set_pos(ui->WatchGiral_3_img_5, 27, 24);
    lv_obj_set_size(ui->WatchGiral_3_img_5, 16, 8);

    //Write style for WatchGiral_3_img_5, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->WatchGiral_3_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->WatchGiral_3_img_5, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_3_img_5, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->WatchGiral_3_img_5, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes WatchGiral_3_img_6
    ui->WatchGiral_3_img_6 = lv_img_create(ui->WatchGiral_3);
    lv_obj_add_flag(ui->WatchGiral_3_img_6, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->WatchGiral_3_img_6, &_Sfen_alpha_21x6);
    lv_img_set_pivot(ui->WatchGiral_3_img_6, 0,0);
    lv_img_set_angle(ui->WatchGiral_3_img_6, 2000);
    lv_obj_set_pos(ui->WatchGiral_3_img_6, 30, 32);
    lv_obj_set_size(ui->WatchGiral_3_img_6, 21, 6);

    //Write style for WatchGiral_3_img_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->WatchGiral_3_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->WatchGiral_3_img_6, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->WatchGiral_3_img_6, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->WatchGiral_3_img_6, true, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of WatchGiral_3.


    //Update current screen layout.
    lv_obj_update_layout(ui->WatchGiral_3);

    //Init events for screen.
    events_init_WatchGiral_3(ui);
}
