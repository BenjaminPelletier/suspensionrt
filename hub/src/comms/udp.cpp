#include "udp.h"
#include <Arduino.h>
#include <AsyncUDP.h>
#include "../events.h"

AsyncUDP udp;

const unsigned int udp_port = 31607;
const String MSG_PREFIX = F("SRT:");
const String MSG_TYPE_TOF = F("TOF");

time_of_flight_callback_t on_time_of_flight;

typedef uint16_t length_t;

const length_t BUFFER_LENGTH = 255;
char buffer[BUFFER_LENGTH];

enum UDPMessageType : uint8_t
{
    None,
    TimeOfFlight,
};

const length_t MAC_ADDRESS_LENGTH = 17;

struct Satellite
{
    char mac_address[18];
    int last_distance;
};

const length_t MAX_SATELLITES = 8;
Satellite satellites[MAX_SATELLITES];
length_t n_satellites = 0;

length_t scanLine(char *s, length_t s_length, char *buffer)
{
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

bool startsWith(const char *prefix, char *str)
{
    return strncmp(prefix, str, strlen(prefix)) == 0;
}

UDPMessageType parseMessageType(char *line)
{
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

void handleTimeOfFlight(uint8_t satellite, char *msg, length_t msg_length)
{
    length_t n_line = scanLine(msg, msg_length, buffer);
    if (n_line < 2) {
        Serial.println("Time of flight message was missing distance payload");
        return;
    }
    int distance = atoi(buffer);
    satellites[satellite].last_distance = distance;
    on_time_of_flight(satellite, distance);
    Serial.print("S");
    Serial.print(satellite);
    Serial.print(": ");
    Serial.println(distance);
}

void onUDPPacket(AsyncUDPPacket packet)
{
    char *msg = (char *)packet.data();
    length_t n = packet.length(); // n is number of characters in msg (without any terminator)
    if (n > BUFFER_LENGTH - 1) {
        Serial.println("UDP message size exceeds buffer length");
        return;
    }

    // Parse message type from first line
    length_t n_line = scanLine(msg, n, buffer); // n_line is number of characters in line, including terminator character
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

void init_udp(time_of_flight_callback_t time_of_flight_handler)
{
    on_time_of_flight = time_of_flight_handler;

    udp.onPacket(onUDPPacket);
    if (!udp.listen(udp_port)) {
        log_e("UDP listening failed.");
        while (1)
            ;
    }
}
