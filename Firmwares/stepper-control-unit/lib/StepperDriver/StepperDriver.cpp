#include <Arduino.h>
#include <StepperDriver.h>

StepperDriver::StepperDriver(String motorName, int totalSteps, int enable, int reset, int stp, int sleep, int dir, int ms1, int ms2, int ms3) {  
  _motorName = motorName;
  _halfPeriod = 3000;
  _totalSteps = totalSteps;
  _en = enable;
  _rst = reset;
  _stp = stp;
  _slp = sleep;
  _dir = dir;
  _ms1 = ms1;
  _ms2 = ms2;
  _ms3 = ms3;
  _pulseFrequency = 1000000 / (2 * _halfPeriod);// in pulses per secons (Hz)
  _angularSpeed = (_pulseFrequency * 60) / _totalSteps; // in Revolutions per Minute (RPM)
  _stepMode = 16;
  _resolution = (360.0/_totalSteps)/_stepMode;
  pinMode(_ms1, OUTPUT);
  pinMode(_ms2, OUTPUT);
  pinMode(_ms3, OUTPUT);
  pinMode(_en, OUTPUT);
  pinMode(_dir, OUTPUT);
  pinMode(_rst, OUTPUT);
  pinMode(_slp, OUTPUT);
  pinMode(_stp, OUTPUT);
}

StepperDriver::StepperDriver() {
  
}

int StepperDriver::setStepMode(int divider) {
  switch(divider) {
    // Full Step
    case 1: 
      digitalWrite(_ms1,LOW);
      digitalWrite(_ms2,LOW);
      digitalWrite(_ms3,LOW);
      _stepMode = divider;
      return _stepMode;
    // Half Step
    case 2: 
      digitalWrite(_ms1,LOW);
      digitalWrite(_ms2,LOW);
      digitalWrite(_ms3,HIGH);
      _stepMode = divider;
      return _stepMode;
    // 1/4 Step
    case 4: 
      digitalWrite(_ms1,LOW);
      digitalWrite(_ms2,HIGH);
      digitalWrite(_ms3,LOW);
      _stepMode = divider;
      return _stepMode;
    // 1/8 Step
    case 8: 
      digitalWrite(_ms1,LOW);
      digitalWrite(_ms2,HIGH);
      digitalWrite(_ms3,HIGH);
      _stepMode = divider;
      return _stepMode;
    // 1/16 Step
    case 16: 
      digitalWrite(_ms1,HIGH);
      digitalWrite(_ms2,HIGH);
      digitalWrite(_ms3,HIGH);
      _stepMode = divider;
      return _stepMode;
    // The default beavior is 1/16 Step
    default:  
      digitalWrite(_ms1,HIGH);
      digitalWrite(_ms2,HIGH);
      digitalWrite(_ms3,HIGH);
      _stepMode = 16;
      return _stepMode;  
  }
}

boolean StepperDriver::setClockWiseDir() {
  disableDriver();   
  digitalWrite(_dir,HIGH);
  _directionStatus = "Clock Wise";
  enableDriver();  
  return true;
}

boolean StepperDriver::setCounterClockWiseDir() {
  disableDriver();  
  digitalWrite(_dir,LOW);
  _directionStatus = "Counter Clock Wise";
  enableDriver(); 
  return true;
}

boolean StepperDriver::enableDriver() {
  digitalWrite(_en,LOW);
  _enableStatus = "Enabled";
  return true;
}

boolean StepperDriver::disableDriver() {
  digitalWrite(_en,HIGH);
  _enableStatus = "Disabled";
  return false;
}

boolean StepperDriver::resetDriver() {
  digitalWrite(_rst, LOW);
  delay (10);
  digitalWrite(_rst, HIGH);
  delay (10);
  return true;
}

void StepperDriver::setHalfPeriod(int value) {
  _halfPeriod = value; 
}

void StepperDriver::executeStep() {
  digitalWrite(_stp, LOW);
  delayMicroseconds (_halfPeriod);
  digitalWrite(_stp, HIGH);
  delayMicroseconds (_halfPeriod);
}

boolean StepperDriver::runDegrees(int deg) {
  for(int s = 0; s < deg; s++) {
    executeStep();  
  }
  return true;
}

boolean StepperDriver::inactivateSleep() {
  digitalWrite(_slp,HIGH);
  return true;
}

boolean StepperDriver::initializeDriver() {
  disableDriver();
  inactivateSleep();
  resetDriver();
  setStepMode(16);
  setClockWiseDir();
  enableDriver();
  return true;  
}

String StepperDriver::getCurrentStatus() {
    String currentStatus = "";
    currentStatus += "Name: "+_motorName+"\n";
    currentStatus += "Total Steps: "+(String)_totalSteps+"\n";
    currentStatus += "Step Mode: 1/"+(String)_stepMode+"\n";
    currentStatus += "Status: "+_enableStatus+"\n";
    currentStatus += "Pulse Frequency: "+(String)_pulseFrequency+"\n";
    currentStatus += "Direction: "+_directionStatus+"\n";
    currentStatus += "Resolution: "+String(_resolution,3)+" degrees per step\n";
    currentStatus += "Angular Speed: "+(String)_angularSpeed+" rpm\n";
    return currentStatus;
}