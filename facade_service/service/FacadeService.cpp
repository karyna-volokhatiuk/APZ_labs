#include "FacadeService.h"

FacadeService::FacadeService() {
    spdlog::info("Creating FacadeService... Messages service: ip = " + ip_messages +
                        ", port = 8081. Looging service: ip = " + ip_logging + ", ports: 8082, 8083, 8084");
    url_messages_service = cpr::Url{"http://" + ip_messages + ":8081/messages-service"};
    url_logging_service_vector = {cpr::Url{"http://" + ip_logging + ":8082/logging-service"},
                                  cpr::Url{"http://" + ip_logging + ":8083/logging-service"},
                                  cpr::Url{"http://" + ip_logging + ":8084/logging-service"}};
}

std::string FacadeService::add_msg(std::string& msg_text) {
    auto msg = Message{boost::uuids::to_string(uuid_generator()), msg_text};
    spdlog::info("Adding message: uuid = " + msg.uuid + " text = " + msg.text);
    auto url_logging_service = get_random_logging_client();
    spdlog::info("Sending POST request to chosen logging service: url = " + url_logging_service.str());
    cpr::Response response_logging =
            cpr::Post(url_logging_service,cpr::Payload{{msg.uuid, msg.text}});
    spdlog::info("Response of logging service: " + response_logging.text);
    return response_logging.text;
}

std::string FacadeService::get_msgs() {
    return get_logging_service_msgs() + " : " + get_messages_service_msgs();
}

cpr::Url FacadeService::get_random_logging_client() {
    return url_logging_service_vector[std::rand() % url_logging_service_vector.size()];
}

std::string FacadeService::get_logging_service_msgs() {
    spdlog::info("Getting messages from logging service");
    auto url_logging_service = get_random_logging_client();
    spdlog::info("Sending GET request to chosen logging service: url = " + url_logging_service.str());
    cpr::Response response_logging =
            cpr::Get(url_logging_service);
    spdlog::info("Response of logging service: " + response_logging.text);
    return response_logging.text;
}

std::string FacadeService::get_messages_service_msgs() {
    spdlog::info("Getting messages from messages service");
    cpr::Response response_messages =
            cpr::Get(url_messages_service);
    spdlog::info("Response of messages service: " + response_messages.text);
    return response_messages.text;
}