#include "MessagesController.h"

MessagesController::MessagesController() {
    disallow_all();
    set_allowing("GET", true);
}

std::shared_ptr<hs::http_response> MessagesController::render_GET(const hs::http_request &req) {
    spdlog::info("Received GET request");
    std::string response = "Not implemented yet";
    spdlog::info("Sending a response: " + response);
    return std::shared_ptr<hs::http_response>(new hs::string_response(response));
}