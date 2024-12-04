#include <Arduino.h>

#include <esp32_smartdisplay.h>
#include <lvgl.h>
#include "ui/ui.h"
#include "ap.h"
#include <esp_lcd_types.h>
#include <esp_lcd_panel_ops.h>

IPAddress my_ip_address;

void setup()
{
#ifdef ARDUINO_USB_CDC_ON_BOOT
    delay(5000);
#endif
    Serial.begin(115200);
    Serial.println("suspensionrt/hub");

    Serial.setDebugOutput(true);
    log_i("Board: %s", BOARD_NAME);
    log_i("CPU: %s rev%d, CPU Freq: %d Mhz, %d core(s)", ESP.getChipModel(), ESP.getChipRevision(), getCpuFrequencyMhz(), ESP.getChipCores());
    log_i("Free heap: %d bytes", ESP.getFreeHeap());
    log_i("Free PSRAM: %d bytes", ESP.getPsramSize());
    log_i("SDK version: %s", ESP.getSdkVersion());

    smartdisplay_init();

    // Un-invert colors
    lv_display_t* display = lv_display_get_default();
    const esp_lcd_panel_handle_t panel_handle = static_cast<esp_lcd_panel_handle_t>(display->user_data);
    esp_lcd_panel_invert_color(panel_handle, false);

    __attribute__((unused)) auto disp = lv_disp_get_default();
    lv_disp_set_rotation(disp, LV_DISPLAY_ROTATION_270);

    ui_init();

    my_ip_address = init_ap();
    char text_buffer[16];
    sprintf(text_buffer, "%d.%d.%d.%d", my_ip_address[0], my_ip_address[1], my_ip_address[2], my_ip_address[3]);
    lv_label_set_text(ui_lblStatus3, text_buffer);
    lv_obj_clear_flag(ui_imgLeftFrontWifi, LV_OBJ_FLAG_HIDDEN);
}

ulong next_millis;
auto lv_last_tick = millis();

void loop()
{
    auto const now = millis();
    if (now > next_millis)
    {
        next_millis = now + 500;

        char text_buffer[32];
        sprintf(text_buffer, "%lu", now);
        lv_label_set_text(ui_lblStatus1, text_buffer);

        float light_level = smartdisplay_lcd_adaptive_brightness_cds();
        sprintf(text_buffer, "%.3f", light_level);
        lv_label_set_text(ui_lblStatus2, text_buffer);
    }

    // Update the ticker
    lv_tick_inc(now - lv_last_tick);
    lv_last_tick = now;

    // Update the UI
    lv_timer_handler();
}
