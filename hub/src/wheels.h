#ifndef SUSPENSIONRT_WHEELS_H
#define SUSPENSIONRT_WHEELS_H

#include "common.h"
#include "satellites.h"

struct Wheel {
    Satellite* satellite = nullptr;
    char last_satellite_id[MAX_SATELLITE_ID_LENGTH + 1];
    mstime_t t_last_report = 0;
};

void init_wheels();

void maybe_assign_satellite_to_wheel(Satellite* satellite);

Wheel* get_wheel_of_satellite(Satellite* satellite);

// index: [left rear, left front, right front, right rear]
Wheel* get_wheel(uint8_t index);

#endif
