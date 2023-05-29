#include "FacadeController.h"

FacadeController::FacadeController() : fs(){
    disallow_all();
    // Used to allow or disallow a method.
    set_allowing("POST", true);
    set_allowing("GET", true);
};

std::shared_ptr<hs::http_response> FacadeController::render_POST(const hs::http_request &req){
    spdlog::info("Received POST request by FacadeController");
    std::string req_content = std::string(req.get_content());
    spdlog::info("Content of request: " + req_content);

    fs.push_msg_to_mqueue(req_content);
    auto response = fs.add_msg_to_logging(req_content);

    spdlog::info("Sending a response: " + response);
    return std::shared_ptr<hs::http_response>(new hs::string_response(response));

}

std::shared_ptr<hs::http_response> FacadeController::render_GET(const hs::http_request &req){
    spdlog::info("Received GET request by FacadeController");
    spdlog::info("Getting messages");
    auto response = fs.get_msgs();
    spdlog::info("Sending a response: " + response);
    return std::shared_ptr<hs::http_response>(new hs::string_response(response));
}