/*
 * Copyright 2025 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

#include "UI_Resource.h"

uint16_t screen_index = 0;
bool is_open_bt = 0;
static uint16_t level;
#include <stdlib.h>
static uint16_t last_angle = 0;
static lv_sqrt_res_t radius;
#define CENTER_X 120
#define CENTER_Y 140
#define menu_3_cnt 7
// 初始坐标
static lv_point_t initial_points[menu_3_cnt] = {
    {100, 30},
    {190, 80},
    {190, 170},
    {150, 220},
    {70, 220},
    {20, 170},
    {20, 80}};
// 起始�??
lv_point_t start_point;
bool is_pissing = 0;
lv_obj_t *scroll_obj[menu_3_cnt];
int get_touch_quadrant()
{
    // 获取屏幕分辨�??
    lv_coord_t screen_width = lv_disp_get_hor_res(NULL);
    lv_coord_t screen_height = lv_disp_get_ver_res(NULL);

    // 计算屏幕中心
    lv_point_t center = {
        .x = screen_width / 2,
        .y = screen_height / 2};

    // 获取触摸�??
    lv_indev_t *indev = lv_indev_get_act();
    lv_point_t point;
    lv_indev_get_point(indev, &point);

    // 计算相对坐标（注�?? y 轴方向反转）
    int32_t rel_x = point.x - center.x;
    int32_t rel_y = -(point.y - center.y);

    // 判断象限
    if (rel_x > 0 && rel_y > 0)
    {
        return 1;
    }
    else if (rel_x < 0 && rel_y > 0)
    {
        return 2;
    }
    else if (rel_x < 0 && rel_y < 0)
    {
        return 3;
    }
    else if (rel_x > 0 && rel_y < 0)
    {
        return 4;
    }
    else
    {
        return 0; // 位于坐标轴上
    }
}
uint16_t mode = 0;

extern lv_obj_t *Watch_giral_2_big_img;
extern lv_timer_t *WatchGiral_3_analog_clock_1_timer_hd;
extern bool WatchGiral_3_analog_clock_1_timer_enabled;

static void WatchGiral_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_SCREEN_LOADED:
    {
        screen_index = 0;
        break;
    }

        // case LV_EVENT_GESTURE:
        // {
        //     lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        //     switch(dir) {
        //     case LV_DIR_BOTTOM:
        //     {
        //         lv_indev_wait_release(lv_indev_get_act());
        //         ui_load_scr_animation(&guider_ui, &guider_ui.top_lap, guider_ui.top_lap_del, &guider_ui.WatchGiral_1_del, setup_scr_top_lap, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 200, 0, true, true);
        //         break;
        //     }
        //     case LV_DIR_RIGHT:
        //     {
        //         lv_indev_wait_release(lv_indev_get_act());
        //         ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_2, guider_ui.WatchGiral_2_del, &guider_ui.WatchGiral_1_del, setup_scr_WatchGiral_2, LV_SCR_LOAD_ANIM_OVER_RIGHT, 200, 0, true, true);
        //         break;
        //     }
        //     case LV_DIR_LEFT:
        //     {
        //         lv_indev_wait_release(lv_indev_get_act());
        //         switch(mode) {
        //         case 0:
        //             ui_load_scr_animation(&guider_ui, &guider_ui.menu_1, guider_ui.menu_1_del, &guider_ui.Set_del, setup_scr_menu_1, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        //             break;
        //         case 1:
        //             ui_load_scr_animation(&guider_ui, &guider_ui.menu_2, guider_ui.menu_2_del, &guider_ui.Set_del, setup_scr_menu_2, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        //             break;
        //         case 2:
        //             ui_load_scr_animation(&guider_ui, &guider_ui.menu_3, guider_ui.menu_3_del, &guider_ui.Set_del, setup_scr_menu_3, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        //             break;
        //         }
        //         break;
        //     }
        //     case LV_DIR_TOP:
        //     {
        //         lv_indev_wait_release(lv_indev_get_act());
        //         ui_load_scr_animation(&guider_ui, &guider_ui.Message, guider_ui.Message_del, &guider_ui.WatchGiral_1_del, setup_scr_Message, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 0, true, true);
        //         break;
        //     }
        //     default:
        //         break;
        //     }
        //     break;
        // }

        // case LV_EVENT_SHORT_CLICKED:
        // {
        //     lv_indev_wait_release(lv_indev_get_act());
        //     ui_load_scr_animation(&guider_ui, &guider_ui.top_lap, guider_ui.top_lap_del, &guider_ui.WatchGiral_1_del, setup_scr_top_lap, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 200, 0, true, true);
        //     break;
        // }

    case LV_EVENT_SHORT_CLICKED:
    {
        lv_indev_wait_release(lv_indev_get_act());
        ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_2, guider_ui.WatchGiral_2_del, &guider_ui.WatchGiral_1_del, setup_scr_WatchGiral_2, LV_SCR_LOAD_ANIM_OVER_RIGHT, 200, 0, true, true);
        break;
    }
        // case LV_EVENT_LONG_PRESSED:
        // {
        //     lv_indev_wait_release(lv_indev_get_act());
        //     ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_2, guider_ui.WatchGiral_2_del, &guider_ui.WatchGiral_1_del, setup_scr_WatchGiral_2, LV_SCR_LOAD_ANIM_OVER_RIGHT, 200, 0, true, true);
        //     break;
        // }

    case LV_EVENT_LONG_PRESSED:
    {

        lv_indev_wait_release(lv_indev_get_act());
        // if(Watch_giral_2_big_img != NULL)
        // {
        //     lv_obj_del(Watch_giral_2_big_img);
        // }
        //     memset(&lvgl_data,0,sizeof(lvgl_data));
        //    Read_LvglData(0x3765E,20000);
        //   externflash_read(0x3765E,20000,lvgl_data);
        ui_load_scr_animation(&guider_ui, &guider_ui.Message, guider_ui.Message_del, &guider_ui.WatchGiral_1_del, setup_scr_Message, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_WatchGiral_1(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->WatchGiral_1, WatchGiral_1_event_handler, LV_EVENT_ALL, ui);
}

static void WatchGiral_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_SCREEN_LOADED:
    {
        screen_index = 1;
        break;
    }
        // case LV_EVENT_GESTURE:
        // {
        //     lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        //     switch(dir) {
        //     case LV_DIR_RIGHT:
        //     {
        //         lv_indev_wait_release(lv_indev_get_act());
        //         ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_3, guider_ui.WatchGiral_3_del, &guider_ui.WatchGiral_2_del, setup_scr_WatchGiral_3, LV_SCR_LOAD_ANIM_OVER_LEFT, 200, 0, true, true);
        //         break;
        //     }
        //     case LV_DIR_BOTTOM:
        //     {
        //         lv_indev_wait_release(lv_indev_get_act());
        //         ui_load_scr_animation(&guider_ui, &guider_ui.top_lap, guider_ui.top_lap_del, &guider_ui.WatchGiral_2_del, setup_scr_top_lap, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 0, true, true);
        //         break;
        //     }
        //     case LV_DIR_LEFT:
        //     {
        //         lv_indev_wait_release(lv_indev_get_act());
        //         switch(mode) {
        //         case 0:
        //             ui_load_scr_animation(&guider_ui, &guider_ui.menu_1, guider_ui.menu_1_del, &guider_ui.Set_del, setup_scr_menu_1, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        //             break;
        //         case 1:
        //             ui_load_scr_animation(&guider_ui, &guider_ui.menu_2, guider_ui.menu_2_del, &guider_ui.Set_del, setup_scr_menu_2, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        //             break;
        //         case 2:
        //             ui_load_scr_animation(&guider_ui, &guider_ui.menu_3, guider_ui.menu_3_del, &guider_ui.Set_del, setup_scr_menu_3, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        //             break;
        //         }
        //         break;
        //     }
        //     case LV_DIR_TOP:
        //     {
        //         lv_indev_wait_release(lv_indev_get_act());
        //         ui_load_scr_animation(&guider_ui, &guider_ui.Message, guider_ui.Message_del, &guider_ui.WatchGiral_2_del, setup_scr_WatchGiral_3, LV_SCR_LOAD_ANIM_OVER_RIGHT, 200, 0, true, true);
        //         break;
        //     }
        //     default:

        //         break;
        //     }
        //     break;
        // }

    case LV_EVENT_SHORT_CLICKED:
    {
        lv_indev_wait_release(lv_indev_get_act());
        ui_load_scr_animation(&guider_ui, &guider_ui.top_lap, guider_ui.top_lap_del, &guider_ui.WatchGiral_3_del, setup_scr_top_lap, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 200, 0, true, true);
        break;
    }

    case LV_EVENT_LONG_PRESSED:
    {
        lv_indev_wait_release(lv_indev_get_act());

        ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_3, guider_ui.WatchGiral_3_del, &guider_ui.WatchGiral_2_del, setup_scr_WatchGiral_3, LV_SCR_LOAD_ANIM_OVER_LEFT, 200, 0, true, true);
        break;
    }
    // case LV_EVENT_LONG_PRESSED_REPEAT:
    // {
    //     lv_indev_wait_release(lv_indev_get_act());
    //     ui_load_scr_animation(&guider_ui, &guider_ui.Message, guider_ui.Message_del, &guider_ui.WatchGiral_2_del, setup_scr_Message, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 0, true, true);
    //     break;
    // }
    case LV_EVENT_SCREEN_UNLOADED:
    {

        break;
    }
    default:
        break;
    }
}

void events_init_WatchGiral_2(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->WatchGiral_2, WatchGiral_2_event_handler, LV_EVENT_ALL, ui);
}

static void WatchGiral_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_SCREEN_LOADED:
    {
        screen_index = 2;
        // if (guider_ui.WatchGiral_2 != NULL)
        // {
        //     lv_obj_del(guider_ui.WatchGiral_2);
        // }

        break;
    }
        // case LV_EVENT_GESTURE:
        // {
        //     lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        //     switch (dir)
        //     {
        //     case LV_DIR_RIGHT:
        //     {
        //         lv_indev_wait_release(lv_indev_get_act());
        //         ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_1, guider_ui.WatchGiral_1_del, &guider_ui.WatchGiral_3_del, setup_scr_WatchGiral_1, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, false, false);
        //         break;
        //     }
        //     case LV_DIR_BOTTOM:
        //     {
        //         lv_indev_wait_release(lv_indev_get_act());
        //         ui_load_scr_animation(&guider_ui, &guider_ui.top_lap, guider_ui.top_lap_del, &guider_ui.WatchGiral_3_del, setup_scr_top_lap, LV_SCR_LOAD_ANIM_OVER_BOTTOM, 200, 0, false, false);
        //         break;
        //     }
        //     case LV_DIR_LEFT:
        //     {
        //         lv_indev_wait_release(lv_indev_get_act());
        //         switch (mode)
        //         {
        //         case 0:
        //             ui_load_scr_animation(&guider_ui, &guider_ui.menu_1, guider_ui.menu_1_del, &guider_ui.Set_del, setup_scr_menu_1, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        //             break;
        //         case 1:
        //             ui_load_scr_animation(&guider_ui, &guider_ui.menu_2, guider_ui.menu_2_del, &guider_ui.Set_del, setup_scr_menu_2, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        //             break;
        //         case 2:
        //             ui_load_scr_animation(&guider_ui, &guider_ui.menu_3, guider_ui.menu_3_del, &guider_ui.Set_del, setup_scr_menu_3, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        //             break;
        //         }
        //         break;
        //     }
        //     case LV_DIR_TOP:
        //     {
        //         lv_indev_wait_release(lv_indev_get_act());
        //         ui_load_scr_animation(&guider_ui, &guider_ui.Message, guider_ui.Message_del, &guider_ui.WatchGiral_3_del, setup_scr_Message, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 0, false, false);
        //         break;
        //     }
        //     default:
        //         break;
        //     }
        //     break;
        // }

    case LV_EVENT_SHORT_CLICKED:
    {
        lv_indev_wait_release(lv_indev_get_act());
                switch (mode)
                {
                case 0:
                    ui_load_scr_animation(&guider_ui, &guider_ui.menu_1, guider_ui.menu_1_del, &guider_ui.Set_del, setup_scr_menu_1, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
                    break;
                case 1:
                    ui_load_scr_animation(&guider_ui, &guider_ui.menu_2, guider_ui.menu_2_del, &guider_ui.Set_del, setup_scr_menu_2, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
                    break;
                case 2:
                    ui_load_scr_animation(&guider_ui, &guider_ui.menu_3, guider_ui.menu_3_del, &guider_ui.Set_del, setup_scr_menu_3, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
                    break;
                }
        break;
    }

    case LV_EVENT_SCREEN_UNLOAD_START:
    {
        if (WatchGiral_3_analog_clock_1_timer_hd != NULL)
        {
            lv_timer_del(WatchGiral_3_analog_clock_1_timer_hd);
            WatchGiral_3_analog_clock_1_timer_hd = NULL;
        }
        WatchGiral_3_analog_clock_1_timer_enabled = false;
        break;
    }
    case LV_EVENT_LONG_PRESSED:
    {
        lv_indev_wait_release(lv_indev_get_act());
        ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_1, guider_ui.WatchGiral_1_del, &guider_ui.WatchGiral_3_del, setup_scr_WatchGiral_1, LV_SCR_LOAD_ANIM_MOVE_LEFT, 200, 0, true, true);
        break;
    }
    // case LV_EVENT_LONG_PRESSED_REPEAT:
    // {
    //     lv_indev_wait_release(lv_indev_get_act());
    //     ui_load_scr_animation(&guider_ui, &guider_ui.Message, guider_ui.Message_del, &guider_ui.WatchGiral_3_del, setup_scr_Message, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 0, true, true);
    //     break;
    // }
    default:
        break;
    }
}

void events_init_WatchGiral_3(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->WatchGiral_3, WatchGiral_3_event_handler, LV_EVENT_ALL, ui);
}

static void top_lap_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_GESTURE:
    {
        lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
        switch (dir)
        {
            // case LV_DIR_TOP:
            // {
            //     lv_indev_wait_release(lv_indev_get_act());
            //     switch (screen_index)
            //     {
            //     case 0:
            //         /* code */
            //         lv_indev_wait_release(lv_indev_get_act());
            //         ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_1, guider_ui.WatchGiral_1_del, &guider_ui.top_lap_del, setup_scr_WatchGiral_1, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 0, true, true);
            //         break;
            //     case 1:
            //         lv_indev_wait_release(lv_indev_get_act());
            //         ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_2, guider_ui.WatchGiral_2_del, &guider_ui.top_lap_del, setup_scr_WatchGiral_2, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 0, true, true);
            //         break;
            //     case 2:
            //         lv_indev_wait_release(lv_indev_get_act());
            //         ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_3, guider_ui.WatchGiral_3_del, &guider_ui.top_lap_del, setup_scr_WatchGiral_3, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 0, true, true);
            //         break;
            //     default:
            //         break;
            //     }
            //     break;
            // }

        default:
            break;
        }
        break;
    }
    case LV_EVENT_LONG_PRESSED:
    {
        lv_indev_wait_release(lv_indev_get_act());
        switch (screen_index)
        {
        case 0:
            /* code */
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_1, guider_ui.WatchGiral_1_del, &guider_ui.top_lap_del, setup_scr_WatchGiral_1, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 0, true, true);
            break;
        case 1:
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_2, guider_ui.WatchGiral_2_del, &guider_ui.top_lap_del, setup_scr_WatchGiral_2, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 0, true, true);
            break;
        case 2:
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_3, guider_ui.WatchGiral_3_del, &guider_ui.top_lap_del, setup_scr_WatchGiral_3, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 0, true, true);
            break;
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void top_lap_cont_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        if (is_open_bt)
        {
            is_open_bt = 0;
            lv_obj_set_style_bg_color(guider_ui.top_lap_cont_1, lv_color_hex(0x525252), LV_PART_MAIN);
        }
        else
        {
            lv_obj_set_style_bg_color(guider_ui.top_lap_cont_1, lv_color_hex(0x2f92da), LV_PART_MAIN);
            is_open_bt = 1;
        }
        break;
    }
    default:
        break;
    }
}

