#include <httpserver.hpp> // https://github.com/etr/libhttpserver
#include <cpr/cpr.h> // https://github.com/libcpr/cpr // https://docs.libcpr.org/introduction.html#post-requests
#include <boost/uuid/random_generator.hpp> // https://www.boost.org/doc/libs/1_65_0/libs/uuid/uuid.html#boost/uuid/random_generator.hpp
#include <boost/uuid/uuid_io.hpp>
#include <spdlog/spdlog.h> // https://github.com/gabime/spdlog
#include <string>

#include "controller/FacadeController.h"

namespace hs = httpserver;

int main(int argc, char** argv) {
    //.start_method(const http::http_utils::start_method_T& start_method):
    // libhttpserver can operate with two different threading models that can
    // be selected through this method. Default value is INTERNAL_SELECT.
    spdlog::info("Creating server");
    int port = 8080;
    spdlog::info("Port: " + std::to_string(port));
    hs::webserver ws = hs::create_webserver(port);

    spdlog::info("Creating a resource");
    FacadeController fc;

    ws.register_resource("/facade-service", &fc);

    // Allows to start a server. If the blocking flag is passed
    // as true, it will block the execution of the current
    // thread until a call to stop on the same webserver
    // object is performed.
    spdlog::info("Start server");
    ws.start(true);

    return 0;
}
