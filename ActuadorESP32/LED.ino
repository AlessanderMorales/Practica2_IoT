#include "LED.h"

LED::LED(int pinNumber) : pin(pinNumber) {
  pinMode(pin, OUTPUT);  // Configurar el pin como salida
  turnOff();  // Apagar el LED inicialmente
}

void LED::turnOn() {
  digitalWrite(pin, HIGH);
}

void LED::turnOff() {
  digitalWrite(pin, LOW);
}
