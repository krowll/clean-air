//*****************************************//
// includes                                //
//*****************************************//
#include "caseTempController/config.h"
#include "caseTempController/temperature.h"

class CaseTempController
{
    private:

        // a history of the last TAU temperature errors
        int temperature_errors[TAU];

        // marks the place of the oldest info in the temperature_errors array
        int* p_oldest_temperature_error;

        // temperature sensor
        TempSensor tempSensor;

    public:

        int init(void);
        
        int caseTempController(void);
};