#suspensionrt satellite

This satellite serves as a wireless sensor to report time-of-flight measurements to the hub for display.  It can use most ESP32 boards, but was designed to be used with [this one](https://www.amazon.com/dp/B0BCJXDYLY) which incorporates a lipo battery charger on the board.  A VL53L1X sensor like [this one](https://www.amazon.com/dp/B0DC6M6G7W) must be connected to the board.  Pin configurations are provided for multiple boards (select the appropriate board by uncommenting the appropriate board `#define` like `ESP32_LITE_CHARGER`), but generally simply choose 6 adjacent pins and provide all electrical signals including ground and Vcc via ESP32 GPIO pins.

Sensor data is sent to the hub via UDP packets.  The source of the sensor measurement can be determined by inspecting the MAC address of the source of the UDP packet, so this satellite doesn't need to include any sender information.
