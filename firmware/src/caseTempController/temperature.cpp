//*****************************************//
// includes                                //
//*****************************************//
#include "caseTempController/temperature.h"

int read_temperature(void)
{

    #ifndef SIMULATION

        // variables
        int i = 0;                      // loop counter
        int level = LOW;                // voltage level of GPIO (filled in macro TEMP_READ)
	    int dht11_dat[5] = { 0, 0, 0, 0, 0 };

	    uint8_t laststate	= HIGH;
	    uint8_t counter		= 0;
	    uint8_t j			= 0;
	    float	f; // fahrenheit

	    printf("\n");

	    // pull pin down for 18 milliseconds
	    GPIO_SET_MODE(TEMP_GPIO, PI_OUTPUT);
	    GPIO_WRITE(TEMP_GPIO, LOW);
	    usleep(18000);
	    // then pull it up for 40 microseconds
	    GPIO_WRITE(TEMP_GPIO, HIGH);
	    usleep(40);
	    // prepare to read the pin
	    GPIO_SET_MODE(TEMP_GPIO, PI_INPUT);
    
	    // detect change and read data
	    for ( i = 0; i < 85; i++ )
	    {
	    	counter = 0;
	    	TEMP_READ(TEMP_GPIO);
	    	while ( level == laststate )
	    	{
	    		counter++;
	    	 	usleep(1);
	    		if (counter == 255)
	    		{
	    			break;
	    		}
	    	}
	    	TEMP_READ(TEMP_GPIO);
	    	laststate = level;

	    	if ( counter == 255 )
	    		break;

	    	// ignore first 3 transitions
	    	if ( (i >= 4) && (i % 2 == 0) )
	    	{
	    		// shove each bit into the storage bytes
	    		dht11_dat[j / 8] <<= 1;
	    		if ( counter > 16 )
	    			dht11_dat[j / 8] |= 1;
	    		j++;
	    	}
	    }

	    // check we read 40 bits (8bit x 5 ) + verify checksum in the last byte print it out if data is good
	    if ( (j >= 40) &&
	         (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) )
	    {
	    	f = dht11_dat[2] * 9. / 5. + 32;
	    	printf("Humidity = %d.%d %% Temperature = %d.%d *C (%.1f *F)\n",
	    		dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3], f );
	    }else  {
	    	printf( "Data not good, skip\n");
	    }

	    return 0;

    end:    
	    return TEMP_READ_ERROR;*/

    #else

        static int counter = 0;

        const int temps[] = {30, 30, 35, 35 , 35, 35, 40, 40, 40, 40,
                             80, 80, 75, 75 , 70, 70, 70, 60, 50, 40,
                             30, 30, 30, 100, 30, 40, 40, 50, 50, 40};

        int temp = temps[counter];
        counter = (counter == 29) ? 0 : counter + 1;                
        return temp;

    #endif
}