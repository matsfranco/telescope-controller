#include <Arduino.h>
#include <StepperDriver.h>
#include <AltazimuthController.h>

StepperDriver motor1 = StepperDriver("Motor 1",200,4,8,3,9,2,4,5,6);

#define STEP_HIGH        PORTD |=  0b00001000;
#define STEP_LOW         PORTD &= ~0b00001000;
#define TIMER1_INTERRUPTS_ON    TIMSK1 |=  (1 << OCIE1A);
#define TIMER1_INTERRUPTS_OFF   TIMSK1 &= ~(1 << OCIE1A);

unsigned int c0;

void setup() {
  //Serial.begin(9600);
  motor1.initializeDriver();
  //motor1.setHalfPeriod(200);
  //motor1.setBotSpeed(12000);
  //motor1.setTopSpeed(100);
  //motor1.setAcceleration(10);

  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;
  OCR1A = 1000;                             
  TCCR1B |= (1 << WGM12);
  TCCR1B |= ((1 << CS11) | (1 << CS10));
  interrupts();
  c0 = 1600;
  //motor1.setC0(1600);
}


volatile int dir = 0;
volatile unsigned int maxSpeed = 20; // timer ticks
volatile unsigned long n = 0;
volatile float d;
volatile unsigned long stepCount = 0;
volatile unsigned long rampUpStepCount = 0;
volatile unsigned long totalSteps = 0;
volatile int stepPosition = 0;
volatile bool movementDone = false;

//Interruption Service Routine
ISR(TIMER1_COMPA_vect) {
  if(stepCount < totalSteps) {
    STEP_HIGH
    STEP_LOW
    stepCount++;
    stepPosition += dir;
  } else {
    movementDone = true;
    TIMER1_INTERRUPTS_OFF
  }

  if(rampUpStepCount == 0) {
    n++;
    d = d - (2*d)/(4*n+1);
    if(d <= maxSpeed) {     
      d = maxSpeed;
      rampUpStepCount = stepCount;
    }
    if(stepCount >= totalSteps/2) {    
      rampUpStepCount = stepCount;
    }
  } else {
    if(stepCount >= totalSteps - rampUpStepCount) {
      n--;
      d = (d * (4*n+1)) / (4*n + 1 - 2);
    }
  }
  OCR1A = d;
}

void moveNSteps(long steps) {
  digitalWrite(2,steps < 0 ? HIGH : LOW);
  dir = steps > 0 ? 1 : -1;
  totalSteps = abs(steps);
  d = c0;
  OCR1A = d;
  stepCount = 0;
  n = 0;
  rampUpStepCount = 0;
  movementDone = false;
  TIMER1_INTERRUPTS_ON
}

void moveToPosition(long p, bool wait = true) {
  moveNSteps(p - stepPosition);
  while(wait && ! movementDone);
}

void loop() {
  //motor1.setClockWiseDir();
  //motor1.constantAcceleration();
  //motor1.setCounterClockWiseDir();
  //motor1.constantAcceleration();
  moveToPosition(32000);
  moveToPosition(-32000);

}

