//*****************************************//
// includes                                //
//*****************************************//
#include <stdio.h>
#include <unistd.h>
#include "config.h"
#include "Arduino.h"


//*****************************************//
// macros                                  //
//*****************************************//
#define GPIO_WRITE(gpio, level)		if (gpioWrite(gpio, level) != 0)						\
									{														\
										printf("GPIO write failed, ending program.\n"); 	\
										goto end;											\
									}


#define GPIO_READ(gpio)				level = gpioRead(gpio);/*if ((level = gpioRead(gpio)) == PI_BAD_GPIO)	        \
									{														\
									 	printf("GPIO read failed, ending program.\n");		\
									 	goto end;											\
									}*/

#define GPIO_SET_MODE(gpio, mode)		if (gpioSetMode(gpio, mode) != 0)									\
										{																	\
											printf("GPIO mode setting failed.\n");			                \
											goto end;														\
										}

#define SET_PWM_DUTYCYCLE(gpio, dutycycle)	ledcWrite(gpio, dutycycle);

#define CONFIG_PWM(gpio, freq, resolution)	ledcSetup(0, freq, resolution);                                 \
                                            ledcAttachPin(gpio, 0);

#define USLEEP(microseconds)            usleep(microseconds);

#define SLEEP(seconds)                  sleep(seconds);