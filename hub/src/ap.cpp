#include "ap.h"

#include <WiFi.h>
#include <WiFiAP.h>
#include "../../wifi_info.h"

IPAddress init_ap() {
    if (!WiFi.softAP(ssid, password)) {
        log_e("Soft AP creation failed.");
        while (1);
    }
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
    return myIP;
}
