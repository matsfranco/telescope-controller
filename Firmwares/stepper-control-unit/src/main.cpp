#include <StepperDriver.h>
#include <AltazimuthController.h>

#define NULL_ZONE 30

StepperDriver motor1 = StepperDriver("Motor 1",200,7,8,2,9,3,4,5,6);
StepperDriver motor2 = StepperDriver("Motor 2",200,7,8,10,9,11,4,5,6);
// max microsseconds 16383

int altControl = A1; 
int aziControl = A2;


void convertValues(StepperDriver driver, int value) {
  
  if(value < 512 - NULL_ZONE ) {
    int halfPeriod = map(value,0,512 - NULL_ZONE,10,16383);
    Serial.print(driver.getName()); Serial.print(": "); Serial.print(halfPeriod);
    driver.disableDriver();
    driver.setCounterClockWiseDir();
    driver.setHalfPeriod(halfPeriod);
    driver.enableDriver();
    driver.runDegrees(1);
  } else {
    if(value > 512 + NULL_ZONE) {
      int halfPeriod = map(value,512 + NULL_ZONE,1023,16383,10);
      Serial.print(driver.getName()); Serial.print(": "); Serial.print(halfPeriod); 
      driver.disableDriver();
      driver.setClockWiseDir();
      driver.setHalfPeriod(halfPeriod);
      driver.enableDriver();
      driver.runDegrees(1);
    } else {
      Serial.print(driver.getName()); Serial.print(": 0");
      driver.disableDriver();
    }
  }
}

void readControl() {
  int altValue = analogRead(altControl);
  //int aziValue = analogRead(aziControl);
  if(altValue < 512 - NULL_ZONE || altValue > 512 + NULL_ZONE) {
    convertValues(motor1,altValue);
  }
  //if(aziValue < 512 - NULL_ZONE || aziValue > 512 + NULL_ZONE) {
  //  convertValues(motor2,aziValue);
  //} 
  
  Serial.println();
}

void setup() {
  Serial.begin(9600);
  motor1.initializeDriver();
  motor1.setStepMode(16);
}

void loop() {
  readControl();
}
