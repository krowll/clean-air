//*****************************************//
// includes                                //
//*****************************************//
#include <DallasTemperature.h>
#include "config.h"
#include "controller.h"


//*****************************************//
// defines                                 //
//*****************************************//
#define TEMP_READ_ERROR		2147483647
#define ONE_WIRE_BUS        2


//*****************************************//
// prototypes                              //
//*****************************************//
class TempSensor
{
    private:

        OneWire* oneWire;

        DallasTemperature* sensors;

    public:

        TempSensor()
        {
            oneWire = new OneWire(ONE_WIRE_BUS);
            sensors = new DallasTemperature(oneWire);
        }

        void init(void);

        int read(void);

};