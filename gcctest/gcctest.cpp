
#include <stdio.h>
#include "drive.h"
#include "cpTime.h"
#include <math.h>

int main()
{
	int degrees;
	drive_vector_t vec;

	printf("GccTest Module Initialized\n");
	drive_init();

	vec.speed = 255;

	while(1)
	{
		printf("Degrees: ");
		scanf("%d", &degrees);
		vec.degrees = degrees;
		go(vec);
	}
}

