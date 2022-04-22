#include <Arduino.h>
#include <AltazimuthController.h>
#include <StepperDriver.h>

AltazimuthController::AltazimuthController(StepperDriver altitude, StepperDriver azimuth) {
    _altitude = altitude;
    _azimuth = azimuth;
}

boolean AltazimuthController::setStepModePins(int ms1, int ms2, int ms3) {
    return true;
}

boolean AltazimuthController::initializeAltitudeAxis(StepperDriver alt) {
    return true;
}

boolean AltazimuthController::initializeAzimuthAxis(StepperDriver azi) {
    return true;
}