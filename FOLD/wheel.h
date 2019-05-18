
#ifndef WHEEL_H
#define WHEEL_H

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "wiring.h"

#define WHEEL_FL 0x00
#define WHEEL_FR 0x01
#define WHEEL_BL 0x02
#define WHEEL_BR 0x03

void wheel_init(void);
void set_speed(uint8_t wheel, int16_t speed, int time);

void wflush();

#endif
