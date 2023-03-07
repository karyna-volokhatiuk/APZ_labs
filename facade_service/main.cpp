#include <httpserver.hpp> // https://github.com/etr/libhttpserver
#include <cpr/cpr.h> // https://github.com/libcpr/cpr // https://docs.libcpr.org/introduction.html#post-requests
#include <boost/uuid/random_generator.hpp> // https://www.boost.org/doc/libs/1_65_0/libs/uuid/uuid.html#boost/uuid/random_generator.hpp
#include <boost/uuid/uuid_io.hpp>
#include <spdlog/spdlog.h> // https://github.com/gabime/spdlog
#include <string>

namespace hs = httpserver;

class FacadeController : public hs::http_resource {
public:

    std::shared_ptr<hs::http_response> render_POST(const hs::http_request &req) override{

        spdlog::info("Received POST request");
        std::string req_content = std::string(req.get_content());
        spdlog::info("Content of request: ", req_content);
        spdlog::info("Generating UUID");
        boost::uuids::uuid uuid = uuid_generator();
        std::string uuid_str = boost::uuids::to_string(uuid);
        spdlog::info("Generated UUID: " + uuid_str);

        spdlog::info("Sending POST request to http://" + ip_logging + ":" + port_logging + "/logging-service");
        cpr::Response response_logging =
                cpr::Post(cpr::Url{"http://" + ip_logging + ":" + port_logging + "/logging-service"},
                          cpr::Payload{{uuid_str, req_content}});
        spdlog::info("Status code of response: " + std::to_string(response_logging.status_code));
        return std::shared_ptr<hs::http_response>(new hs::string_response(""));
    }

    std::shared_ptr<hs::http_response> render_GET(const hs::http_request &req) override{
        spdlog::info("Received GET request");

        spdlog::info("Sending GET request to http://" + ip_logging + ":" + port_logging + "/logging-service");
        cpr::Response response_logging =
                cpr::Get(cpr::Url{"http://" + ip_logging + ":" + port_logging + "/logging-service"});
        spdlog::info("Status code of response: " + std::to_string(response_logging.status_code));

        spdlog::info("Sending GET request to http://" + ip_messages + ":" + port_messages + "/messages-service");
        cpr::Response response_messages =
                cpr::Get(cpr::Url{"http://" + ip_messages + ":" + port_messages + "/messages-service"});
        spdlog::info("Status code of response: " + std::to_string(response_messages.status_code));
        return std::shared_ptr<hs::http_response>(new hs::string_response("\nlogging-service GET response: " +
                                                                          response_logging.text  +
                                                                          "\nmessages-service GET response: " +
                                                                          response_messages.text + "\n"));
    }

private:
    std::string ip_logging = "10.0.0.3";
    std::string ip_messages = "10.0.0.4";

    std::string port_facade = "8080";
    std::string port_logging = "8081";
    std::string port_messages = "8082";

    boost::uuids::random_generator uuid_generator;
};

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
    // Marks all HTTP methods as not allowed.
    spdlog::info("Allowing and disallowing method on a resource");
    fc.disallow_all();
    // Used to allow or disallow a method.
    fc.set_allowing("POST", true);
    fc.set_allowing("GET", true);
    spdlog::info("Register a resource");
    ws.register_resource("/facade-service", &fc);

    // Allows to start a server. If the blocking flag is passed
    // as true, it will block the execution of the current
    // thread until a call to stop on the same webserver
    // object is performed.
    spdlog::info("Start server");
    ws.start(true);

    return 0;
}
