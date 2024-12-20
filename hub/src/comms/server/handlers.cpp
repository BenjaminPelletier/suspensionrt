#include "handlers.h"

#include <WebServer.h>
#include <WString.h>

void handleRoot(WebServer* server) {
  server->send(200, "text/plain", "Hello from SuspensionRT");
}

void handleNotFound(WebServer* server) {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server->uri();
  message += "\nMethod: ";
  message += (server->method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server->args();
  message += "\n";
  for (uint8_t i = 0; i < server->args(); i++) {
    message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
  }
  server->send(404, "text/plain", message);
}
