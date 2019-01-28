#ifndef DRIVE_H
#define DRIVE_H

#include "testoptions.h"
#include "wiring.h"
#include "wheel.h"

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
void go(drive_vector_t vec);

#endif
