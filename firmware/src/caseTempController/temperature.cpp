//*****************************************//
// includes                                //
//*****************************************//
#include "caseTempController/temperature.h"

//*****************************************//
// functions    		   				   //
//*****************************************//
void TempSensor::init(void)
{
    (*sensors).begin();
    return;
}


int TempSensor::read(void)
{
    #ifndef SIMULATION

        (*sensors).requestTemperatures();
        return (*sensors).getTempCByIndex(0);

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