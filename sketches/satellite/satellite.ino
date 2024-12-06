// Uses libraries:
// Adafruit VL53L1X

#include <WiFi.h>
#include <AsyncUDP.h>
#include <Adafruit_VL53L1X.h>
#include "wifi_info.h"

#define TOF_PIN_VIN -1
#define TOF_PIN_GND 19
#define TOF_PIN_SDA 23
#define TOF_PIN_SCL 18
#define TOF_PIN_INT 5
#define TOF_PIN_XSHUT 17
#define TOF_ADDRESS 0x29

#define LED_PIN 22

enum ErrorCode : uint8_t {
  WifiConectionFailure = 1,
  WifiReconectionFailure = 2,
  SensorInitializationFailure = 3,
  RangingStartFailure = 4,
};

Adafruit_VL53L1X tof = Adafruit_VL53L1X(TOF_PIN_XSHUT, TOF_PIN_INT);

AsyncUDP udp;
IPAddress hub(192, 168, 4, 1);
String mac_address;

void waitThenRestart(ErrorCode error_code) {
  // Blink out the error code
  pinMode(LED_PIN, OUTPUT);
  for (uint8_t i = 0; i < (uint8_t)error_code; i++) {
    digitalWrite(LED_PIN, LOW);
    delay(10);
    digitalWrite(LED_PIN, HIGH);
    esp_sleep_enable_timer_wakeup(300000);
    esp_light_sleep_start();
  }

  Serial.println("Restarting...");
  Serial.flush();
  esp_sleep_enable_timer_wakeup(10 * 1000000); // light sleep for 10 seconds
  esp_light_sleep_start();
  ESP.restart();
}

void connectToWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult(15000) != WL_CONNECTED) {
    Serial.println("WiFi could not connect");
    waitThenRestart(ErrorCode::WifiConectionFailure);
  }
  Serial.print("MAC address: ");
  Serial.println(WiFi.macAddress());
}

void startSensor() {
  if (TOF_PIN_GND >= 0) {
    pinMode(TOF_PIN_GND, OUTPUT);
    digitalWrite(TOF_PIN_GND, LOW);
  }
  if (TOF_PIN_VIN >= 0) {
    pinMode(TOF_PIN_VIN, OUTPUT);
    digitalWrite(TOF_PIN_VIN, HIGH);
  }

  Serial.println("Starting Wire");
  Wire.begin(TOF_PIN_SDA, TOF_PIN_SCL);
  Serial.println("Starting sensor");
  if (!tof.begin(TOF_ADDRESS, &Wire)) {
    Serial.print(F("Error on init of VL sensor: "));
    Serial.println(tof.vl_status);
    waitThenRestart(ErrorCode::SensorInitializationFailure);
  }
  Serial.println(F("VL53L1X sensor OK!"));

  Serial.print(F("Sensor ID: 0x"));
  Serial.println(tof.sensorID(), HEX);

  if (!tof.startRanging()) {
    Serial.print(F("Couldn't start ranging: "));
    Serial.println(tof.vl_status);
    waitThenRestart(ErrorCode::RangingStartFailure);
  }
  Serial.println(F("Ranging started"));

  // Valid timing budgets: 15, 20, 33, 50, 100, 200 and 500ms!
  tof.setTimingBudget(50);
  Serial.print(F("Timing budget (ms): "));
  Serial.println(tof.getTimingBudget());
}

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println(F("suspensionrt/satellite"));

  connectToWifi();
  startSensor();
}

void ensureStillConnected() {
  if (!WiFi.isConnected()) {
    Serial.println("WiFi disconnected");
    for (uint8_t attempt = 0; attempt < 3; attempt++) {
      if (WiFi.reconnect()) {
        return;
      }
      Serial.flush();
      esp_sleep_enable_timer_wakeup(1000000); // light sleep for 1 second
      esp_light_sleep_start();
    }
    Serial.println("Could not reconnect WiFi");
    waitThenRestart(ErrorCode::WifiReconectionFailure);
  }
}

void sendPacket(String text) {
  AsyncUDPMessage msg;
  msg.write((uint8_t*)text.c_str(), text.length());
  udp.sendTo(msg, hub, udp_port);
}

void loop() {
  ensureStillConnected();

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
