#ifndef SWITCH_H
#define SWTICH_H

#include "wiring.h"
#include <Arduino.h>

// #define FAILURE 1
// #define SUCCESS 0

void switch_init(void);
int switch_simple_read(uint8_t pin_switch);
// int test_switch_south(long breaktime);
// int test_switch_north(long breaktime);
// int test_switch_east(long breaktime);
// int test_switch_west(long breaktime);

#endif
