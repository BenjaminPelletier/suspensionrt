// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.0
// LVGL version: 9.1.0
// Project name: Hub

#include "../ui.h"

void ui_scrMain_screen_init(void)
{
    ui_scrMain = lv_obj_create(NULL);
    lv_obj_remove_flag(ui_scrMain, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_scrMain, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scrMain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_pnlMain = lv_obj_create(ui_scrMain);
    lv_obj_set_width(ui_pnlMain, lv_pct(95));
    lv_obj_set_height(ui_pnlMain, lv_pct(95));
    lv_obj_set_align(ui_pnlMain, LV_ALIGN_CENTER);
    lv_obj_remove_flag(ui_pnlMain, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_pnlMain, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_pnlMain, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_btnHamburger = lv_button_create(ui_pnlMain);
    lv_obj_set_width(ui_btnHamburger, 32);
    lv_obj_set_height(ui_btnHamburger, 32);
    lv_obj_add_flag(ui_btnHamburger, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_remove_flag(ui_btnHamburger, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ctnrLeftRear = lv_obj_create(ui_pnlMain);
    lv_obj_remove_style_all(ui_ctnrLeftRear);
    lv_obj_set_width(ui_ctnrLeftRear, 56);
    lv_obj_set_height(ui_ctnrLeftRear, 120);
    lv_obj_set_align(ui_ctnrLeftRear, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_remove_flag(ui_ctnrLeftRear, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ctnrLeftRear, lv_color_hex(0xCC2929), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ctnrLeftRear, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ctnrLeftRearGap = lv_obj_create(ui_ctnrLeftRear);
    lv_obj_remove_style_all(ui_ctnrLeftRearGap);
    lv_obj_set_width(ui_ctnrLeftRearGap, lv_pct(100));
    lv_obj_set_height(ui_ctnrLeftRearGap, lv_pct(50));
    lv_obj_set_align(ui_ctnrLeftRearGap, LV_ALIGN_TOP_MID);
    lv_obj_remove_flag(ui_ctnrLeftRearGap, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ctnrLeftRearGap, lv_color_hex(0x29CC29), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ctnrLeftRearGap, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblLeftRear = lv_label_create(ui_ctnrLeftRear);
    lv_obj_set_width(ui_lblLeftRear, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblLeftRear, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblLeftRear, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblLeftRear, "LR");
    lv_obj_set_style_text_color(ui_lblLeftRear, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lblLeftRear, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_lblLeftRear, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_lblLeftRear, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_lblLeftRear, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_lblLeftRear, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_lblLeftRear, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_lblLeftRear, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_imgLeftRearWifi = lv_image_create(ui_ctnrLeftRear);
    lv_image_set_src(ui_imgLeftRearWifi, &ui_img_wifi_png);
    lv_obj_set_width(ui_imgLeftRearWifi, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_imgLeftRearWifi, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_imgLeftRearWifi, 2);
    lv_obj_set_y(ui_imgLeftRearWifi, -2);
    lv_obj_set_align(ui_imgLeftRearWifi, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(ui_imgLeftRearWifi, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_remove_flag(ui_imgLeftRearWifi, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ctnrRightRear = lv_obj_create(ui_pnlMain);
    lv_obj_remove_style_all(ui_ctnrRightRear);
    lv_obj_set_width(ui_ctnrRightRear, 56);
    lv_obj_set_height(ui_ctnrRightRear, 120);
    lv_obj_set_align(ui_ctnrRightRear, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_remove_flag(ui_ctnrRightRear, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ctnrRightRear, lv_color_hex(0xCC2929), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ctnrRightRear, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ctnrRightRearGap = lv_obj_create(ui_ctnrRightRear);
    lv_obj_remove_style_all(ui_ctnrRightRearGap);
    lv_obj_set_width(ui_ctnrRightRearGap, lv_pct(100));
    lv_obj_set_height(ui_ctnrRightRearGap, lv_pct(50));
    lv_obj_set_align(ui_ctnrRightRearGap, LV_ALIGN_TOP_MID);
    lv_obj_remove_flag(ui_ctnrRightRearGap, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ctnrRightRearGap, lv_color_hex(0x29CC29), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ctnrRightRearGap, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblRightRear = lv_label_create(ui_ctnrRightRear);
    lv_obj_set_width(ui_lblRightRear, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblRightRear, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblRightRear, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblRightRear, "RR");
    lv_obj_set_style_text_color(ui_lblRightRear, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lblRightRear, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_lblRightRear, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_lblRightRear, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_lblRightRear, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_lblRightRear, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_lblRightRear, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_lblRightRear, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_imgRightRearWifi = lv_image_create(ui_ctnrRightRear);
    lv_image_set_src(ui_imgRightRearWifi, &ui_img_wifi_png);
    lv_obj_set_width(ui_imgRightRearWifi, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_imgRightRearWifi, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_imgRightRearWifi, -2);
    lv_obj_set_y(ui_imgRightRearWifi, -2);
    lv_obj_set_align(ui_imgRightRearWifi, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(ui_imgRightRearWifi, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_remove_flag(ui_imgRightRearWifi, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ctnrLeftFront = lv_obj_create(ui_pnlMain);
    lv_obj_remove_style_all(ui_ctnrLeftFront);
    lv_obj_set_width(ui_ctnrLeftFront, 56);
    lv_obj_set_height(ui_ctnrLeftFront, 120);
    lv_obj_set_x(ui_ctnrLeftFront, -38);
    lv_obj_set_y(ui_ctnrLeftFront, 0);
    lv_obj_set_align(ui_ctnrLeftFront, LV_ALIGN_TOP_MID);
    lv_obj_remove_flag(ui_ctnrLeftFront, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ctnrLeftFront, lv_color_hex(0xCC2929), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ctnrLeftFront, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ctnrLeftFrontGap = lv_obj_create(ui_ctnrLeftFront);
    lv_obj_remove_style_all(ui_ctnrLeftFrontGap);
    lv_obj_set_width(ui_ctnrLeftFrontGap, lv_pct(100));
    lv_obj_set_height(ui_ctnrLeftFrontGap, lv_pct(50));
    lv_obj_set_align(ui_ctnrLeftFrontGap, LV_ALIGN_TOP_MID);
    lv_obj_remove_flag(ui_ctnrLeftFrontGap, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ctnrLeftFrontGap, lv_color_hex(0x29CC29), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ctnrLeftFrontGap, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblLeftFront = lv_label_create(ui_ctnrLeftFront);
    lv_obj_set_width(ui_lblLeftFront, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblLeftFront, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblLeftFront, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblLeftFront, "LF");
    lv_obj_set_style_text_color(ui_lblLeftFront, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lblLeftFront, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_lblLeftFront, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_lblLeftFront, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_lblLeftFront, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_lblLeftFront, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_lblLeftFront, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_lblLeftFront, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_imgLeftFrontWifi = lv_image_create(ui_ctnrLeftFront);
    lv_image_set_src(ui_imgLeftFrontWifi, &ui_img_wifi_png);
    lv_obj_set_width(ui_imgLeftFrontWifi, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_imgLeftFrontWifi, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_imgLeftFrontWifi, 2);
    lv_obj_set_y(ui_imgLeftFrontWifi, -2);
    lv_obj_set_align(ui_imgLeftFrontWifi, LV_ALIGN_BOTTOM_LEFT);
    lv_obj_add_flag(ui_imgLeftFrontWifi, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_remove_flag(ui_imgLeftFrontWifi, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_ctnrRightFront = lv_obj_create(ui_pnlMain);
    lv_obj_remove_style_all(ui_ctnrRightFront);
    lv_obj_set_width(ui_ctnrRightFront, 56);
    lv_obj_set_height(ui_ctnrRightFront, 120);
    lv_obj_set_x(ui_ctnrRightFront, 38);
    lv_obj_set_y(ui_ctnrRightFront, 0);
    lv_obj_set_align(ui_ctnrRightFront, LV_ALIGN_TOP_MID);
    lv_obj_remove_flag(ui_ctnrRightFront, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ctnrRightFront, lv_color_hex(0xCC2929), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ctnrRightFront, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_ctnrRightFrontGap = lv_obj_create(ui_ctnrRightFront);
    lv_obj_remove_style_all(ui_ctnrRightFrontGap);
    lv_obj_set_width(ui_ctnrRightFrontGap, lv_pct(100));
    lv_obj_set_height(ui_ctnrRightFrontGap, lv_pct(50));
    lv_obj_set_align(ui_ctnrRightFrontGap, LV_ALIGN_TOP_MID);
    lv_obj_remove_flag(ui_ctnrRightFrontGap, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_ctnrRightFrontGap, lv_color_hex(0x29CC29), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_ctnrRightFrontGap, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblRightFront = lv_label_create(ui_ctnrRightFront);
    lv_obj_set_width(ui_lblRightFront, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblRightFront, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblRightFront, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblRightFront, "RF");
    lv_obj_set_style_text_color(ui_lblRightFront, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lblRightFront, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_lblRightFront, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_lblRightFront, 128, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_lblRightFront, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_lblRightFront, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_lblRightFront, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_lblRightFront, 2, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_imgRightFrontWifi = lv_image_create(ui_ctnrRightFront);
    lv_image_set_src(ui_imgRightFrontWifi, &ui_img_wifi_png);
    lv_obj_set_width(ui_imgRightFrontWifi, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_imgRightFrontWifi, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_imgRightFrontWifi, -2);
    lv_obj_set_y(ui_imgRightFrontWifi, -2);
    lv_obj_set_align(ui_imgRightFrontWifi, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(ui_imgRightFrontWifi, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_remove_flag(ui_imgRightFrontWifi, LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_lblStatus1 = lv_label_create(ui_pnlMain);
    lv_obj_set_width(ui_lblStatus1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblStatus1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_lblStatus1, 0);
    lv_obj_set_y(ui_lblStatus1, -40);
    lv_obj_set_align(ui_lblStatus1, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_lblStatus1, "Status1");
    lv_obj_set_style_text_color(ui_lblStatus1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lblStatus1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblStatus2 = lv_label_create(ui_pnlMain);
    lv_obj_set_width(ui_lblStatus2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblStatus2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_lblStatus2, 0);
    lv_obj_set_y(ui_lblStatus2, -20);
    lv_obj_set_align(ui_lblStatus2, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_lblStatus2, "Status2");
    lv_obj_set_style_text_color(ui_lblStatus2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lblStatus2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblStatus3 = lv_label_create(ui_pnlMain);
    lv_obj_set_width(ui_lblStatus3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblStatus3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_lblStatus3, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_lblStatus3, "Status3");
    lv_obj_set_style_text_color(ui_lblStatus3, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lblStatus3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


}
