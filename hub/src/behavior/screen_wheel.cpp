#include "screen_wheel.h"

#include <Arduino.h>
#include <lvgl.h>
#include "intrascreen.h"
#include "../persistence.h"
#include "../ui/ui.h"
#include "../wheels.h"

const uint8_t MAX_SATELLITES = 4;

struct SatelliteUIElements {
    lv_obj_t* chkSatellite;
    lv_obj_t* lblSatellite;
};

struct SatelliteUIState {
    bool toggle;
};

SatelliteUIElements satellite_ui_elements[MAX_SATELLITES];
SatelliteUIState satellite_ui_state[MAX_SATELLITES];

static uint8_t ui_senders[MAX_SATELLITES] = {0, 1, 2, 3};

lv_obj_t* btnmtxKeypad;
lv_obj_t* taSelected = nullptr;

void ta_Focused(lv_event_t* e) {
    Serial.println("ta_Focused");
    taSelected = (lv_obj_t*)lv_event_get_user_data(e);

    lv_obj_update_flag(btnmtxKeypad, LV_OBJ_FLAG_HIDDEN, false);

    lv_textarea_set_text_selection(taSelected, true);
    length_t n = strlen(lv_textarea_get_text(taSelected));
    lv_obj_t* ta_label = lv_textarea_get_label(taSelected);
    lv_label_set_text_selection_start(ta_label, 0);
    lv_label_set_text_selection_end(ta_label, n);
    lv_textarea_set_text_selection(taSelected, true);

    Serial.print("Selected 0 to "); Serial.println(n);
}

void ta_Defocused(lv_event_t* e) {
    Serial.println("ta_Defocused");
    lv_obj_t* ta = (lv_obj_t*)lv_event_get_user_data(e);

    Wheel* wheel = get_wheel(current_wheel);
    uint16_t dist = 0;
    if (ta == ui_taCompressed) {
        dist = wheel->fully_compressed_distance;
    } else if (ta == ui_taExtended) {
        dist = wheel->fully_extended_distance;
    }
    lv_textarea_set_text_selection(ta, false);
    char text_buffer[5];
    lv_textarea_set_text(ta, itoa(dist, text_buffer, 10));

    taSelected = nullptr;
    lv_obj_update_flag(btnmtxKeypad, LV_OBJ_FLAG_HIDDEN, true);
}

void btnmtxKeypad_Click(lv_event_t * e)
{
    if (taSelected == nullptr) {
        return;  // Should never happen, but just to be safe
    }

    const char* txt = lv_buttonmatrix_get_button_text(btnmtxKeypad, lv_buttonmatrix_get_selected_button(btnmtxKeypad));

    if(lv_strcmp(txt, LV_SYMBOL_BACKSPACE) == 0) lv_textarea_delete_char(taSelected);
    else if(lv_strcmp(txt, LV_SYMBOL_NEW_LINE) == 0) lv_obj_send_event(taSelected, LV_EVENT_READY, NULL);
    else lv_textarea_add_text(taSelected, txt);
}

void ta_Confirm(lv_event_t* e) {
    Serial.println("ta_Confirm");
    lv_obj_t* ta = (lv_obj_t*)lv_event_get_user_data(e);

    Wheel* wheel = get_wheel(current_wheel);
    if (ta == ui_taCompressed) {
        wheel->fully_compressed_distance = atoi(lv_textarea_get_text(ui_taCompressed));
    } else if (ta == ui_taExtended) {
        wheel->fully_extended_distance = atoi(lv_textarea_get_text(ui_taExtended));
    } else if (ta == nullptr) {
        return;  // Should never happen, but just to be safe
    } else {
        Serial.println("???");
    }
    store_wheel_settings();

    lv_obj_remove_state(ta, LV_STATE_FOCUSED);
    ta_Defocused(e);  // TODO: Fix (https://forum.lvgl.io/t/19260)
}

void set_selected_wheel(uint8_t w) {
    lv_dropdown_set_selected(ui_ddSelectedWheel, w);
    Wheel* wheel = get_wheel(w);
    if (wheel != nullptr) {
        current_wheel = w;
        for (uint8_t s = 0; s < MAX_SATELLITES; s++) {
            Satellite* satellite = get_satellite_by_index(s);
            if (wheel->satellite == satellite) {
                lv_obj_add_state(satellite_ui_elements[s].chkSatellite, LV_STATE_CHECKED);
            } else {
                lv_obj_remove_state(satellite_ui_elements[s].chkSatellite, LV_STATE_CHECKED);
            }
        }
        
        char text_buffer[5];
        lv_textarea_set_text(ui_taCompressed, itoa(wheel->fully_compressed_distance, text_buffer, 10));
        lv_textarea_set_text(ui_taExtended, itoa(wheel->fully_extended_distance, text_buffer, 10));
    }
}

