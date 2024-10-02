#include <WiFi.h>
#include "UltrasonicSensor.h"

const int trigPin = 12;   
const int echoPin = 13;   

UltrasonicSensor sensor(trigPin, echoPin);
const char* ssid = "COMTECO-N3715155";         
const char* password = "AKQXC71347"; 

const char* serverAddress = "192.168.1.66"; 
int serverPort = 8000;

WiFiClient client;

// Función para conectar a la red Wi-Fi
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
void sendDistance(float distance) {
  if (!client.connect(serverAddress, serverPort)) {
    Serial.println("Fallo al conectar con el servidor");
    return;
  }

  // Enviar la distancia al servidor
  String data = "distance=" + String(distance);
  client.print(data);
  Serial.println("Distancia enviada: " + data);
  client.stop(); 
}

void setup() {
  Serial.begin(115200);
  connectWiFi();
}

void loop() {
  sensor.trigger();
  float distance = sensor.getDistance();
  Serial.print("Distancia medida: ");
  Serial.println(distance);
  sendDistance(distance);
  delay(2000);
}
