// iot-firmware/ParkIt_Node.ino
// Arduino Sketch for ParkIt Parking Slot Node
// This code focuses on basic connectivity and sensor polling.

#include <WiFi.h>  //library based on your board
//#include <HTTPClient.h> // Library for making HTTP calls (if needed)

// --- WiFi Credentials (Update these in a local .env file when developing) ---
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";


const int SENSOR_PIN = 2; 
const char* API_URL = "http://your-backend-ip/api/v1/iot/update"; 


void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT);

  // Connect to Wi-Fi
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {

  int sensorValue = digitalRead(SENSOR_PIN);
  bool isOccupied = (sensorValue == HIGH); 

  Serial.print("Slot Status: ");
  Serial.println(isOccupied ? "OCCUPIED" : "AVAILABLE");


  sendSlotStatusToBackend(isOccupied);


  delay(5000); 
}


void sendSlotStatusToBackend(bool status) {

  Serial.print("Preparing to send status to backend: ");
  Serial.println(status ? "Occupied" : "Available");
}
