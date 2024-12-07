#include "ui_behavior.h"

#include <esp32_smartdisplay.h>

#include "../ui/ui.h"
#include "screen_main.h"
#include "screen_wheel.h"

void init_ui_behavior() {
    init_main_screen_behavior();
    init_wheel_screen_behavior();
}

void ui_behavior_tick(const mstime_t now) {
    lv_obj_t* active_screen = lv_screen_active();
    if (active_screen == ui_scrMain) {
        main_screen_behavior_tick(now);
    } else if (active_screen == ui_scrWheel) {
        wheel_screen_behavior_tick(now);
    }
}
