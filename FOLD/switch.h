#ifndef SWITCH_H
#define SWTICH_H

#include "testoptions.h"
#include "wiring.h"
#include <Arduino.h>


void switch_init(void);
pin_t switch_test_all();
bool switch_test_up(pin_t pin);
bool switch_test_down(pin_t pin);

#endif
