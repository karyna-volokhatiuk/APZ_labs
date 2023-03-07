#include <httpserver.hpp> // https://github.com/etr/libhttpserver
#include <spdlog/spdlog.h> // https://github.com/gabime/spdlog
#include <tbb/concurrent_unordered_map.h>

namespace hs = httpserver;

class LoggingController : public hs::http_resource {
public:

    std::shared_ptr<hs::http_response> render_POST(const hs::http_request &req) override{
        spdlog::info("Received POST request");
        auto args = req.get_args();
        spdlog::info("Content of request: ");
        for (const auto& arg : args) {
            spdlog::info("UUID: " + std::string(arg.first) + "; content: " + std::string(arg.second));
            uuid_msgs_map.insert(std::pair(std::string(arg.first), std::string(arg.second)));
        }

        spdlog::info("All content was added to a map");
        return std::shared_ptr<hs::http_response>(new hs::string_response(""));
    }

    std::shared_ptr<hs::http_response> render_GET(const hs::http_request &req) override{
        spdlog::info("Received GET request");

        spdlog::info("Creating an output string");
        std::string output_str{};
        for (const auto& pair : uuid_msgs_map) {
            spdlog::info("Adding content of UUID = " + pair.first + " : " + pair.second);
            output_str += pair.second + " ";
        }
        spdlog::info("All content was added to an output string");

        spdlog::info("Sending a response: " + output_str);
        return std::shared_ptr<hs::http_response>(new hs::string_response(output_str));
    }

private:
    tbb::concurrent_unordered_map<std::string , std::string> uuid_msgs_map;
};

int main(int argc, char** argv) {
    spdlog::info("Creating server");
    int port = 8081;
    spdlog::info("Port: " + std::to_string(port));
    hs::webserver ws = hs::create_webserver(port);

    spdlog::info("Creating a resource");
    LoggingController lc;

    spdlog::info("Allowing and disallowing method on a resource");
    lc.disallow_all();
    lc.set_allowing("POST", true);
    lc.set_allowing("GET", true);
    spdlog::info("Register a resource");
    ws.register_resource("/logging-service", &lc);

    spdlog::info("Start server");
    ws.start(true);
    return 0;
}
