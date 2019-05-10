
#include "pretendarduino.h"

void pinMode(int num, int x)
{

}

void delay(int ms)
{

}

int analogRead(int pin)
{
	return time(NULL);
}

void randomSeed(int seed)
{
	srand(seed);
}

int arduinoRandom(int max)
{
	return random() % max;
}

