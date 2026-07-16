/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"


typedef struct
{
  
	lv_obj_t *WatchGiral_1;
	bool WatchGiral_1_del;
	lv_obj_t *WatchGiral_1_label_1;
	lv_obj_t *WatchGiral_1_arc_1;
	lv_obj_t *WatchGiral_1_arc_2;
	lv_obj_t *WatchGiral_1_arc_3;
	lv_obj_t *WatchGiral_1_arc_4;
	lv_obj_t *WatchGiral_1_img_1;
	lv_obj_t *WatchGiral_1_img_2;
	lv_obj_t *WatchGiral_1_img_3;
	lv_obj_t *WatchGiral_1_img_4;
	lv_obj_t *WatchGiral_1_label_2;
	lv_obj_t *WatchGiral_1_img_5;
	lv_obj_t *WatchGiral_1_label_3;
	lv_obj_t *WatchGiral_1_label_4;
	lv_obj_t *WatchGiral_1_label_5;
	lv_obj_t *WatchGiral_1_label_6;
	lv_obj_t *WatchGiral_1_label_7;
	lv_obj_t *WatchGiral_1_label_8;
	lv_obj_t *WatchGiral_1_label_9;
	lv_obj_t *WatchGiral_2;
	bool WatchGiral_2_del;
	lv_obj_t *WatchGiral_2_cont_1;
	lv_obj_t *WatchGiral_2_label_1;
	lv_obj_t *WatchGiral_2_label_2;
	lv_obj_t *WatchGiral_2_img_1;
	lv_obj_t *WatchGiral_2_img_2;
	lv_obj_t *WatchGiral_3;
	bool WatchGiral_3_del;
	lv_obj_t *WatchGiral_3_analog_clock_1;
	lv_obj_t *WatchGiral_3_cont_1;
	lv_obj_t *WatchGiral_3_cont_2;
	lv_obj_t *WatchGiral_3_label_1;
	lv_obj_t *WatchGiral_3_label_2;
	lv_obj_t *WatchGiral_3_img_7;
	lv_obj_t *WatchGiral_3_img_4;
	lv_obj_t *WatchGiral_3_img_5;
	lv_obj_t *WatchGiral_3_img_6;
	lv_obj_t *top_lap;
	bool top_lap_del;
	lv_obj_t *top_lap_slider_1;
	lv_obj_t *top_lap_cont_1;
	lv_obj_t *top_lap_img_1;
	lv_obj_t *top_lap_cont_2;
	lv_obj_t *top_lap_img_2;
	lv_obj_t *top_lap_cont_3;
	lv_obj_t *top_lap_img_3;
	lv_obj_t *top_lap_cont_4;
	lv_obj_t *top_lap_img_4;
	lv_obj_t *top_lap_label_1;
	lv_obj_t *top_lap_img_5;
	lv_obj_t *menu_1;
	bool menu_1_del;
	lv_obj_t *menu_1_cont_1;
	lv_obj_t *menu_1_cont_2;
	lv_obj_t *menu_1_img_1;
	lv_obj_t *menu_1_label_2;
	lv_obj_t *menu_1_cont_3;
	lv_obj_t *menu_1_img_2;
	lv_obj_t *menu_1_label_3;
	lv_obj_t *menu_1_cont_4;
	lv_obj_t *menu_1_img_3;
	lv_obj_t *menu_1_label_4;
	lv_obj_t *menu_1_cont_5;
	lv_obj_t *menu_1_img_4;
	lv_obj_t *menu_1_label_5;
	lv_obj_t *menu_1_cont_6;
	lv_obj_t *menu_1_img_5;
	lv_obj_t *menu_1_label_6;
	lv_obj_t *menu_1_cont_7;
	lv_obj_t *menu_1_img_6;
	lv_obj_t *menu_1_label_7;
	lv_obj_t *menu_1_cont_8;
	lv_obj_t *menu_1_img_7;
	lv_obj_t *menu_1_label_8;
	lv_obj_t *menu_1_btn_1;
	lv_obj_t *menu_1_btn_1_label;
	lv_obj_t *menu_2;
	bool menu_2_del;
	lv_obj_t *menu_2_cont_1;
	lv_obj_t *menu_2_cont_8;
	lv_obj_t *menu_2_img_7;
	lv_obj_t *menu_2_label_7;
	lv_obj_t *menu_2_cont_7;
	lv_obj_t *menu_2_img_6;
	lv_obj_t *menu_2_label_6;
	lv_obj_t *menu_2_cont_6;
	lv_obj_t *menu_2_img_5;
	lv_obj_t *menu_2_label_5;
	lv_obj_t *menu_2_cont_5;
	lv_obj_t *menu_2_img_4;
	lv_obj_t *menu_2_label_4;
	lv_obj_t *menu_2_cont_4;
	lv_obj_t *menu_2_img_3;
	lv_obj_t *menu_2_label_3;
	lv_obj_t *menu_2_cont_3;
	lv_obj_t *menu_2_img_2;
	lv_obj_t *menu_2_label_2;
	lv_obj_t *menu_2_cont_2;
	lv_obj_t *menu_2_img_1;
	lv_obj_t *menu_2_label_1;
	lv_obj_t *menu_2_btn_1;
	lv_obj_t *menu_2_btn_1_label;
	lv_obj_t *menu_3;
	bool menu_3_del;
	lv_obj_t *menu_3_btn_1;
	lv_obj_t *menu_3_btn_1_label;
	lv_obj_t *menu_3_img_2;
	lv_obj_t *menu_3_label_1;
	lv_obj_t *menu_3_img_3;
	lv_obj_t *menu_3_img_4;
	lv_obj_t *menu_3_img_5;
	lv_obj_t *menu_3_img_6;
	lv_obj_t *menu_3_img_7;
	lv_obj_t *menu_3_img_8;
	lv_obj_t *menu_3_cont_1;
	// lv_obj_t *menu_3_btn_2;
	// lv_obj_t *menu_3_btn_2_label;
	lv_obj_t *menu_3_img_9;
	lv_obj_t *Heart;
	bool Heart_del;
	lv_obj_t *Heart_btn_1;
	lv_obj_t *Heart_btn_1_label;
	lv_obj_t *Heart_img_1;
	lv_obj_t *Heart_label_1;
	lv_obj_t *Heart_slider_1;
	lv_obj_t *Heart_img_2;
	lv_obj_t *Heart_label_2;
	lv_obj_t *Electronicfence;
	bool Electronicfence_del;
	lv_obj_t *Electronicfence_btn_1;
	lv_obj_t *Electronicfence_btn_1_label;
	lv_obj_t *Electronicfence_cont_1;
	lv_obj_t *Electronicfence_cont_2;
	lv_obj_t *Electronicfence_cont_3;
	lv_obj_t *Electronicfence_img_1;
	lv_obj_t *Electronicfence_label_1;
	lv_obj_t *Electronicfence_img_2;
	lv_obj_t *NFCCard;
	bool NFCCard_del;
	lv_obj_t *NFCCard_btn_1;
	lv_obj_t *NFCCard_btn_1_label;
	lv_obj_t *NFCCard_img_1;
	lv_obj_t *NFCCard_label_1;
	lv_obj_t *NFCCard_label_2;
	lv_obj_t *NFCCard_cont_1;
	lv_obj_t *NFCCard_label_3;
	lv_obj_t *NFCCard_label_4;
	lv_obj_t *NFCCard_label_5;
	lv_obj_t *NFCCard_label_6;
	lv_obj_t *NFCCard_label_7;
	lv_obj_t *NFCCard_label_8;
	lv_obj_t *QrCode;
	bool QrCode_del;
	lv_obj_t *QrCode_btn_1;
	lv_obj_t *QrCode_btn_1_label;
	lv_obj_t *QrCode_img_1;
	lv_obj_t *QrCode_cont_1;
	lv_obj_t *QrCode_label_2;
	lv_obj_t *QrCode_label_1;
	lv_obj_t *QrCode_btn_2;
	lv_obj_t *QrCode_btn_2_label;
	lv_obj_t *Systeamupdate;
	bool Systeamupdate_del;
	lv_obj_t *Systeamupdate_btn_1;
	lv_obj_t *Systeamupdate_btn_1_label;
	lv_obj_t *Systeamupdate_img_1;
	lv_obj_t *Systeamupdate_label_1;
	lv_obj_t *Systeamupdate_label_2;
	lv_obj_t *Systeamupdate_btn_2;
	lv_obj_t *Systeamupdate_btn_2_label;
	lv_obj_t *Systeamupdate_cheak;
	bool Systeamupdate_cheak_del;
	lv_obj_t *Systeamupdate_cheak_label_1;
	lv_obj_t *Systeamupdate_cheak_label_2;
	lv_obj_t *Systeamupdate_cheak_label_3;
	lv_obj_t *Systeamupdate_cheak_label_4;
	lv_obj_t *Systeamupdate_cheak_label_5;
	lv_obj_t *Systeamupdate_cheak_label_6;
	lv_obj_t *Systeamupdate_cheak_label_7;
	lv_obj_t *Systeamupdate_cheak_btn_1;
	lv_obj_t *Systeamupdate_cheak_btn_1_label;
	lv_obj_t *Systeamupdate_cheak_btn_2;
	lv_obj_t *Systeamupdate_cheak_btn_2_label;
	lv_obj_t *Set;
	bool Set_del;
	lv_obj_t *Set_btn_1;
	lv_obj_t *Set_btn_1_label;
	lv_obj_t *Set_cont_1;
	lv_obj_t *Set_cont_2;
	lv_obj_t *Set_label_1;
	lv_obj_t *Set_cont_3;
	lv_obj_t *Set_cont_4;
	lv_obj_t *Set_label_2;
	lv_obj_t *Set_cont_5;
	lv_obj_t *Set_cont_6;
	lv_obj_t *Set_label_3;
	lv_obj_t *Message;
	bool Message_del;
	lv_obj_t *Message_img_1;
	lv_obj_t *Message_img_2;
	lv_obj_t *Message_cont_1;
	lv_obj_t *Message_cont_2;
	lv_obj_t *Message_cont_3;
	lv_obj_t *Message_cont_4;
	lv_obj_t *Message_cont_5;
	lv_obj_t *Message_img_4;
	lv_obj_t *Message_img_5;
	lv_obj_t *Message_img_6;
	lv_obj_t *Message_img_7;
	lv_obj_t *Message_img_8;
	lv_obj_t *Message_label_1;
	lv_obj_t *Message_label_2;
	lv_obj_t *Message_label_3;
	lv_obj_t *Message_label_4;
	lv_obj_t *error;
	bool error_del;
	lv_obj_t *error_img_1;
	lv_obj_t *error_label_1;
	lv_obj_t *error_cont_1;
	lv_obj_t *error_label_2;
	lv_obj_t *error_label_3;
	lv_obj_t *error_label_4;
	lv_obj_t *error_label_5;
	lv_obj_t *error_label_6;
}lv_ui;



typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_animation(void * var, int32_t duration, int32_t delay, int32_t start_value, int32_t end_value, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_exec_xcb_t exec_cb, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);


void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);

void init_keyboard(lv_ui *ui);

extern lv_ui guider_ui;


void setup_scr_WatchGiral_1(lv_ui *ui);
void setup_scr_WatchGiral_2(lv_ui *ui);
void setup_scr_WatchGiral_3(lv_ui *ui);
void setup_scr_top_lap(lv_ui *ui);
void setup_scr_menu_1(lv_ui *ui);
void setup_scr_menu_2(lv_ui *ui);
void setup_scr_menu_3(lv_ui *ui);
void setup_scr_Heart(lv_ui *ui);
void setup_scr_Electronicfence(lv_ui *ui);
void setup_scr_NFCCard(lv_ui *ui);
void setup_scr_QrCode(lv_ui *ui);
void setup_scr_Systeamupdate(lv_ui *ui);
void setup_scr_Systeamupdate_cheak(lv_ui *ui);
void setup_scr_Set(lv_ui *ui);
void setup_scr_Message(lv_ui *ui);
void setup_scr_error(lv_ui *ui);
void test_screen();
// void setup_scr_screen_1(lv_ui *ui);


// #define MAX_ARRAY_SIZE   20000 
// extern uint8_t lvgl_data[MAX_ARRAY_SIZE];

