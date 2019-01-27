#include <stdio.h>

int main()
{
	FILE* input;
	char buf[2048];
    printf("Init \n");
    input = fopen("/dev/ttyACM0", "r");
    if(!input) 
    {
        printf("ACM0 is NULL. \n");
        input = fopen("/dev/ttyUSB0", "r");
        if (!input) {
            printf("USB0 is also NULL. Exiting.\n");
            return 1;
        }
    }
    while(fgets(buf, 2048, input) >= 0)
    {

    	printf("%s",buf);
    	// fprintf(input,"%s",buf);
    }
    return 0;
}