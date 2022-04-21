#include "StepperDriver.h"

StepperDriver motor1 = StepperDriver("Motor 1",200,7,8,2,9,3,4,5,6);

void setup() {
  Serial.begin(9600);
  motor1.initializeDriver();
  motor1.setStepMode(16);
}

void loop() {
  motor1.enableDriver();
  motor1.setClockWiseDir();
  Serial.println(motor1.getCurrentStatus());
  motor1.runDegrees(3000);
  motor1.disableDriver();
  delay(1000);
  motor1.enableDriver();
  motor1.setCounterClockWiseDir();
  Serial.println(motor1.getCurrentStatus());
  motor1.runDegrees(3000);
  delay(1000);
}