LV_IMG_DECLARE(_heart16x16_alpha_16x16);
LV_IMG_DECLARE(_wather16x16_alpha_16x16);
LV_IMG_DECLARE(_foot16x16_alpha_16x16);
LV_IMG_DECLARE(_KLL16x16_alpha_16x16);
LV_IMG_DECLARE(_sheshidu_alpha_10x10);
LV_IMG_DECLARE(_wtime_30x50);
LV_IMG_DECLARE(_M_50x50);
LV_IMG_DECLARE(_biaopan1_100x100);
LV_IMG_DECLARE(_time_alpha_40x5);
LV_IMG_DECLARE(_fen_alpha_70x5);
LV_IMG_DECLARE(_watchdight1_alpha_60x60);
LV_IMG_DECLARE(_watchdight3_alpha_60x60);
LV_IMG_DECLARE(_watchdight2_alpha_60x60);
LV_IMG_DECLARE(_Ellipse_40x40);
LV_IMG_DECLARE(_Stime_alpha_16x8);
LV_IMG_DECLARE(_Sfen_alpha_21x6);

LV_IMG_DECLARE(_liangdu_40x40);
LV_IMG_DECLARE(_BIGHeart_alpha_46x43);
LV_IMG_DECLARE(_BT32_alpha_32x32);
LV_IMG_DECLARE(_location_alpha_32x32);
LV_IMG_DECLARE(_taiwan_alpha_32x32);
LV_IMG_DECLARE(_nfc_alpha_32x32);
LV_IMG_DECLARE(_power_hight_alpha_32x32);
LV_IMG_DECLARE(_heart32x32_alpha_32x32);
LV_IMG_DECLARE(_NFC32x32_alpha_32x32);
LV_IMG_DECLARE(_logo_100x100);
LV_IMG_DECLARE(_weater32x32_alpha_32x32);
LV_IMG_DECLARE(_set32x32_alpha_32x32);
LV_IMG_DECLARE(_syteam32x32_alpha_32x32);
LV_IMG_DECLARE(_set32x32_alpha_32x32);
LV_IMG_DECLARE(_heart32x32_alpha_32x32);
LV_IMG_DECLARE(_set32x32_alpha_32x32);

