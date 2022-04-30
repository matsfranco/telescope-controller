#include <Arduino.h>
#include <StepperDriver.h>
#include <AltazimuthController.h>

StepperDriver motor1 = StepperDriver("Motor 1",200,4,8,3,9,2,4,5,6);

void setup() {
  Serial.begin(9600);
  motor1.initializeDriver();
  motor1.setHalfPeriod(200);
  
  motor1.setBotSpeed(12000);
  motor1.setTopSpeed(100);
  motor1.setAcceleration(10);
}

void loop() {
  motor1.setClockWiseDir();
  motor1.constantAcceleration();
  motor1.setCounterClockWiseDir();
  motor1.constantAcceleration();
}

