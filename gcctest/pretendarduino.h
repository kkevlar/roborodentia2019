
#ifndef PRETENDARDUINO_H
#define PRETENDARDUINO_H

#define GCCTEST

#define A0 20
#define A1 21
#define A2 22
#define A3 23
#define INPUT 0

#include "wiring.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void pinMode(int num, int x);
void delay(int ms);
int analogRead(int pin);
void randomSeed(int seed);
int arduinoRandom(int max);

#endif

