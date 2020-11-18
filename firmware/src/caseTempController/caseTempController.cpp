//*****************************************//
// includes                                //
//*****************************************//
#include <stdbool.h>
#include "caseTempController.h"
#include "caseTempController/controller.h"
#include "caseTempController/fan.h"

//*****************************************//
// functions    		   				   //
//*****************************************//
int CaseTempController::init(void)
{
    // variables
	int i;								// loop counter
    #ifndef SIMULATION
        int temperature;				// current actual temperature
        int temperature_error;			// the current difference between wished temperature and actual temperature
    #endif

    printf("Configuration:\n");
    printf("   Proportional factor:             %i\n", K_P);
    printf("   Integral factor:                 %f\n", K_I);
    printf("   Differential factor:             %f\n", K_D);
    printf("   Viewed number of measurements:   %i\n", TAU);
    printf("   Goal temperature:                %i°C\n", GOAL_TEMP);
    printf("   Sleep between each measurement:  %is\n", SLEEP_TIME);
    #ifdef SIMULATION
        printf("   The temperature measurements are simulated.\n");
    #endif

    printf("Initialize hardware.\n");
    if (fan_init() != 0)
		return -1;
    tempSensor.init();

    printf("Fill the temperature_errors array with inital values.\n");
	for (i = 0; i < TAU; i++)
	{
        #ifndef SIMULATION
            if ((temperature = tempSensor.read()) == TEMP_READ_ERROR)
			    return -1;
		
		    temperature_errors[i] =  ((temperature_error = temperature - GOAL_TEMP) > 0 ? temperature_error : 0);
        #else
            temperature_errors[i] = 0;
        #endif
	}
	p_oldest_temperature_error = &temperature_errors[0];

    return 0;
}


int CaseTempController::caseTempController(void)
{
	// variables
	int i;								// loop counter
	int temperature;					// current actual temperature
	int temperature_error;			// the current difference between wished temperature and actual temperature
    int temperature_error_sum;			// the sum of the last TAU temperature errors
	int pr, in, di;						// proportional, integral, and differential adjustment
	int fan_speed;						// the fan speed that shall be set


	printf("Enter main loop.\n");
	while (true)
	{
		// read in newest temperature error, put it in place of the oldest value
		if ((temperature = tempSensor.read()) == TEMP_READ_ERROR)
			return -1;
		*p_oldest_temperature_error = temperature_error = (temperature_error = temperature - GOAL_TEMP) > 0 ? temperature_error : 0;
        printf("\nNewest temperature: %i°C\n", temperature);
        printf("   Newest temperature error: %i°C\n", temperature_error);


		// set p_oldest_temperature_error to next place in array
		if (p_oldest_temperature_error == &temperature_errors[TAU])
			p_oldest_temperature_error = &temperature_errors[0];
		else
			p_oldest_temperature_error++;

        
		// calculate proportional adjustment
		pr = K_P * temperature_error;
        printf("   Proportional adjustment: %i\n", pr);


        // calculate integral adjustment
	    temperature_error_sum = 0;
	    for (i = 0; i < TAU; i++)
		    temperature_error_sum += temperature_errors[i];
	    in = K_I * temperature_error_sum;
        printf("   Integral adjustment: %i\n", in);


	    // calculate differential adjustment
	    di = K_D * (temperature_error - *p_oldest_temperature_error);
        printf("   Differential adjustment: %i\n", di);


	    // calculate and set new fan speed
	    fan_speed = pr + in + di;
        if (fan_speed < 0) fan_speed = 0;
	    if (fan_speed > 100) fan_speed = 100;
        printf("   Resulting fan speed: %i%%\n", fan_speed);
	    if (set_fan_speed(fan_speed) != 0)
	    	return -1;
	}
}
