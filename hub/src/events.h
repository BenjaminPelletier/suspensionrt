#ifndef SUSPENSIONRT_EVENTS_H
#define SUSPENSIONRT_EVENTS_H

#include <cstdint>

typedef void (*time_of_flight_callback_t)(uint8_t sensor, int distance);
void onTimeOfFlight(uint8_t sensor, int distance);

#endif
