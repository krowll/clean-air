//*****************************************//
// configuration                           //
//*****************************************//
#define K_P				1	    // proportional factor of the PID controller
#define K_I				0.1  	// integral factor of the PID controller
#define K_D				0.5	    // derivative factor of the PID controller
#define TAU				20	    // number of measurements viewed in calculation, reduce to save space and calculation times
#define GOAL_TEMP		30	    // goal temperature of 30°C
#define SLEEP_TIME      5       // number of seconds waiting until next temperature read
//#define SIMULATION              // define is temperature is simulated or coming from a real sensor
#define TEMP_GPIO		17	    // the GPIO data pin of the temperature sensor
#define PWM			    16      // the PWM pin for fan control