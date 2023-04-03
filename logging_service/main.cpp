#include <httpserver.hpp> // https://github.com/etr/libhttpserver
#include <spdlog/spdlog.h> // https://github.com/gabime/spdlog

#include "controller/LoggingController.h"

namespace hs = httpserver;

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Incorrect number of arguments" << std::endl;
        return 1;
    }

    int port;
    try {
        port = std::stoi(argv[1]);
    } catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
        return 2;
    }

    spdlog::info("Creating server");
    spdlog::info("Port: " + std::to_string(port));
    hs::webserver ws = hs::create_webserver(port);

    spdlog::info("Creating a resource");
    LoggingController lc;

    spdlog::info("Register a resource");
    ws.register_resource("/logging-service", &lc);

    spdlog::info("Start server");
    ws.start(true);
    return 0;
}
