
#ifndef WHEEL_H
#define WHEEL_H

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "wiring.h"

#define WHEEL_NW 0x01
#define WHEEL_NE 0x02
#define WHEEL_SW 0x04
#define WHEEL_SE 0x08

void wheel_init(void);
void set_speed(uint8_t wheel, int16_t speed, int time);

#endif
