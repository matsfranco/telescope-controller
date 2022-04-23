#include <StepperDriver.h>
#include <AltazimuthController.h>

#define NULL_ZONE 15

StepperDriver motor1 = StepperDriver("Motor 1",200,7,8,2,9,3,4,5,6);

// max microsseconds 16383

int altControl = A1; 
int aziControl = A2;


void convertValues(int value) {
  int halfPeriod = 3000;
  if(value < 512 - NULL_ZONE ) {
    halfPeriod = map(value,0,512 - NULL_ZONE,10,16000);
    Serial.println(halfPeriod);
    motor1.disableDriver();
    motor1.setCounterClockWiseDir();
    motor1.setHalfPeriod(halfPeriod);
    motor1.enableDriver();
    motor1.runDegrees(1);
  } else {
    if(value > 512 + NULL_ZONE) {
      halfPeriod = map(value,512 + NULL_ZONE,1023,16000,10);
      Serial.println(halfPeriod);
      motor1.disableDriver();
      motor1.setClockWiseDir();
    motor1.setHalfPeriod(halfPeriod);
      motor1.enableDriver();
      motor1.runDegrees(1);
    } else {
      motor1.disableDriver();
    }
  }
}

void readControl() {
  //int altValue = analogRead(altControl);
  int aziValue = analogRead(aziControl);
  //Serial.print(altValue); Serial.print(","); 
  //Serial.println(aziValue);
  convertValues(aziValue);
}

void setup() {
  Serial.begin(9600);
  motor1.initializeDriver();
  motor1.setStepMode(16);
}

void loop() {
  readControl();
  
  
  //motor1.enableDriver();
  //motor1.setClockWiseDir();
  //Serial.println(motor1.getCurrentStatus());
  //motor1.runDegrees(3000);
  //motor1.disableDriver();
  //delay(1000);
  //motor1.enableDriver();
  //motor1.setCounterClockWiseDir();
  //Serial.println(motor1.getCurrentStatus());
  //motor1.runDegrees(3000);
  //delay(1000);
}