void scrWheel_Loaded(lv_event_t* e) {
    for (uint8_t s = 0; s < MAX_SATELLITES; s++) {
        Satellite* satellite = get_satellite_by_index(s);
        lv_obj_update_flag(satellite_ui_elements[s].chkSatellite, LV_OBJ_FLAG_HIDDEN, satellite == nullptr);
        if (satellite != nullptr) {
            lv_checkbox_set_text(satellite_ui_elements[s].chkSatellite, satellite->id);
        }
    }

    btnmtxKeypad = lv_buttonmatrix_create(lv_screen_active());
    lv_obj_update_flag(btnmtxKeypad, LV_OBJ_FLAG_HIDDEN, true);
    lv_obj_set_size(btnmtxKeypad, 200, 240);
    lv_obj_align(btnmtxKeypad, LV_ALIGN_LEFT_MID, 0, 0);
    lv_obj_add_event_cb(btnmtxKeypad, btnmtxKeypad_Click, LV_EVENT_VALUE_CHANGED, NULL);
    lv_obj_remove_flag(btnmtxKeypad, LV_OBJ_FLAG_CLICK_FOCUSABLE);  // Keep the text area focused on button clicks
    lv_buttonmatrix_set_map(btnmtxKeypad, BUTTON_MAP_NUMERIC);

    lv_obj_add_event_cb(ui_taCompressed, ta_Confirm, LV_EVENT_READY, ui_taCompressed);
    lv_obj_add_event_cb(ui_taCompressed, ta_Focused, LV_EVENT_FOCUSED, ui_taCompressed);
    lv_obj_add_event_cb(ui_taCompressed, ta_Defocused, LV_EVENT_DEFOCUSED, ui_taCompressed);

    lv_obj_add_event_cb(ui_taExtended, ta_Confirm, LV_EVENT_READY, ui_taExtended);
    lv_obj_add_event_cb(ui_taExtended, ta_Focused, LV_EVENT_FOCUSED, ui_taExtended);
    lv_obj_add_event_cb(ui_taExtended, ta_Defocused, LV_EVENT_DEFOCUSED, ui_taExtended);

    set_selected_wheel(current_wheel);
}

void btnWheelBack_Click(lv_event_t* e) {
    lv_disp_load_scr(ui_scrMain);
}

void ddSelectedWheel_ValueChanged(lv_event_t* e) {
    uint32_t index = lv_dropdown_get_selected(ui_ddSelectedWheel);
    Wheel* wheel = get_wheel(index);
    if (wheel != nullptr) {
        set_selected_wheel(index);
    }
}

void chkSatellite_ValueChanged(lv_event_t* e) {
    uint8_t satellite_index = *(uint8_t*)lv_event_get_user_data(e);
    Satellite* satellite = get_satellite_by_index(satellite_index);
    if (satellite == nullptr) {
        // Should not happen
        Serial.println("Null satellite found in chkSatellite_ValueChanged!");
        return;
    }
    Wheel* wheel = get_wheel(current_wheel);
    wheel->satellite = satellite;
    strncpy(wheel->last_satellite_id, satellite->id, MAX_SATELLITE_ID_LENGTH);
    store_wheel_settings();
    for (uint8_t s = 0; s < MAX_SATELLITES; s++) {
        if (s == satellite_index) {
            lv_obj_add_state(satellite_ui_elements[s].chkSatellite, LV_STATE_CHECKED);
        } else {
            lv_obj_remove_state(satellite_ui_elements[s].chkSatellite, LV_STATE_CHECKED);
        }
    }
}

void init_wheel_screen_behavior() {
    satellite_ui_elements[0] = {
        .chkSatellite = ui_chkSatellite1,
        .lblSatellite = ui_lblSatellite1,
    };
    satellite_ui_elements[1] = {
        .chkSatellite = ui_chkSatellite2,
        .lblSatellite = ui_lblSatellite2,
    };
    satellite_ui_elements[2] = {
        .chkSatellite = ui_chkSatellite3,
        .lblSatellite = ui_lblSatellite3,
    };
    satellite_ui_elements[3] = {
        .chkSatellite = ui_chkSatellite4,
        .lblSatellite = ui_lblSatellite4,
    };
    lv_obj_add_event_cb(ui_scrWheel, scrWheel_Loaded, LV_EVENT_SCREEN_LOADED, NULL);
    lv_obj_add_event_cb(ui_btnWheelBack, btnWheelBack_Click, LV_EVENT_CLICKED, NULL);
    for (uint8_t s = 0; s < MAX_SATELLITES; s++) {
        lv_obj_add_event_cb(satellite_ui_elements[s].chkSatellite, chkSatellite_ValueChanged, LV_EVENT_VALUE_CHANGED, (void*)&ui_senders[s]);
    }
    lv_obj_add_event_cb(ui_ddSelectedWheel, ddSelectedWheel_ValueChanged, LV_EVENT_VALUE_CHANGED, NULL);
}

void wheel_screen_behavior_tick(const mstime_t now) {
    Wheel* wheel = get_wheel(current_wheel);
    if (wheel == nullptr) {
        // This should not happen
        Serial.println("Got wheel == nullptr in wheel_screen_behavior_tick");
    }
    for (uint8_t s = 0; s < MAX_SATELLITES; s++) {
        Satellite* satellite = get_satellite_by_index(s);
        if (satellite == nullptr) { break; }
        if (satellite->t_report > wheel->t_last_report) {
            int dist = satellite->distance;
            char text_buffer[8];

            if (satellite == wheel->satellite) {
                int32_t percent_height;
                if (dist < wheel->fully_compressed_distance) {
                    percent_height = 0;
                } else if (dist > wheel->fully_extended_distance) {
                    percent_height = 100;
                } else {
                    percent_height = (int32_t)100 * (dist - wheel->fully_compressed_distance) / (wheel->fully_extended_distance - wheel->fully_compressed_distance);
                }
                lv_obj_set_height(ui_ctnrGap, lv_pct(percent_height));

                sprintf(text_buffer, "%d", dist);
                lv_label_set_text(ui_lblGap, text_buffer);
            }

            text_buffer[0] = satellite_ui_state[s].toggle ? '/' : '\\';
            sprintf(text_buffer + 1, " %d", dist);
            lv_label_set_text(satellite_ui_elements[s].lblSatellite, text_buffer);
            satellite_ui_state[s].toggle = !satellite_ui_state[s].toggle;
        }
    }
}