static void top_lap_img_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        if (is_open_bt)
        {
            lv_obj_set_style_bg_color(guider_ui.top_lap_cont_1, lv_color_hex(0x525252), LV_PART_MAIN);
            is_open_bt = 0;
        }
        else
        {
            lv_obj_set_style_bg_color(guider_ui.top_lap_cont_1, lv_color_hex(0x2f92da), LV_PART_MAIN);
            is_open_bt = 1;
        }
        break;
    }
    default:
        break;
    }
}

static void top_lap_cont_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.Electronicfence, guider_ui.Electronicfence_del, &guider_ui.top_lap_del, setup_scr_Electronicfence, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

static void top_lap_cont_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {

        break;
    }
    default:
        break;
    }
}

static void top_lap_cont_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.NFCCard, guider_ui.NFCCard_del, &guider_ui.top_lap_del, setup_scr_NFCCard, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_top_lap(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->top_lap, top_lap_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->top_lap_cont_1, top_lap_cont_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->top_lap_img_1, top_lap_img_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->top_lap_cont_2, top_lap_cont_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->top_lap_cont_3, top_lap_cont_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->top_lap_cont_4, top_lap_cont_4_event_handler, LV_EVENT_ALL, ui);
}

static void menu_1_cont_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.Heart, guider_ui.Heart_del, &guider_ui.menu_1_del, setup_scr_Heart, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void menu_1_cont_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.Electronicfence, guider_ui.Electronicfence_del, &guider_ui.menu_1_del, setup_scr_Electronicfence, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void menu_1_cont_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.NFCCard, guider_ui.NFCCard_del, &guider_ui.menu_1_del, setup_scr_NFCCard, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void menu_1_cont_5_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.QrCode, guider_ui.QrCode_del, &guider_ui.menu_1_del, setup_scr_QrCode, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void menu_1_cont_6_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.Systeamupdate, guider_ui.Systeamupdate_del, &guider_ui.menu_1_del, setup_scr_Systeamupdate, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void menu_1_cont_8_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.Set, guider_ui.Set_del, &guider_ui.menu_1_del, setup_scr_Set, LV_SCR_LOAD_ANIM_FADE_ON, 200, 0, true, true);
        break;
    }
    default:
        break;
    }
}

