// Uses libraries:
// Adafruit VL53L1X

#include <WiFi.h>
//#include <esp_wifi.h>
#include <AsyncUDP.h>
#include "Adafruit_VL53L1X.h"
#include "wifi_info.h"

#define TOF_PIN_VIN -1
#define TOF_PIN_GND 22
#define TOF_PIN_SDA 19
#define TOF_PIN_SCL 23
#define TOF_PIN_INT 18
#define TOF_PIN_XSHUT 5
#define TOF_ADDRESS 0x29

Adafruit_VL53L1X tof = Adafruit_VL53L1X(TOF_PIN_XSHUT, TOF_PIN_INT);

AsyncUDP udp;
IPAddress hub(192, 168, 4, 1);
String mac_address;

void connectToWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("WiFi Failed");
    while (1) {
      delay(1000);
    }
  }
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
}

void sendPacket(String text) {
  AsyncUDPMessage msg;
  msg.write((uint8_t*)text.c_str(), text.length());
  udp.sendTo(msg, hub, udp_port);
}

void setup() {
  delay(2000);

  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println(F("suspensionrt/satellite"));

  if (TOF_PIN_GND >= 0) {
    pinMode(TOF_PIN_GND, OUTPUT);
    digitalWrite(TOF_PIN_GND, LOW);
  }
  if (TOF_PIN_VIN >= 0) {
    pinMode(TOF_PIN_VIN, OUTPUT);
    digitalWrite(TOF_PIN_VIN, HIGH);
  }

  Wire.begin(TOF_PIN_SDA, TOF_PIN_SCL);
  if (!tof.begin(TOF_ADDRESS, &Wire)) {
    Serial.print(F("Error on init of VL sensor: "));
    Serial.println(tof.vl_status);
    while (1) delay(10);
  }
  Serial.println(F("VL53L1X sensor OK!"));

  Serial.print(F("Sensor ID: 0x"));
  Serial.println(tof.sensorID(), HEX);

  if (! tof.startRanging()) {
    Serial.print(F("Couldn't start ranging: "));
    Serial.println(tof.vl_status);
    while (1) delay(10);
  }
  Serial.println(F("Ranging started"));

  // Valid timing budgets: 15, 20, 33, 50, 100, 200 and 500ms!
  tof.setTimingBudget(50);
  Serial.print(F("Timing budget (ms): "));
  Serial.println(tof.getTimingBudget());

  connectToWifi();
}

unsigned long lastSend = 0;

void loop() {
  int16_t distance;

  if (tof.dataReady()) {
    distance = tof.distance();
    if (distance == -1) {
      Serial.print(F("Couldn't get distance: "));
      Serial.println(tof.vl_status);
      return;
    }
    sendPacket(MSG_PREFIX + MSG_TYPE_TOF + "\n" + WiFi.macAddress() + "\n" + distance);
    tof.clearInterrupt();
  }
}
