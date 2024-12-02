// Uses libraries:
// Adafruit VL53L1X

#include "Adafruit_VL53L1X.h"

#define TOF_PIN_VIN 4
#define TOF_PIN_GND 5
#define TOF_PIN_SDA 6
#define TOF_PIN_SCL 7
#define TOF_PIN_INT 15
#define TOF_PIN_XSHUT 16
#define TOF_ADDRESS 0x29

Adafruit_VL53L1X tof = Adafruit_VL53L1X(TOF_PIN_XSHUT, TOF_PIN_INT);

void setup() {
  delay(2000);

  Serial.begin(115200);
  while (!Serial) delay(10);

  Serial.println(F("suspensionrt/satellite"));

  pinMode(TOF_PIN_GND, OUTPUT);
  digitalWrite(TOF_PIN_GND, LOW);
  pinMode(TOF_PIN_VIN, OUTPUT);
  digitalWrite(TOF_PIN_VIN, HIGH);

  Wire.begin(TOF_PIN_SDA, TOF_PIN_SCL);
  if (! tof.begin(TOF_ADDRESS, &Wire)) {
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

  /*
  vl.VL53L1X_SetDistanceThreshold(100, 300, 3, 1);
  vl.VL53L1X_SetInterruptPolarity(0);
  */
}

void loop() {
  int16_t distance;

  if (tof.dataReady()) {
    // new measurement for the taking!
    distance = tof.distance();
    if (distance == -1) {
      // something went wrong!
      Serial.print(F("Couldn't get distance: "));
      Serial.println(tof.vl_status);
      return;
    }
    Serial.println(distance);

    // data is read out, time for another reading!
    tof.clearInterrupt();
  }
}