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

void echo_test()
{
	float f_front = -1;
	float f_back = -1;
	float f_left = -1;
	float f_right = -1;
	char buf[128];
	int16_t i_front = -1;
	int16_t i_back = -1;
	int16_t i_left = -1;
	int16_t i_right = -1;

	go_stop();

	// f_front = echo_test_mm(PIN_ULTRASONIC_ECHO_FRONT);
	// f_back = echo_test_mm(PIN_ULTRASONIC_ECHO_BACK);
	f_left = echo_test_mm(PIN_ULTRASONIC_ECHO_LEFT);
	// f_right = echo_test_mm(PIN_ULTRASONIC_ECHO_RIGHT);

	i_front = f_front;
	i_back = f_back;
	i_left = f_left;
	i_right = f_right;

	snprintf(buf, 128,"F:%5d B:%5d L:%5d R:%5d",
		i_front,
		i_back,
		i_left,
		i_right
		);
	Serial.println(buf);
	delay(500);
}

void test_loop()
{
	#if defined(TEST_DRIVE_STOP)
		go_stop();
	#elif defined(TEST_DRIVE_DIAG)
		diag_test();
	#elif defined(TEST_DRIVE_CARD)
		card_test();
	#elif defined(TEST_SWITCH)
		switch_test();
	#elif defined(TEST_ECHO)
		echo_test();
	#elif defined(GAME_A)
		#warning "THIS IS NOT A DRILL"
	#endif
}


