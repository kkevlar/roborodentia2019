
#include "aim.h"
#include <stdio.h>

int main(void)
{
	int i;
	aim_init();


	for(i = 0; i < 100; i++)
	{
		if(i % 5 == 0)
			printf("-----\n");
		printf("Shoot @ %d\n", aim_select_location());	
	}

	return 1;
}

