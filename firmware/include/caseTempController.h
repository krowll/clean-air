//*****************************************//
// includes                                //
//*****************************************//
#include "caseTempController/config.h"

class CaseTempController
{
    private:

        // a history of the last TAU temperature errors
        int temperature_errors[TAU];

        // marks the place of the oldest info in the temperature_errors array
        int* p_oldest_temperature_error;

    public:

        int initCaseTempController(void);
        
        int caseTempController(void);
};