//*****************************************//
// includes                                //
//*****************************************//
#include "caseTempController/fan.h"


//*****************************************//
// defines                                 //
//*****************************************//
#define FREQUENCY   25000   // the PWM frequency (fan runs best at 25kHz)
#define RESOLUTION  8       // the duty cycle resolution in bits (8 means 255 steps)

//*****************************************//
// functions                               //
//*****************************************//

int fan_init(void)
{
    CONFIG_PWM(PWM, FREQUENCY, RESOLUTION);
	return 0;

end:
    printf("Fan initialization failed.\n");
	return -1;
}


int set_fan_speed(int fan_speed)
{
	SET_PWM_DUTYCYCLE(PWM, (int)(fan_speed * (RESOLUTION / 100)));
	return 0;
}