#ifndef SUSPENSIONRT_UI_BEHAVIOR_H
#define SUSPENSIONRT_UI_BEHAVIOR_H

#include "common.h"

// Note: This function must not be called until the UI elements have been initialized
void init_ui_behavior();

void ui_behavior_tick(mstime_t now);

#endif
