# suspensionrt

This project is intended to monitoring suspension travel on all four corners of an offroad vehicle in real time.  The [hub](./hub) is PlatformIO firmware for a "cheap yellow display" (ESP32 + touchscreen LCD module) that hosts a WiFi access point (AP) and displays "real-time" suspension compression.  Suspension compression data is captured by [satellites](./satellite), one for each wheel/corner of the truck, using a VL53L1X time-of-flight sensor.  It is transmitted to the hub by connection to the hub's AP and transmission of UDP packets.
