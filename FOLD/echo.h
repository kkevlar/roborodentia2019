#ifndef ECHO_H
#define ECHO_H

#include "testoptions.h"
#include <Arduino.h>
#include "wiring.h"

void echo_init();
float echo_test_mm(uint8_t pin);
void echo_print_all();

#endif

