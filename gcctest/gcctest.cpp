
#include <stdio.h>
#include "drive.h"
#include "cpTime.h"
#include <math.h>

int main()
{
	int fb;
	int rl;
	int degrees;
	drive_vector_t vec;

	printf("GccTest Module Initialized\n");
	drive_init();

	vec.speed = 255;

	while(1)
	{
		printf("FB: ");
		scanf("%d", &fb);
		printf("RL: ");
		scanf("%d", &rl);

		degrees = drive_easy_atan(fb,rl);

		printf("degrees = %d\n\n", degrees);
	}

	// while(1)
	// {
	// 	printf("Degrees: ");
	// 	scanf("%d", &degrees);
	// 	vec.degrees = degrees;
	// 	go(vec);
	// }
}

