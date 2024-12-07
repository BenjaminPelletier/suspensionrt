#include <Arduino.h>

#include <esp32_smartdisplay.h>
#include <lvgl.h>
#include <esp_lcd_types.h>
#include <esp_lcd_panel_ops.h>
#include "common.h"
#include "ui/ui.h"
#include "comms/ap.h"
#include "comms/server/server.h"
#include "comms/udp.h"
#include "behavior/ui_behavior.h"

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

    // Set rotation appropriately
    __attribute__((unused)) auto disp = lv_disp_get_default();
    lv_disp_set_rotation(disp, LV_DISPLAY_ROTATION_270);

    ui_init();
    init_ui_behavior();

    init_ap();

    IPAddress ip = get_my_ip_address();
    char text_buffer[16];
    sprintf(text_buffer, "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
    lv_label_set_text(ui_lblStatus3, text_buffer);

    init_server();

    init_udp();
}

auto lv_last_tick = millis();

void loop()
{
    mstime_t const now = millis();

    // Apply changes to UI
    ui_behavior_tick(now);

    // Update the ticker
    lv_tick_inc(now - lv_last_tick);
    lv_last_tick = now;

    // Update the UI
    lv_timer_handler();

    // Handle any webserver tasks
    server_tick();
}
