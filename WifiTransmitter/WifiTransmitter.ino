#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

// Replace with your network credentials
const char* ssid = "YourSSID";
const char* password = "YourPassword";

// IP address of the receiver
const IPAddress receiverIP(192, 168, 1, 100);

// Port number to send data to
const unsigned int receiverPort = 12345;

// Define pins for joystick 1
#define joy1XPin  A0 // Arduino pin connected to VRX pin
//#define joy1YPin  A1
#define joy1YPin D4
//const int joy1XPin = A0;
//const int joy1YPin = A1;

// Define pins for joystick 2
#define joy2XPin   D3 // Arduino pin connected to VRX pin
#define joy2YPin  D0
//const int joy2XPin =;
//const int joy2YPin = ;

// Joystick threshold
const int joyThreshold = 10;

// UDP object
WiFiUDP udp;

void setup() {
  Serial.begin(115200);
  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Print local IP address
  Serial.println(WiFi.localIP());
}

void loop() {
  // Read joystick 1 input
  int joy1X = analogRead(joy1XPin);
  int joy1Y = analogRead(joy1YPin);

  // Read joystick 2 input
  int joy2X = analogRead(joy2XPin);
  int joy2Y = analogRead(joy2YPin);

  // Calculate joystick 1 values
  int joy1XVal = map(joy1X, 0, 1023, -100, 100);
  int joy1YVal = map(joy1Y, 0, 1023, -100, 100);

  // Calculate joystick 2 values
  int joy2XVal = map(joy2X, 0, 1023, -100, 100);
  int joy2YVal = map(joy2Y, 0, 1023, -100, 100);

  // Check joystick thresholds
  if (abs(joy1XVal) < joyThreshold) joy1XVal = 0;
  if (abs(joy1YVal) < joyThreshold) joy1YVal = 0;
  if (abs(joy2XVal) < joyThreshold) joy2XVal = 0;
  if (abs(joy2YVal) < joyThreshold) joy2YVal = 0;

  // Create data packet
  String data = String(joy1XVal) + "," + String(joy1YVal) + "," + String(joy2XVal) + "," + String(joy2YVal);

  // Send data to receiver
  udp.beginPacket(receiverIP, receiverPort);
  udp.print(data);
  udp.endPacket();

  delay(10);
}
