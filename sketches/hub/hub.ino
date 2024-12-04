// Board: ESP32-WROOM-DA Module (esp32 by Espressif Systems 3.0.7)

// Uses libraries:
// Adafruit ILI9341 1.6.1

#include <WiFi.h>
#include <NetworkClient.h>
#include <WiFiAP.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <AsyncUDP.h>

#include "../../wifi_info.h"

typedef uint16_t length_t;

WebServer server(80);
AsyncUDP udp;

const length_t BUFFER_LENGTH = 255;
char buffer[BUFFER_LENGTH];

enum UDPMessageType : uint8_t {
  None,
  TimeOfFlight,
};

const length_t MAC_ADDRESS_LENGTH = 17;

struct Satellite {
  char mac_address[18];
  int last_distance;
};

const length_t MAX_SATELLITES = 8;
Satellite satellites[MAX_SATELLITES];
length_t n_satellites = 0;

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

length_t scanLine(char* s, length_t s_length, char* buffer) {
  for (length_t i = 0; i < s_length; i++) {
    if (s[i] == '\n') {
      buffer[i] = 0;
      return i + 1;
    }
    buffer[i] = s[i];
  }
  buffer[s_length] = 0;
  return s_length + 1;
}

bool startsWith(const char* prefix, char* str)
{
    return strncmp(prefix, str, strlen(prefix)) == 0;
}

UDPMessageType parseMessageType(char* line) {
  if (!startsWith(MSG_PREFIX.c_str(), line)) {
    Serial.print("UDP message did not have the right prefix: '");
    Serial.print(line);
    Serial.println("'");
    return UDPMessageType::None;
  }
  if (strcmp(MSG_TYPE_TOF.c_str(), line + MSG_PREFIX.length()) == 0) {
    return UDPMessageType::TimeOfFlight;
  }
  Serial.print("UDP message's type was invalid: '");
  Serial.print(line);
  Serial.println("'");
  return UDPMessageType::None;
}

void handleTimeOfFlight(uint8_t satellite, char* msg, length_t msg_length) {
  length_t n_line = scanLine(msg, msg_length, buffer);
  if (n_line < 2) {
    Serial.println("Time of flight message was missing distance payload");
    return;
  }
  int distance = atoi(buffer);
  satellites[satellite].last_distance = distance;
  Serial.print("S");
  Serial.print(satellite);
  Serial.print(": ");
  Serial.println(distance);
}

void onUDPPacket(AsyncUDPPacket packet) {
  char* msg = (char*)packet.data();
  length_t n = packet.length();  // n is number of characters in msg (without any terminator)
  if (n > BUFFER_LENGTH - 1) {
    Serial.println("UDP message size exceeds buffer length");
    return;
  }

  // Parse message type from first line
  length_t n_line = scanLine(msg, n, buffer);  // n_line is number of characters in line, including terminator character
  UDPMessageType msg_type = parseMessageType(buffer);
  if (msg_type == UDPMessageType::None) {
    return;
  }
  msg += n_line;
  n -= n_line;

  // Parse sender from second line
  n_line = scanLine(msg, n, buffer);
  if (n_line != MAC_ADDRESS_LENGTH + 1) {
    Serial.print("UDP message had invalid sender: '");
    Serial.print(buffer);
    Serial.println("'");
    return;
  }
  msg += n_line;
  n -= n_line;

  // Match sender to satellite
  uint8_t s;
  for (s = 0; s < n_satellites; s++) {
    if (strcmp(satellites[s].mac_address, buffer) == 0) {
      break;
    }
  }
  if (s >= n_satellites) {
    // We haven't seen this satellite before
    if (s >= MAX_SATELLITES) {
      // We've identified too many satellites; overwrite one
      s -= 1;
    }
    n_satellites = s + 1;
    for (uint8_t c = 0; c < MAC_ADDRESS_LENGTH + 1; c++) {
      satellites[s].mac_address[c] = buffer[c];
    }
  }

  // Handle specific message types
  if (msg_type == UDPMessageType::TimeOfFlight) {
    handleTimeOfFlight(s, msg, n);
  }
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