LV_IMG_DECLARE(_location32x32_alpha_32x32);
LV_IMG_DECLARE(_qrcode32x32_alpha_32x32);


LV_IMG_DECLARE(_location20x20_alpha_20x20);
LV_IMG_DECLARE(_location32x32_alpha_16x16);

LV_IMG_DECLARE(_syteam32x32_alpha_32x32);
LV_IMG_DECLARE(_Frame_50x50);
LV_IMG_DECLARE(_arw_alpha_49x40);
LV_IMG_DECLARE(_heart32x32_alpha_32x32);
LV_IMG_DECLARE(_tiwen_alpha_16x16);
LV_IMG_DECLARE(_pa_alpha_16x16);
LV_IMG_DECLARE(_error_alpha_48x48);

LV_FONT_DECLARE(lv_customer_font_interttf_24)
LV_FONT_DECLARE(lv_customer_font_alimama_16)
LV_FONT_DECLARE(lv_customer_font_interttf_10)
LV_FONT_DECLARE(lv_customer_font_interttf_82)
LV_FONT_DECLARE(lv_customer_font_alimama_36)
LV_FONT_DECLARE(lv_customer_font_digitaldreamfatnarrow_36)
LV_FONT_DECLARE(lv_customer_font_alimama_12)
LV_FONT_DECLARE(lv_customer_font_interttf_16)


#ifdef __cplusplus
}
#endif
#endif
