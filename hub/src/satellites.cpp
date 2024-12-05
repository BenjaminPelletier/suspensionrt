#include "satellites.h"
#include "common.h"
#include <string.h>

const length_t MAX_SATELLITES = 8;
Satellite satellites[MAX_SATELLITES];
length_t n_satellites = 0;

Satellite* get_satellite_by_id(char* id) {
    uint8_t s;
    for (s = 0; s < n_satellites; s++) {
        if (strcmp(satellites[s].id, id) == 0) {
            break;
        }
    }
    if (s >= n_satellites) {
        // We haven't seen this satellite before
        if (s >= MAX_SATELLITES) {
            // We've identified too many satellites; overwrite one
            s -= 1;
        }
        n_satellites = s + 1;
        strncpy(satellites[s].id, id, MAX_SATELLITE_ID_LENGTH);
    }
    return &satellites[s];
}
