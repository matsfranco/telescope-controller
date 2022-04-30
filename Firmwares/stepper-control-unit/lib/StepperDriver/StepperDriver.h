/**  StepperDriver.h - Library to implement the hardware interface with A4988 Stepper Motor Driver
 * Created by Mateus Franco
 *  March 2022
**/

#ifndef STEPPERDRIVER_H
#define STEPPERDRIVER_H

#include <Arduino.h>

class StepperDriver {
  public:
    StepperDriver(String motorName, int totalSteps, int enable, int reset, int stp, int sleep, int dir, int ms1, int ms2, int ms3);
    StepperDriver();
    int setStepMode(int divider);
    boolean setClockWiseDir();
    boolean setCounterClockWiseDir();
    boolean enableDriver();
    boolean disableDriver();
    boolean resetDriver();
    void setHalfPeriod(int value);
    boolean initializeDriver();
    boolean runSteps(int steps);
    boolean inactivateSleep();
    String getCurrentStatus();
    String getName();
    boolean setTopSpeed(int speed); 
    boolean setBotSpeed(int speed);
    boolean setAcceleration(int acc);
    void constantAcceleration();

  private: 
    String _motorName;
    int _en;  // Enable Pin
    int _dir; // Direction Pin
    int _rst; // Reset Pin
    int _slp; // Sleep Pin
    int _stp; // Step Pin
    int _ms1;
    int _ms2;
    int _ms3;
    int _stepMode;
    int _totalSteps;
    int _halfPeriod;  // Half Period in Microseconds
    float _angularSpeed;
    long _pulseFrequency;
    float _resolution;
    String _directionStatus;
    String _enableStatus;
    int _botSpeed;
    int _topSpeed;
    int _acc;
    void executeStep(int halfPeriod);
};

#endif