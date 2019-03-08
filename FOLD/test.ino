#include "test.h"

void test_setup()
{
	switch_init();
	drive_init();
	echo_init();
	Serial.begin(9600);
}

void switch_test()
{
	int i;

	for(i = 2; i <= 7; i++)
	{
		if(digitalRead(i) == LOW)
		{
			Serial.print("PRESS: ");
			Serial.println(i);
		}

	}

	delay(100);
}


void diag_test()
{
	drive_vector_t vec;
	vec.speed = 150;

	for(int i = 0; i < 4; i++)
	{
		vec.degrees = 45 + 90*i;
		go(vec);
		delay(1000);
		go_stop();
		delay(1000);
	}
	delay(5000);
}

void card_test()
{
	drive_vector_t vec;
	vec.speed = 150;

	// Serial.println("immacard");
	for(int i = 0; i < 4; i++)
	{
		vec.degrees = 90*i;
		go(vec);
		delay(500);
		go_stop();
		delay(500);
	}
	delay(1000);
}

void test_loop()
{
	#ifdef TEST_DRIVE_STOP
		go_stop();
	#endif
	#ifdef TEST_DRIVE_DIAG
		diag_test();
	#endif
	#ifdef TEST_DRIVE_CARD
		card_test();
	#endif
	#ifdef TEST_SWITCH
		switch_test();
	#endif
}


