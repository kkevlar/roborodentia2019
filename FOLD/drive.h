#ifndef DRIVE_H
#define DRIVE_H

#include "testoptions.h"
#include "wiring.h"
#include "wheel.h"

struct _drive_vector_t_
{
	int16_t degrees; 
	int16_t speed;
	// uint8_t maxspeed; 
};
typedef struct _drive_vector_t_ drive_vector_t;

void drive_init(void);
int16_t drive_easy_atan(int16_t fb, int16_t lr);
void go_front(void);
void go_back(void);
void go_right(void);
void go_left(void);
void go_stop(void);
void go(drive_vector_t vec);

#endif
