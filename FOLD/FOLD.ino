#include "FOLD.h"


void setup()
{
	#ifdef FOLD_GLOBAL_TEST
		test_setup();
	#else
		main_setup();
	#endif
}

void loop()
{
	#ifdef FOLD_GLOBAL_TEST
		test_loop();
	#else
		main_loop();
	#endif
}
