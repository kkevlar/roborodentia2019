#ifndef CONTROL_H
#define CONTROL_H

#include "testoptions.h"
#include "echo.h"
#include "wiring.h"
#include "wheel.h"

struct p_control_result
{
	int16_t result_speed;
	uint16_t end_condition_count;
};

struct p_control_args
{
	uint8_t pin_ultrasonic;
    int32_t mm_target;
    int32_t mm_cutoff;
    float pk;
    int16_t max_speed;
    uint8_t abs_speed_dead_zone;
    uint8_t abs_speed_boost_zone;
    uint8_t pin_switch;
    uint16_t max_end_condition_count;
};



void fill_p_control_result_default(struct p_control_result* result, struct p_control_args* args);
void fill_p_control_args_default(struct p_control_args* args);
void p_control_non_block(struct p_control_result* result, struct p_control_args* args);

#endif
