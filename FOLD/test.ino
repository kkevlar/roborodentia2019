#include "test.h"

void test_setup()
{
	switch_init();
	drive_init();
	echo_init();
	Serial.begin(9600);
}

void test_loop()
{
	go_stop();
}


