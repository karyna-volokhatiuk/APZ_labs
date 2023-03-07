#include <httpserver.hpp> // https://github.com/etr/libhttpserver
#include <spdlog/spdlog.h> // https://github.com/gabime/spdlog

namespace hs = httpserver;

class MessagesController : public hs::http_resource {
public:

    std::shared_ptr<hs::http_response> render_GET(const hs::http_request &req) override{
        spdlog::info("Received GET request");
        std::string response = "Not implemented yet";
        spdlog::info("Sending a response: " + response);
        return std::shared_ptr<hs::http_response>(new hs::string_response(response));
    }

};

int main(int argc, char** argv) {
    spdlog::info("Creating server");
    int port = 8082;
    spdlog::info("Port: " + std::to_string(port));
    hs::webserver ws = hs::create_webserver(port);

    spdlog::info("Creating a resource");
    MessagesController mc;

    spdlog::info("Allowing and disallowing method on a resource");
    mc.disallow_all();
    mc.set_allowing("GET", true);
    spdlog::info("Register a resource");
    ws.register_resource("/messages-service", &mc);

    spdlog::info("Start server");
    ws.start(true);
    return 0;
}
