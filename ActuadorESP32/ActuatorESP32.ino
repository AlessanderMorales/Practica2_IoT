#include <WiFi.h>
#include "LED.h"
const char* ssid = "COMTECO-N3715155";
const char* password = "AKQXC71347"; 

const char* serverAddress = "192.168.1.66";
int serverPort = 8000;

LED blueLED(14);   // 3 a 10 cm
LED greenLED(27);  // 10 a 20 cm
LED redLED(26);    // 20 a 30 cm
LED yellowLED(25); // 30 a 40 cm

WiFiClient client;

void connectWiFi() {
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado exitosamente");
  Serial.print("Dirección IP local: ");
  Serial.println(WiFi.localIP());
}


float requestDistance() {
  if (!client.connect(serverAddress, serverPort)) {
    Serial.println("Fallo al conectar con el servidor");
    return -1;  
  }
  client.print("GET");  
  delay(100);          
  String response = client.readString(); 
  Serial.println("Respuesta del servidor: " + response);
  client.stop(); 
  return response.toFloat();  
}
void updateLEDs(float distance) {
  blueLED.turnOff();
  greenLED.turnOff();
  redLED.turnOff();
  yellowLED.turnOff();
  if (distance >= 3 && distance <= 10) {
    blueLED.turnOn();
  } else if (distance > 10 && distance <= 20) {
    greenLED.turnOn();
  } else if (distance > 20 && distance <= 30) {
    redLED.turnOn();
  } else if (distance > 30 && distance <= 40) {
    yellowLED.turnOn();
  }
}

void setup() {
  Serial.begin(115200);
  connectWiFi(); 
}

void loop() {
  float distance = requestDistance();
  if (distance > 0) {
    updateLEDs(distance);
  }
  delay(2000);
}
