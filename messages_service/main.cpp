#include "controller/MessagesController.h"

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
    MessagesController mc{port};

    spdlog::info("Register a resource");
    ws.register_resource("/messages-service", &mc);

    spdlog::info("Start server");
    ws.start(false);

    while (true) {
        mc.save_msgs_from_queue();
    }

    return 0;
}
