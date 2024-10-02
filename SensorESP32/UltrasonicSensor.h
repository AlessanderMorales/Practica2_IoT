#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <Arduino.h>

class UltrasonicSensor {
  private:
    int trigPin;
    int echoPin;   
    long duration; 

  public:
    UltrasonicSensor(int trig, int echo);
    void trigger();
    float getDistance();
};

#endif
