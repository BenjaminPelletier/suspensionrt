#include "ap.h"

#include <WiFi.h>
#include <WiFiAP.h>

const char* ssid = "SuspensionRT";
const char* password = "springconstant";

IPAddress my_ip_address;

void init_ap() {
    if (!WiFi.softAP(ssid, password)) {
        log_e("Soft AP creation failed.");
        while (1);
    }
    my_ip_address = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(my_ip_address);
    WiFi.setSleep(false);
}

IPAddress get_my_ip_address() {
    return my_ip_address;
}
