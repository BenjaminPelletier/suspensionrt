// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 9.1.0
// Project name: Hub

#include "../ui.h"

void ui_scrWheel_screen_init(void)
{
    ui_scrWheel = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_scrWheel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_scrWheel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scrWheel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_pnlWheel = lv_obj_create(ui_scrWheel);
    lv_obj_set_width(ui_pnlWheel, lv_pct(95));
    lv_obj_set_height(ui_pnlWheel, lv_pct(95));
    lv_obj_set_align(ui_pnlWheel, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_pnlWheel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_pnlWheel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_pnlWheel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_btnWheelBack = lv_button_create(ui_pnlWheel);
    lv_obj_set_width(ui_btnWheelBack, 36);
    lv_obj_set_height(ui_btnWheelBack, 36);
    lv_obj_add_flag(ui_btnWheelBack, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_btnWheelBack, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ddSelectedWheel = lv_dropdown_create(ui_pnlWheel);
    lv_dropdown_set_options(ui_ddSelectedWheel, "Rear left\nFront left\nFront right\nRear right");
    lv_obj_set_width(ui_ddSelectedWheel, 120);
    lv_obj_set_height(ui_ddSelectedWheel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ddSelectedWheel, 50);
    lv_obj_set_y(ui_ddSelectedWheel, 0);
    lv_obj_add_flag(ui_ddSelectedWheel, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags



    ui_taCompressed = lv_textarea_create(ui_pnlWheel);
    lv_obj_set_width(ui_taCompressed, 60);
    lv_obj_set_height(ui_taCompressed, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_taCompressed, LV_ALIGN_TOP_RIGHT);
    if("0123456789" == "") lv_textarea_set_accepted_chars(ui_taCompressed, NULL);
    else lv_textarea_set_accepted_chars(ui_taCompressed, "0123456789");
    lv_textarea_set_max_length(ui_taCompressed, 4);
    lv_textarea_set_text(ui_taCompressed, "0");
    lv_textarea_set_placeholder_text(ui_taCompressed, "0");
    lv_textarea_set_one_line(ui_taCompressed, true);



    ui_ctnrCompressionHeight = lv_obj_create(ui_pnlWheel);
    lv_obj_remove_style_all(ui_ctnrCompressionHeight);
    lv_obj_set_width(ui_ctnrCompressionHeight, 60);
    lv_obj_set_height(ui_ctnrCompressionHeight, 110);
    lv_obj_set_align(ui_ctnrCompressionHeight, LV_ALIGN_RIGHT_MID);
    lv_obj_remove_flag(ui_ctnrCompressionHeight, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ctnrCompressionHeight, lv_color_hex(0xCC2929), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ctnrCompressionHeight, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ctnrGap = lv_obj_create(ui_ctnrCompressionHeight);
    lv_obj_remove_style_all(ui_ctnrGap);
    lv_obj_set_width(ui_ctnrGap, lv_pct(100));
    lv_obj_set_height(ui_ctnrGap, lv_pct(50));
    lv_obj_set_align(ui_ctnrGap, LV_ALIGN_TOP_MID);
    lv_obj_remove_flag(ui_ctnrGap, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ctnrGap, lv_color_hex(0x29CC29), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ctnrGap, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblGap = lv_label_create(ui_ctnrCompressionHeight);
    lv_obj_set_width(ui_lblGap, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblGap, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblGap, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblGap, "RR");
    lv_obj_set_style_text_color(ui_lblGap, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lblGap, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_lblGap, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_lblGap, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_lblGap, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_lblGap, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_lblGap, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_lblGap, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_taExtended = lv_textarea_create(ui_pnlWheel);
    lv_obj_set_width(ui_taExtended, 60);
    lv_obj_set_height(ui_taExtended, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_taExtended, LV_ALIGN_BOTTOM_RIGHT);
    if("0123456789" == "") lv_textarea_set_accepted_chars(ui_taExtended, NULL);
    else lv_textarea_set_accepted_chars(ui_taExtended, "0123456789");
    lv_textarea_set_max_length(ui_taExtended, 4);
    lv_textarea_set_text(ui_taExtended, "500	");
    lv_textarea_set_placeholder_text(ui_taExtended, "500");
    lv_textarea_set_one_line(ui_taExtended, true);



    ui_chkSatellite1 = lv_checkbox_create(ui_pnlWheel);
    lv_checkbox_set_text(ui_chkSatellite1, "Satellite 1");
    lv_obj_set_width(ui_chkSatellite1, 200);
    lv_obj_set_height(ui_chkSatellite1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_chkSatellite1, 0);
    lv_obj_set_y(ui_chkSatellite1, 46);
    lv_obj_add_flag(ui_chkSatellite1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_set_style_text_color(ui_chkSatellite1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_chkSatellite1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblSatellite1 = lv_label_create(ui_chkSatellite1);
    lv_obj_set_width(ui_lblSatellite1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblSatellite1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblSatellite1, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_lblSatellite1, "???");

    ui_chkSatellite2 = lv_checkbox_create(ui_pnlWheel);
    lv_checkbox_set_text(ui_chkSatellite2, "Satellite 2");
    lv_obj_set_width(ui_chkSatellite2, 200);
    lv_obj_set_height(ui_chkSatellite2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_chkSatellite2, 0);
    lv_obj_set_y(ui_chkSatellite2, 72);
    lv_obj_add_flag(ui_chkSatellite2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_set_style_text_color(ui_chkSatellite2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_chkSatellite2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblSatellite2 = lv_label_create(ui_chkSatellite2);
    lv_obj_set_width(ui_lblSatellite2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblSatellite2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblSatellite2, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_lblSatellite2, "???");

    ui_chkSatellite3 = lv_checkbox_create(ui_pnlWheel);
    lv_checkbox_set_text(ui_chkSatellite3, "Satellite 3");
    lv_obj_set_width(ui_chkSatellite3, 200);
    lv_obj_set_height(ui_chkSatellite3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_chkSatellite3, 0);
    lv_obj_set_y(ui_chkSatellite3, 98);
    lv_obj_add_flag(ui_chkSatellite3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_set_style_text_color(ui_chkSatellite3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_chkSatellite3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblSatellite3 = lv_label_create(ui_chkSatellite3);
    lv_obj_set_width(ui_lblSatellite3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblSatellite3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblSatellite3, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_lblSatellite3, "???");

    ui_chkSatellite4 = lv_checkbox_create(ui_pnlWheel);
    lv_checkbox_set_text(ui_chkSatellite4, "Satellite 4");
    lv_obj_set_width(ui_chkSatellite4, 200);
    lv_obj_set_height(ui_chkSatellite4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_chkSatellite4, 0);
    lv_obj_set_y(ui_chkSatellite4, 124);
    lv_obj_add_flag(ui_chkSatellite4, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_set_style_text_color(ui_chkSatellite4, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_chkSatellite4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblSatellite4 = lv_label_create(ui_chkSatellite4);
    lv_obj_set_width(ui_lblSatellite4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblSatellite4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblSatellite4, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_lblSatellite4, "???");


}
