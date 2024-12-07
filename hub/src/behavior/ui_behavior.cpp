#include "ui_behavior.h"

#include <esp32_smartdisplay.h>

#include "../ui/ui.h"
#include "screen_main.h"

uint8_t currentWheel;

void scrWheel_Loaded(lv_event_t* e) {
    Serial.println("scrWheel loaded");
}

void init_ui_behavior() {
    init_main_screen_behavior();
    lv_obj_add_event_cb(ui_scrWheel, scrWheel_Loaded, LV_EVENT_SCREEN_LOADED, NULL);
}

void ui_behavior_tick(const mstime_t now) {
    main_screen_behavior_tick(now);
}
