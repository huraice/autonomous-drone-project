

// Replace with your network credentials
const char* ssid = "YourSSID";
const char* password = "YourPassword";

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Mavlink.h>
//// Replace with your network credentials
//const char* ssid = "your_SSID";
//const char* password = "your_PASSWORD";

// Port number to listen for data on
const unsigned int localPort = 12345;

// UDP object
WiFiUDP udp;

void setup() {
  // Connect to Wi-Fi network
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  // Start UDP server
  udp.begin(localPort);
  Serial.print("Listening on port ");
  Serial.println(localPort);
}

void loop() {
  // Buffer to hold incoming data
  char packetBuffer[255];

  // Receive incoming UDP packets
  int packetSize = udp.parsePacket();
  if (packetSize) {
    // Read data into buffer
    int len = udp.read(packetBuffer, 255);
    if (len > 0) {
      packetBuffer[len] = 0;
    }

    // Parse joystick data
    int roll = 0;
    int pitch = 0;
    int throttle = 0;
    int yaw = 0;

    sscanf(packetBuffer, "%d,%d,%d,%d", &roll, &pitch, &throttle, &yaw);

    // Send RC commands to Pixhawk
    int RC_CHANNELS[8] = {1500, 1500, throttle, yaw, roll, pitch, 1500, 1500};
    int start_channel = 1;
    for (int i = 0; i < 8; i++) {
      int pwm = RC_CHANNELS[i];
      if (pwm < 1000) pwm = 1000;
      if (pwm > 2000) pwm = 2000;
      pwm = map(pwm, 1000, 2000, 1100, 1900);
      pwm = constrain(pwm, 1100, 1900);
      pwm = round(pwm);
      pwm = (pwm - 1100) * 2 + 1000;
      pwm = constrain(pwm, 1000, 2000);
      pwm = map(pwm, 1000, 2000, 0, 65535);
      uint16_t channel = start_channel + i;
      mavlink_msg_rc_channels_override_send(MAVLINK_COMM_0, 1, channel, pwm);
    }

    // Print joystick values
    Serial.print("Roll: ");
    Serial.print(roll);
    Serial.print(", Pitch: ");
    Serial.print(pitch);
    Serial.print(", Throttle: ");
    Serial.print(throttle);
    Serial.print(", Yaw: ");
    Serial.println(yaw);
  }

  delay(10);
}
