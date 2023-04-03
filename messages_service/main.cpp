#include "controller/MessagesController.h"

int main(int argc, char** argv) {
    spdlog::info("Creating server");
    int port = 8081;
    spdlog::info("Port: " + std::to_string(port));
    hs::webserver ws = hs::create_webserver(port);

    spdlog::info("Creating a resource");
    MessagesController mc;

    spdlog::info("Register a resource");
    ws.register_resource("/messages-service", &mc);

    spdlog::info("Start server");
    ws.start(true);
    return 0;
}
