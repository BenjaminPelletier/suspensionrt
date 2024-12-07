#ifndef SUSPENSIONRT_SATELLITES_H
#define SUSPENSIONRT_SATELLITES_H

#include "common.h"

const length_t MAX_SATELLITE_ID_LENGTH = 17;

struct Satellite
{
    char id[MAX_SATELLITE_ID_LENGTH + 1];
    int distance;
    mstime_t t_report;
};

Satellite* get_satellite_by_id(char* id);

Satellite* get_satellite_by_index(uint8_t index);

#endif
