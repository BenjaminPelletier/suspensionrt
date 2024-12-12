#include "persistence.h"

#include <Preferences.h>

#include "common.h"
#include "wheels.h"
#include "satellites.h"

Preferences preferences;

struct WheelKeys {
    const char* fully_compressed_distance;
    const char* fully_extended_distance;
    const char* last_satellite_id;
};

const WheelKeys WHEEL_KEYS[N_WHEELS] = {
    {
        .fully_compressed_distance = "c0",
        .fully_extended_distance = "e0",
        .last_satellite_id = "s0",
    },
    {
        .fully_compressed_distance = "c1",
        .fully_extended_distance = "e1",
        .last_satellite_id = "s1",
    },
    {
        .fully_compressed_distance = "c2",
        .fully_extended_distance = "e2",
        .last_satellite_id = "s2",
    },
    {
        .fully_compressed_distance = "c3",
        .fully_extended_distance = "e3",
        .last_satellite_id = "s3",
    },
};

void init_persistence() {
    preferences.begin("suspensionrt");
}

void store_wheel_settings() {
    for (uint8_t w = 0; w < N_WHEELS; w++) {
        Wheel* wheel = get_wheel(w);
        preferences.putUShort(WHEEL_KEYS[w].fully_compressed_distance, wheel->fully_compressed_distance);
        preferences.putUShort(WHEEL_KEYS[w].fully_extended_distance, wheel->fully_extended_distance);
        preferences.putString(WHEEL_KEYS[w].last_satellite_id, wheel->last_satellite_id);
    }
}

void restore_wheel_settings() {
    for (uint8_t w = 0; w < N_WHEELS; w++) {
        Wheel* wheel = get_wheel(w);
        wheel->fully_compressed_distance = preferences.getUShort(WHEEL_KEYS[w].fully_compressed_distance, 0);
        wheel->fully_extended_distance = preferences.getUShort(WHEEL_KEYS[w].fully_extended_distance, 1000);
        String sat_id = preferences.getString(WHEEL_KEYS[w].last_satellite_id, "");
        strncpy(wheel->last_satellite_id, sat_id.c_str(), MAX_SATELLITE_ID_LENGTH);
    }
}
