
#include <StepperDriver.h>
#ifndef ALTAZIMUTHCONTROLLER_H
#define ALTAZIMUTHCONTROLLER_H



class AltazimuthController {
    public:
        AltazimuthController(StepperDriver altitude, StepperDriver azimuth);
        boolean setStepModePins(int ms1, int ms2, int ms3);
        boolean initializeAltitudeAxis(StepperDriver alt);
        boolean initializeAzimuthAxis(StepperDriver azi);
    private:    
        String _type;
        StepperDriver _altitude;
        StepperDriver _azimuth;
};

#endif