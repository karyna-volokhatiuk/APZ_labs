#include "MessagesController.h"

MessagesController::MessagesController(): ms(){
    disallow_all();
    set_allowing("GET", true);
}

std::shared_ptr<hs::http_response> MessagesController::render_GET(const hs::http_request &req) {
    spdlog::info("Received GET request by MessagesController");
    spdlog::info("Creating an output string");
    std::string output_str{};
    for (const auto& text : ms.get_saved_msgs()) {
        output_str += text + " ";
    }
    spdlog::info("All content was added to an output string");

    spdlog::info("Sending a response: " + output_str);
    return std::shared_ptr<hs::http_response>(new hs::string_response(output_str));
}

void MessagesController::save_msgs_from_queue(){
    ms.save_msgs_from_queue();
}