static void menu_1_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        switch (screen_index)
        {
        case 0:
            /* code */
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_1, guider_ui.WatchGiral_1_del, &guider_ui.menu_1_del, setup_scr_WatchGiral_1, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, true, true);
            break;
        case 1:
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_2, guider_ui.WatchGiral_2_del, &guider_ui.menu_1_del, setup_scr_WatchGiral_2, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, true, true);
            break;
        case 2:
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_3, guider_ui.WatchGiral_3_del, &guider_ui.menu_1_del, setup_scr_WatchGiral_3, LV_SCR_LOAD_ANIM_MOVE_RIGHT, 200, 200, true, true);
            break;
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_menu_1(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->menu_1_cont_2, menu_1_cont_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_1_cont_3, menu_1_cont_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_1_cont_4, menu_1_cont_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_1_cont_5, menu_1_cont_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_1_cont_6, menu_1_cont_6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_1_cont_8, menu_1_cont_8_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_1_btn_1, menu_1_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void menu_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_SCROLL:
    {
        lv_obj_t *scroll_container = lv_event_get_target(e);
        int32_t scroll_y = lv_obj_get_scroll_y(scroll_container); // 获取滚动偏移�??
        if (scroll_y > 40)
        {
            uint16_t get_y = (scroll_y - 40);
            level = (get_y / 70);
            uint16_t over_len = (get_y % 70);
            uint16_t chage_width = (over_len * 240) / 70;
            switch (level)
            {
            case 0:
                lv_obj_set_width(guider_ui.menu_2_cont_8, 300 - chage_width);
                lv_obj_set_width(guider_ui.menu_2_cont_5, chage_width);
                lv_obj_set_width(guider_ui.menu_2_cont_3, 240);
                lv_obj_set_width(guider_ui.menu_2_cont_4, 240);
                lv_obj_set_width(guider_ui.menu_2_cont_6, 240);
                lv_obj_set_width(guider_ui.menu_2_cont_7, 240);
                break;
            case 1:
                lv_obj_set_width(guider_ui.menu_2_cont_7, 320 - chage_width);
                lv_obj_set_width(guider_ui.menu_2_cont_4, chage_width);
                lv_obj_set_width(guider_ui.menu_2_cont_3, 240);
                lv_obj_set_width(guider_ui.menu_2_cont_5, 240);
                lv_obj_set_width(guider_ui.menu_2_cont_6, 240);
                lv_obj_set_width(guider_ui.menu_2_cont_8, 240);
                break;
            case 2:
                lv_obj_set_width(guider_ui.menu_2_cont_6, 320 - chage_width);
                lv_obj_set_width(guider_ui.menu_2_cont_3, chage_width + 30);
                lv_obj_set_width(guider_ui.menu_2_cont_5, 240);
                lv_obj_set_width(guider_ui.menu_2_cont_4, 240);
                lv_obj_set_width(guider_ui.menu_2_cont_8, 240);
                lv_obj_set_width(guider_ui.menu_2_cont_7, 240);
                break;
            case 3:
                if ((360 - chage_width) > 240)
                {
                    lv_obj_set_width(guider_ui.menu_2_cont_5, 240);
                }
                else
                {
                    lv_obj_set_width(guider_ui.menu_2_cont_5, 360 - chage_width);
                }

                lv_obj_set_width(guider_ui.menu_2_cont_2, chage_width + 30);

                lv_obj_set_width(guider_ui.menu_2_cont_3, 240);
                lv_obj_set_width(guider_ui.menu_2_cont_4, 240);
                lv_obj_set_width(guider_ui.menu_2_cont_6, 240);
                lv_obj_set_width(guider_ui.menu_2_cont_7, 240);
                break;
            case 4:
                lv_obj_set_width(guider_ui.menu_2_cont_2, chage_width + 52);
                break;
            default:
                break;
            }
        }

        break;
    }
    case LV_EVENT_SCROLL_END:
    {

        switch (level)
        {
        case 0:
            lv_obj_scroll_to_y(guider_ui.menu_2, 0, LV_ANIM_ON);
            break;
        case 1:
            lv_obj_scroll_to_y(guider_ui.menu_2, 120, LV_ANIM_ON);
            break;
        case 2:
            lv_obj_scroll_to_y(guider_ui.menu_2, 200, LV_ANIM_ON);
            break;
        case 3:
            lv_obj_scroll_to_y(guider_ui.menu_2, 280, LV_ANIM_ON);
            break;
        case 4:
            lv_obj_scroll_to_y(guider_ui.menu_2, 380, LV_ANIM_ON);
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void menu_2_cont_8_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.Heart, guider_ui.Heart_del, &guider_ui.menu_2_del, setup_scr_Heart, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

static void menu_2_cont_7_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.Electronicfence, guider_ui.Electronicfence_del, &guider_ui.menu_2_del, setup_scr_Electronicfence, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

static void menu_2_cont_6_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.NFCCard, guider_ui.NFCCard_del, &guider_ui.menu_2_del, setup_scr_NFCCard, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

static void menu_2_cont_5_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.QrCode, guider_ui.QrCode_del, &guider_ui.menu_2_del, setup_scr_QrCode, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

static void menu_2_cont_4_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.Systeamupdate, guider_ui.Systeamupdate_del, &guider_ui.menu_2_del, setup_scr_Systeamupdate, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

static void menu_2_cont_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.Set, guider_ui.Set_del, &guider_ui.menu_2_del, setup_scr_Set, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

static void menu_2_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        switch (screen_index)
        {
        case 0:
            /* code */
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_1, guider_ui.WatchGiral_1_del, &guider_ui.top_lap_del, setup_scr_WatchGiral_1, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 200, true, true);
            break;
        case 1:
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_2, guider_ui.WatchGiral_2_del, &guider_ui.top_lap_del, setup_scr_WatchGiral_2, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 200, true, true);
            break;
        case 2:
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_3, guider_ui.WatchGiral_3_del, &guider_ui.top_lap_del, setup_scr_WatchGiral_3, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 200, true, true);
            break;
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_menu_2(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->menu_2, menu_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_2_cont_8, menu_2_cont_8_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_2_cont_7, menu_2_cont_7_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_2_cont_6, menu_2_cont_6_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_2_cont_5, menu_2_cont_5_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_2_cont_4, menu_2_cont_4_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_2_cont_2, menu_2_cont_2_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_2_btn_1, menu_2_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void menu_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_SCREEN_LOADED:
    {
        scroll_obj[0] = guider_ui.menu_3_img_2;
        scroll_obj[1] = guider_ui.menu_3_img_3;
        scroll_obj[2] = guider_ui.menu_3_img_4;
        scroll_obj[3] = guider_ui.menu_3_img_5;
        scroll_obj[4] = guider_ui.menu_3_img_6;
        scroll_obj[5] = guider_ui.menu_3_img_7;
        scroll_obj[6] = guider_ui.menu_3_img_8;
        break;
    }
    default:
        break;
    }
}

