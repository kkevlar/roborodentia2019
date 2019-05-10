
#include "aim.h"

uint16_t shoot_location_tally[AIM_LOCATION_COUNT];

void aim_init(void)
{
	uint32_t seed;

	pinMode(PIN_ANALOG_RANDOM, INPUT);
	delay(5);
	seed = analogRead(PIN_ANALOG_RANDOM);
	delay(5);
	seed *= analogRead(PIN_ANALOG_RANDOM);
	randomSeed(seed);

	for(seed = 0; seed < AIM_LOCATION_COUNT; seed++)
	{
		shoot_location_tally[seed] = 0;
	}
}

#define CLEAR_ALL_IS_MINS() for( \
		z = AIM_LOCATION_SELECTION_RANDOM_MIN;\
		z <= AIM_LOCATION_SELECTION_RANDOM_MAX;\
		z++)\
	{\
		is_min[z] = 0;\
	}\

#define TRUE_TO_ONE(b) (((b) ? (1) : (0)))

#ifndef GCCTEST
#define arduinoRandom(x) random(x)
#endif

aim_location_t aim_select_location()
{
	bool is_min[AIM_LOCATION_COUNT];
	uint16_t min_tally = 0;
	uint16_t count_cups = 0;
	int i;
	int z;

	CLEAR_ALL_IS_MINS();
	is_min[AIM_LOCATION_SELECTION_RANDOM_MIN] = 1;
	min_tally = shoot_location_tally[AIM_LOCATION_SELECTION_RANDOM_MIN];
	count_cups = 1;
	
	for(
		i = AIM_LOCATION_SELECTION_RANDOM_MIN+1;
		i <= AIM_LOCATION_SELECTION_RANDOM_MAX;
		i++)
	{


		if(min_tally == 
			shoot_location_tally[i])
		{
			count_cups++;
			is_min[i] = 1;
		}
		else if(min_tally > 
			shoot_location_tally[i])
		{
			CLEAR_ALL_IS_MINS();
			count_cups = 1;
			min_tally = shoot_location_tally[i];
			is_min[i] = 1;
		}
	}

	z = arduinoRandom(count_cups);
	for( i = AIM_LOCATION_SELECTION_RANDOM_MIN;
		i <= AIM_LOCATION_SELECTION_RANDOM_MAX;
		 i++)
	{
		z -= TRUE_TO_ONE(is_min[i]);
		if(z < 0)
			break;
	}

	shoot_location_tally[i]++;
	return i;
}














