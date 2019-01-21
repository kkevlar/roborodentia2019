#ifndef DRIVE_H
#define DRIVE_H

#include <Wire.h>
#include <Adafruit_MotorShield.h>

#include "wiring.h"

struct _drive_vector_t_
{
	int16_t degrees; 
	int16_t speed;
	uint8_t maxspeed; 
};
typedef struct _drive_vector_t_ drive_vector_t;


void drive_init(void);
void go_north(void);
void go_south(void);
void go_east(void);
void go_west(void);
void go_stop(void);
void set_speed(Adafruit_DCMotor* motor, int speed, int time);
void go(drive_vector_t vec);

#endif