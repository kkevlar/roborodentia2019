#include "FOLD.h"


void setup()
{
	#if defined(TEST_DRIVE_STOP) || \
	defined(TEST_SWITCH) ||\
	defined(TEST_DRIVE_DIAG) ||\
	defined(TEST_DRIVE_CARD) ||\
	defined(TEST_ECHO)
		test_setup();
	#elif defined(GAME_A)
		main_setup();
	#else
		#error "NO OPTION"
	#endif
}

void loop()
{
	#if defined(TEST_DRIVE_STOP) || \
	defined(TEST_SWITCH) ||\
	defined(TEST_DRIVE_DIAG) ||\
	defined(TEST_DRIVE_CARD) ||\
	defined(TEST_ECHO)
		test_loop();
	#elif defined(GAME_A)
		main_loop();
	#else
		#error "NO OPTION"
	#endif
}
