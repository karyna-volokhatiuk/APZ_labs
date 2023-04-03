#include "LoggingController.h"

LoggingController::LoggingController() : ls(){
    disallow_all();
    // Used to allow or disallow a method.
    set_allowing("POST", true);
    set_allowing("GET", true);
};

std::shared_ptr<hs::http_response> LoggingController::render_POST(const hs::http_request &req) {
    spdlog::info("Received POST request by LoggingController");
    auto args = req.get_args();
    for (const auto& [uuid, text] : args) {
        ls.add_log({std::string(uuid), std::string(text)});
    }
    spdlog::info("All content was added to a map");
    return std::shared_ptr<hs::http_response>(new hs::string_response(""));
}

std::shared_ptr<hs::http_response> LoggingController::render_GET(const hs::http_request &req) {
    spdlog::info("Received GET request by LoggingController");

    spdlog::info("Creating an output string");
    std::string output_str{};
    for (const auto& [uuid, text] : ls.get_logs()) {
        output_str += text + " ";
    }
    spdlog::info("All content was added to an output string");

    spdlog::info("Sending a response: " + output_str);
    return std::shared_ptr<hs::http_response>(new hs::string_response(output_str));
}

