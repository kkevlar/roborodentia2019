
#ifndef FAKEWHEEL_H
#define FAKEWHEEL_H

#include <stdio.h>
#include <inttypes.h>
#include "wiring.h"

#define WHEEL_FL 0x01
#define WHEEL_FR 0x02
#define WHEEL_BL 0x04
#define WHEEL_BR 0x08

void wheel_init(void);
void set_speed(uint8_t wheel, int16_t speed, int time);

#endif
