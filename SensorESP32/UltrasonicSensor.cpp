#include "UltrasonicSensor.h"


UltrasonicSensor::UltrasonicSensor(int trig, int echo) {
  trigPin = trig;
  echoPin = echo;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);   
}


void UltrasonicSensor::trigger() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
}

float UltrasonicSensor::getDistance() {
  duration = pulseIn(echoPin, HIGH);
  float distance = duration / 58.2;  
  return distance;
}