static void menu_3_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        switch (screen_index)
        {
        case 0:
            /* code */
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_1, guider_ui.WatchGiral_1_del, &guider_ui.top_lap_del, setup_scr_WatchGiral_1, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 200, true, true);
            break;
        case 1:
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_2, guider_ui.WatchGiral_2_del, &guider_ui.top_lap_del, setup_scr_WatchGiral_2, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 200, true, true);
            break;
        case 2:
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_3, guider_ui.WatchGiral_3_del, &guider_ui.top_lap_del, setup_scr_WatchGiral_3, LV_SCR_LOAD_ANIM_MOVE_TOP, 200, 200, true, true);
            break;
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void menu_3_cont_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_PRESSED:
    {
        lv_indev_t *indev = lv_indev_get_act();
        lv_point_t point;
        lv_indev_get_point(indev, &point);
        start_point.x = point.x;
        start_point.y = point.y;

        // move layer
        lv_obj_move_to_index(guider_ui.menu_3_img_9, 11);

        is_pissing = 1;
        break;
    }
    case LV_EVENT_PRESSING:
    {
        lv_indev_t *indev = lv_indev_get_act();
        lv_point_t point;
        lv_indev_get_point(indev, &point);
        int16_t dx = (point.x - start_point.x);
        int16_t dy = (point.y - start_point.y);

        if (LV_ABS(dx) > 20 || LV_ABS(dy) > 20)
        {
            if (is_pissing)
            {
                switch (get_touch_quadrant())
                {
                case 1:
                    if ((dx ^ dy) >= 0)
                    {
                        if (dx > 0)
                        {
                            for (int i = 0; i < menu_3_cnt; i++)
                            {

                                if (i == 6)
                                {
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].x, initial_points[0].x, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].y, initial_points[0].y, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);

                                    // 执行反向位移操作
                                    lv_obj_t *temp = scroll_obj[menu_3_cnt - 1];
                                    for (int i = menu_3_cnt - 2; i >= 0; i--)
                                    {
                                        scroll_obj[i + 1] = scroll_obj[i];
                                    }
                                    scroll_obj[0] = temp;
                                }
                                else
                                {
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].x, initial_points[i + 1].x, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].y, initial_points[i + 1].y, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
                                }
                            }
                        }
                        else
                        {
                            for (int i = 0; i < menu_3_cnt; i++)
                            {
                                if (i == 0)
                                {
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].x, initial_points[6].x, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].y, initial_points[6].y, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
                                }
                                else
                                {
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].x, initial_points[i - 1].x, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].y, initial_points[i - 1].y, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
                                    if (i == 6)
                                    {
                                        lv_obj_t *temp = scroll_obj[0];
                                        for (int i = 0; i < menu_3_cnt - 1; i++)
                                        {
                                            scroll_obj[i] = scroll_obj[i + 1];
                                        }
                                        scroll_obj[menu_3_cnt - 1] = temp;
                                    }
                                }
                            }
                        }
                    }
                    break;
                case 2:
                    if ((dx ^ dy) < 0)
                    {
                        if (dx > 0)
                        {
                            for (int i = 0; i < menu_3_cnt; i++)
                            {

                                if (i == 6)
                                {
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].x, initial_points[0].x, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].y, initial_points[0].y, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);

                                    // 执行反向位移操作
                                    lv_obj_t *temp = scroll_obj[menu_3_cnt - 1];
                                    for (int i = menu_3_cnt - 2; i >= 0; i--)
                                    {
                                        scroll_obj[i + 1] = scroll_obj[i];
                                    }
                                    scroll_obj[0] = temp;
                                }
                                else
                                {
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].x, initial_points[i + 1].x, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].y, initial_points[i + 1].y, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
                                }
                            }
                        }
                        else
                        {
                            for (int i = 0; i < menu_3_cnt; i++)
                            {
                                if (i == 0)
                                {
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].x, initial_points[6].x, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].y, initial_points[6].y, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
                                }
                                else
                                {
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].x, initial_points[i - 1].x, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].y, initial_points[i - 1].y, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
                                    if (i == 6)
                                    {
                                        lv_obj_t *temp = scroll_obj[0];
                                        for (int i = 0; i < menu_3_cnt - 1; i++)
                                        {
                                            scroll_obj[i] = scroll_obj[i + 1];
                                        }
                                        scroll_obj[menu_3_cnt - 1] = temp;
                                    }
                                }
                            }
                        }
                    }
                    break;
                case 3:

                    if ((dx ^ dy) >= 0)
                    {
                        if (dx > 0)
                        {
                            for (int i = 0; i < menu_3_cnt; i++)
                            {
                                if (i == 0)
                                {
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].x, initial_points[6].x, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].y, initial_points[6].y, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
                                }
                                else
                                {
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].x, initial_points[i - 1].x, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].y, initial_points[i - 1].y, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
                                    if (i == 6)
                                    {
                                        lv_obj_t *temp = scroll_obj[0];
                                        for (int i = 0; i < menu_3_cnt - 1; i++)
                                        {
                                            scroll_obj[i] = scroll_obj[i + 1];
                                        }
                                        scroll_obj[menu_3_cnt - 1] = temp;
                                    }
                                }
                            }
                        }
                        else
                        {
                            for (int i = 0; i < menu_3_cnt; i++)
                            {

                                if (i == 6)
                                {
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].x, initial_points[0].x, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].y, initial_points[0].y, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);

                                    // 执行反向位移操作
                                    lv_obj_t *temp = scroll_obj[menu_3_cnt - 1];
                                    for (int i = menu_3_cnt - 2; i >= 0; i--)
                                    {
                                        scroll_obj[i + 1] = scroll_obj[i];
                                    }
                                    scroll_obj[0] = temp;
                                }
                                else
                                {
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].x, initial_points[i + 1].x, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].y, initial_points[i + 1].y, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
                                }
                            }
                        }
                    }
                    break;
                case 4:

                    if ((dx ^ dy) < 0)
                    {
                        if (dx > 0)
                        {
                            for (int i = 0; i < menu_3_cnt; i++)
                            {
                                if (i == 0)
                                {
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].x, initial_points[6].x, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].y, initial_points[6].y, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
                                }
                                else
                                {
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].x, initial_points[i - 1].x, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].y, initial_points[i - 1].y, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
                                    if (i == 6)
                                    {
                                        lv_obj_t *temp = scroll_obj[0];
                                        for (int i = 0; i < menu_3_cnt - 1; i++)
                                        {
                                            scroll_obj[i] = scroll_obj[i + 1];
                                        }
                                        scroll_obj[menu_3_cnt - 1] = temp;
                                    }
                                }
                            }
                        }
                        else
                        {
                            for (int i = 0; i < menu_3_cnt; i++)
                            {

                                if (i == 6)
                                {
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].x, initial_points[0].x, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].y, initial_points[0].y, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);

                                    // 执行反向位移操作
                                    lv_obj_t *temp = scroll_obj[menu_3_cnt - 1];
                                    for (int i = menu_3_cnt - 2; i >= 0; i--)
                                    {
                                        scroll_obj[i + 1] = scroll_obj[i];
                                    }
                                    scroll_obj[0] = temp;
                                }
                                else
                                {
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].x, initial_points[i + 1].x, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_x, NULL, NULL, NULL);
                                    ui_animation(scroll_obj[i], 500, 0, initial_points[i].y, initial_points[i + 1].y, &lv_anim_path_overshoot, 0, 0, 0, 0, (lv_anim_exec_xcb_t)lv_obj_set_y, NULL, NULL, NULL);
                                }
                            }
                        }
                    }
                    break;
                }
                is_pissing = 0;
            }
        }

        break;
    }
    case LV_EVENT_PRESS_LOST:
    {
        lv_obj_move_to_index(guider_ui.menu_3_img_9, 12);
        break;
    }
    default:
        break;
    }
}

