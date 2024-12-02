#include <WiFi.h>
#include <NetworkClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <AsyncUDP.h>

#include "../wifi_info.h"

WebServer server(80);
AsyncUDP udp;

void handleRoot() {
  server.send(200, "text/plain", "hello from esp32!");
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void onUDPPacket(AsyncUDPPacket packet) {
  /*Serial.print("UDP Packet Type: ");
  Serial.print(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
  Serial.print(", From: ");
  Serial.print(packet.remoteIP());
  Serial.print(":");
  Serial.print(packet.remotePort());
  Serial.print(", To: ");
  Serial.print(packet.localIP());
  Serial.print(":");
  Serial.print(packet.localPort());
  Serial.print(", Length: ");
  Serial.println(packet.length());*/
  Serial.print(packet.remoteIP());
  Serial.print(": ");
  Serial.println((char*)packet.data());
}

void setup() {
  delay(2000);
  Serial.begin(115200);
  Serial.println("suspensionrt/hub");
  Serial.println("Configuring access point...");

  if (!WiFi.softAP(ssid, password)) {
    log_e("Soft AP creation failed.");
    while (1);
  }
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  if (MDNS.begin("suspensionrt_hub")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  if(!udp.listen(udp_port)) {
    log_e("UDP listening failed.");
    while (1);
  }
  udp.onPacket(onUDPPacket);
  Serial.print("UDP Listening on ");
  Serial.print(WiFi.localIP());
  Serial.print(":");
  Serial.println(udp_port);

  WiFi.setSleep(false);
}

void loop(void) {
  server.handleClient();
  delay(2);  //allow the cpu to switch to other tasks
}
