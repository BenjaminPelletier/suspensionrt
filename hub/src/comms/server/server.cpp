#include "server.h"
#include "handlers.h"

#include <WebServer.h>

WebServer server(80);

void init_server() {
    server.on("/", []() { handleRoot(&server); });
    server.onNotFound([]() { handleNotFound(&server); });

    server.begin();
}

void server_tick() {
    server.handleClient();
}
