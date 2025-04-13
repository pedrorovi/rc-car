#pragma once

#include "system.h"

bool setupSystem(System* system);
bool mpptLoop(System* system);
void updateStepperLoop(System* system);