static void menu_3_btn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {

        if (scroll_obj[0] == guider_ui.menu_3_img_2)
        {
            ui_load_scr_animation(&guider_ui, &guider_ui.Heart, guider_ui.Heart_del, &guider_ui.menu_3_del, setup_scr_Heart, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        }
        if (scroll_obj[0] == guider_ui.menu_3_img_4)
        {
            ui_load_scr_animation(&guider_ui, &guider_ui.Set, guider_ui.Set_del, &guider_ui.menu_3_del, setup_scr_Set, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        }
        if (scroll_obj[0] == guider_ui.menu_3_img_5)
        {
            ui_load_scr_animation(&guider_ui, &guider_ui.Systeamupdate, guider_ui.Systeamupdate_del, &guider_ui.menu_3_del, setup_scr_Systeamupdate, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        }
        if (scroll_obj[0] == guider_ui.menu_3_img_6)
        {
            ui_load_scr_animation(&guider_ui, &guider_ui.NFCCard, guider_ui.NFCCard_del, &guider_ui.menu_3_del, setup_scr_NFCCard, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        }
        if (scroll_obj[0] == guider_ui.menu_3_img_7)
        {
            ui_load_scr_animation(&guider_ui, &guider_ui.Electronicfence, guider_ui.Electronicfence_del, &guider_ui.menu_3_del, setup_scr_Electronicfence, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        }
        if (scroll_obj[0] == guider_ui.menu_3_img_8)
        {
            ui_load_scr_animation(&guider_ui, &guider_ui.QrCode, guider_ui.QrCode_del, &guider_ui.menu_3_del, setup_scr_QrCode, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        }
        break;
    }
    default:
        break;
    }
}

void events_init_menu_3(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->menu_3, menu_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_3_btn_1, menu_3_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_3_cont_1, menu_3_cont_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->menu_3_img_9, menu_3_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void Heart_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {

        switch (mode)
        {
        case 0:
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_1, guider_ui.menu_1_del, &guider_ui.Set_del, setup_scr_menu_1, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
            break;
        case 1:
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_2, guider_ui.menu_2_del, &guider_ui.Set_del, setup_scr_menu_2, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
            break;
        case 2:
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_3, guider_ui.menu_3_del, &guider_ui.Set_del, setup_scr_menu_3, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_Heart(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Heart_btn_1, Heart_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void Electronicfence_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {

        switch (mode)
        {
        case 0:
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_1, guider_ui.menu_1_del, &guider_ui.Set_del, setup_scr_menu_1, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
            break;
        case 1:
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_2, guider_ui.menu_2_del, &guider_ui.Set_del, setup_scr_menu_2, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
            break;
        case 2:
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_3, guider_ui.menu_3_del, &guider_ui.Set_del, setup_scr_menu_3, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_Electronicfence(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Electronicfence_btn_1, Electronicfence_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void NFCCard_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {

        switch (mode)
        {
        case 0:
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_1, guider_ui.menu_1_del, &guider_ui.Set_del, setup_scr_menu_1, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
            break;
        case 1:
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_2, guider_ui.menu_2_del, &guider_ui.Set_del, setup_scr_menu_2, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
            break;
        case 2:
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_3, guider_ui.menu_3_del, &guider_ui.Set_del, setup_scr_menu_3, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_NFCCard(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->NFCCard_btn_1, NFCCard_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void QrCode_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {

        switch (mode)
        {
        case 0:
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_1, guider_ui.menu_1_del, &guider_ui.Set_del, setup_scr_menu_1, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
            break;
        case 1:
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_2, guider_ui.menu_2_del, &guider_ui.Set_del, setup_scr_menu_2, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
            break;
        case 2:
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_3, guider_ui.menu_3_del, &guider_ui.Set_del, setup_scr_menu_3, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
            break;
        }
        break;
    }
    default:
        break;
    }
}

void events_init_QrCode(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->QrCode_btn_1, QrCode_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void Systeamupdate_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {

        switch (mode)
        {
        case 0:
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_1, guider_ui.menu_1_del, &guider_ui.Set_del, setup_scr_menu_1, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
            break;
        case 1:
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_2, guider_ui.menu_2_del, &guider_ui.Set_del, setup_scr_menu_2, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
            break;
        case 2:
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_3, guider_ui.menu_3_del, &guider_ui.Set_del, setup_scr_menu_3, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void Systeamupdate_btn_2_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.Systeamupdate_cheak, guider_ui.Systeamupdate_cheak_del, &guider_ui.Systeamupdate_del, setup_scr_Systeamupdate_cheak, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_Systeamupdate(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Systeamupdate_btn_1, Systeamupdate_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Systeamupdate_btn_2, Systeamupdate_btn_2_event_handler, LV_EVENT_ALL, ui);
}

static void Systeamupdate_cheak_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.Systeamupdate, guider_ui.Systeamupdate_del, &guider_ui.Systeamupdate_cheak_del, setup_scr_Systeamupdate, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_Systeamupdate_cheak(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Systeamupdate_cheak_btn_1, Systeamupdate_cheak_btn_1_event_handler, LV_EVENT_ALL, ui);
}

static void Set_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_SCREEN_LOADED:
    {

        switch (mode)
        {
        case (0):
        {
            lv_obj_set_style_bg_color(guider_ui.Set_cont_6, lv_color_hex(0xffffff), LV_PART_MAIN);
            lv_obj_set_style_border_color(guider_ui.Set_cont_6, lv_color_hex(0x414141), LV_PART_MAIN);
            lv_obj_set_style_bg_color(guider_ui.Set_cont_4, lv_color_hex(0xffffff), LV_PART_MAIN);
            lv_obj_set_style_border_color(guider_ui.Set_cont_4, lv_color_hex(0x3d3d3d), LV_PART_MAIN);
            lv_obj_set_style_bg_color(guider_ui.Set_cont_2, lv_color_hex(0x00ff16), LV_PART_MAIN);
            lv_obj_set_style_border_color(guider_ui.Set_cont_2, lv_color_hex(0x025807), LV_PART_MAIN);
            break;
        }
        case (1):
        {
            lv_obj_set_style_bg_color(guider_ui.Set_cont_6, lv_color_hex(0xffffff), LV_PART_MAIN);
            lv_obj_set_style_border_color(guider_ui.Set_cont_6, lv_color_hex(0x474747), LV_PART_MAIN);
            lv_obj_set_style_bg_color(guider_ui.Set_cont_4, lv_color_hex(0x00ff16), LV_PART_MAIN);
            lv_obj_set_style_border_color(guider_ui.Set_cont_4, lv_color_hex(0x025807), LV_PART_MAIN);
            lv_obj_set_style_bg_color(guider_ui.Set_cont_2, lv_color_hex(0xffffff), LV_PART_MAIN);
            lv_obj_set_style_border_color(guider_ui.Set_cont_2, lv_color_hex(0x474747), LV_PART_MAIN);
            break;
        }
        case (2):
        {
            lv_obj_set_style_bg_color(guider_ui.Set_cont_6, lv_color_hex(0x00ff16), LV_PART_MAIN);
            lv_obj_set_style_border_color(guider_ui.Set_cont_6, lv_color_hex(0x025807), LV_PART_MAIN);
            lv_obj_set_style_bg_color(guider_ui.Set_cont_4, lv_color_hex(0xffffff), LV_PART_MAIN);
            lv_obj_set_style_border_color(guider_ui.Set_cont_4, lv_color_hex(0x474747), LV_PART_MAIN);
            lv_obj_set_style_bg_color(guider_ui.Set_cont_2, lv_color_hex(0xffffff), LV_PART_MAIN);
            lv_obj_set_style_border_color(guider_ui.Set_cont_2, lv_color_hex(0x474747), LV_PART_MAIN);
            break;
        }
        default:
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void Set_btn_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {

        switch (mode)
        {
        case 0:
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_1, guider_ui.menu_1_del, &guider_ui.Set_del, setup_scr_menu_1, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
            break;
        case 1:
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_2, guider_ui.menu_2_del, &guider_ui.Set_del, setup_scr_menu_2, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
            break;
        case 2:
            ui_load_scr_animation(&guider_ui, &guider_ui.menu_3, guider_ui.menu_3_del, &guider_ui.Set_del, setup_scr_menu_3, LV_SCR_LOAD_ANIM_FADE_ON, 200, 200, true, true);
            break;
        }
        break;
    }
    default:
        break;
    }
}

static void Set_cont_1_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        mode = 0;
        lv_obj_set_style_bg_color(guider_ui.Set_cont_6, lv_color_hex(0xffffff), LV_PART_MAIN);
        lv_obj_set_style_border_color(guider_ui.Set_cont_6, lv_color_hex(0x474747), LV_PART_MAIN);
        lv_obj_set_style_bg_color(guider_ui.Set_cont_4, lv_color_hex(0xffffff), LV_PART_MAIN);
        lv_obj_set_style_border_color(guider_ui.Set_cont_4, lv_color_hex(0x474747), LV_PART_MAIN);
        lv_obj_set_style_bg_color(guider_ui.Set_cont_2, lv_color_hex(0x00ff16), LV_PART_MAIN);
        lv_obj_set_style_border_color(guider_ui.Set_cont_2, lv_color_hex(0x025807), LV_PART_MAIN);
        break;
    }
    default:
        break;
    }
}

static void Set_cont_3_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        mode = 1;
        lv_obj_set_style_bg_color(guider_ui.Set_cont_6, lv_color_hex(0xffffff), LV_PART_MAIN);
        lv_obj_set_style_border_color(guider_ui.Set_cont_6, lv_color_hex(0x3d3d3d), LV_PART_MAIN);
        lv_obj_set_style_bg_color(guider_ui.Set_cont_2, lv_color_hex(0xffffff), LV_PART_MAIN);
        lv_obj_set_style_border_color(guider_ui.Set_cont_2, lv_color_hex(0x474747), LV_PART_MAIN);
        lv_obj_set_style_bg_color(guider_ui.Set_cont_4, lv_color_hex(0x00ff16), LV_PART_MAIN);
        lv_obj_set_style_border_color(guider_ui.Set_cont_4, lv_color_hex(0x025807), LV_PART_MAIN);
        break;
    }
    default:
        break;
    }
}

static void Set_cont_5_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    case LV_EVENT_CLICKED:
    {
        mode = 2;
        lv_obj_set_style_bg_color(guider_ui.Set_cont_6, lv_color_hex(0x00ff16), LV_PART_MAIN);
        lv_obj_set_style_border_color(guider_ui.Set_cont_6, lv_color_hex(0x025807), LV_PART_MAIN);
        lv_obj_set_style_bg_color(guider_ui.Set_cont_4, lv_color_hex(0xffffff), LV_PART_MAIN);
        lv_obj_set_style_border_color(guider_ui.Set_cont_4, lv_color_hex(0x3d3d3d), LV_PART_MAIN);
        lv_obj_set_style_bg_color(guider_ui.Set_cont_2, lv_color_hex(0xffffff), LV_PART_MAIN);
        lv_obj_set_style_border_color(guider_ui.Set_cont_2, lv_color_hex(0x474747), LV_PART_MAIN);
        break;
    }
    default:
        break;
    }
}

void events_init_Set(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Set, Set_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Set_btn_1, Set_btn_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Set_cont_1, Set_cont_1_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Set_cont_3, Set_cont_3_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->Set_cont_5, Set_cont_5_event_handler, LV_EVENT_ALL, ui);
}

static void Message_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code)
    {
    // case LV_EVENT_GESTURE:
    // {
    //     lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    //     switch (dir)
    //     {
    //     case LV_DIR_BOTTOM:
    //         //  case LV_EVENT_LONG_PRESSED:
    //         {
    //             lv_indev_wait_release(lv_indev_get_act());
    //             switch (screen_index)
    //             {
    //             case 0:
    //                 /* code */
    //                 lv_indev_wait_release(lv_indev_get_act());
    //                 ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_1, guider_ui.WatchGiral_1_del, &guider_ui.top_lap_del, setup_scr_WatchGiral_1, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 0, true, true);
    //                 break;
    //             case 1:
    //                 lv_indev_wait_release(lv_indev_get_act());
    //                 ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_2, guider_ui.WatchGiral_2_del, &guider_ui.top_lap_del, setup_scr_WatchGiral_2, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 0, true, true);
    //                 break;
    //             case 2:
    //                 lv_indev_wait_release(lv_indev_get_act());
    //                 ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_3, guider_ui.WatchGiral_3_del, &guider_ui.top_lap_del, setup_scr_WatchGiral_3, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 0, true, true);
    //                 break;
    //             default:
    //                 break;
    //             }
    //             break;
    //         }
    //     default:
    //         break;
    //     }
    //     break;
    // }
    case LV_EVENT_LONG_PRESSED:
    {
        lv_indev_wait_release(lv_indev_get_act());
        switch (screen_index)
        {
        case 0:
            /* code */
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_1, guider_ui.WatchGiral_1_del, &guider_ui.top_lap_del, setup_scr_WatchGiral_1, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 0, true, true);
            break;
        case 1:
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_2, guider_ui.WatchGiral_2_del, &guider_ui.top_lap_del, setup_scr_WatchGiral_2, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 0, true, true);
            break;
        case 2:
            lv_indev_wait_release(lv_indev_get_act());
            ui_load_scr_animation(&guider_ui, &guider_ui.WatchGiral_3, guider_ui.WatchGiral_3_del, &guider_ui.top_lap_del, setup_scr_WatchGiral_3, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 200, 0, true, true);
            break;
        default:
            break;
        }
    }

    default:
        break;
    }
}

void events_init_Message(lv_ui *ui)
{
    lv_obj_add_event_cb(ui->Message, Message_event_handler, LV_EVENT_ALL, ui);
}

void events_init(lv_ui *ui)
{
}
