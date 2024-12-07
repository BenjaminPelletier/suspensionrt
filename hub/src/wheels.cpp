#include "wheels.h"

#include <string.h>
#include "common.h"

Wheel wheels[N_WHEELS];

void init_wheels() {
    for (uint8_t w = 0; w < N_WHEELS; w++) {
        wheels[w].last_satellite_id[0] = 0;
    }
}

void maybe_assign_satellite_to_wheel(Satellite* satellite) {
    if (satellite == nullptr) { return; }

    uint8_t w = 0;

    // See if this satellite is already assigned to a wheel
    for (w = 0; w < N_WHEELS; w++) {
        if (wheels[w].satellite == satellite) {
            return;
        }
    }

    // See if any wheels are already associated (via ID) with this satellite
    for (w = 0; w < N_WHEELS; w++) {
        if (wheels[w].satellite == nullptr && strcmp(wheels[w].last_satellite_id, satellite->id) == 0) {
            break;
        }
    }

    if (w == N_WHEELS) {
        // See if any wheels do not yet have an associated satellite
        for (w = 0; w < N_WHEELS; w++) {
            if (wheels[w].last_satellite_id[0] == 0) {
                break;
            }
        }
    }

    if (w < N_WHEELS) {
        // Associate this satellite with the wheel of the identified index
        wheels[w].satellite = satellite;
        strncpy(wheels[w].last_satellite_id, satellite->id, MAX_SATELLITE_ID_LENGTH);
    }
}

Wheel* get_wheel_of_satellite(Satellite* satellite) {
    for (uint8_t w = 0; w < N_WHEELS; w++) {
        if (wheels[w].satellite == satellite) {
            return &wheels[w];
        }
    }
    return nullptr;
}

Wheel* get_wheel(uint8_t index) {
    if (index >= N_WHEELS) {
        return nullptr;
    }
    return &wheels[index];
}
