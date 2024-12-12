#ifndef SUSPENSIONRT_WHEELS_H
#define SUSPENSIONRT_WHEELS_H

#include "common.h"
#include "satellites.h"

struct Wheel {
    Satellite* satellite = nullptr;
    char last_satellite_id[MAX_SATELLITE_ID_LENGTH + 1];
    mstime_t t_last_report = 0;
    uint16_t fully_compressed_distance = 0;
    uint16_t fully_extended_distance = 1000;
};

void maybe_assign_satellite_to_wheel(Satellite* satellite);

Wheel* get_wheel_of_satellite(Satellite* satellite);

// index: [left rear, left front, right front, right rear]
Wheel* get_wheel(uint8_t index);

#endif
