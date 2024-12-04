#ifndef SUSPENSIONRT_COMMS_SERVER_HANDLERS_H
#define SUSPENSIONRT_COMMS_SERVER_HANDLERS_H

#include <WebServer.h>

void handleNotFound(WebServer* server);
void handleRoot(WebServer* server);

#endif
