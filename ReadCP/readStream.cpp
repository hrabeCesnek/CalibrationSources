#include "./linux-build-files/ps2000aCon.c"
#include<unistd.h>




int32_t main(void)
{
    int8_t ch;

	PICO_STATUS status;
	UNIT unit;

	printf("PicoScope 2000 Series (A API) Driver Example Program\n");
	printf("Version 2.3\n\n");
	printf("\n\nOpening the device...\n");

	status = OpenDevice(&unit);

	ch = ' ';

	
	DisplaySettings(&unit);


	//unsigned int microsecond = 1000000;
	//usleep(3 * microsecond);//sleeps for 3 second
	CloseDevice(&unit);

	return 1;
}