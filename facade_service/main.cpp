#include <httpserver.hpp> // https://github.com/etr/libhttpserver
#include <cpr/cpr.h> // https://github.com/libcpr/cpr // https://docs.libcpr.org/introduction.html#post-requests
#include <boost/uuid/random_generator.hpp> // https://www.boost.org/doc/libs/1_65_0/libs/uuid/uuid.html#boost/uuid/random_generator.hpp
#include <boost/uuid/uuid_io.hpp>
#include <spdlog/spdlog.h> // https://github.com/gabime/spdlog
#include <string>

#include "controller/FacadeController.h"

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
    FacadeController fc{port};

    spdlog::info("Register a resource");
    ws.register_resource("/facade-service", &fc);

    spdlog::info("Start server");
    ws.start(true);

    return 0;
}
