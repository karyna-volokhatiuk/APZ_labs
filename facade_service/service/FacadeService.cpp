#include "FacadeService.h"

FacadeService::FacadeService(int port):
        hz{hazelcast::new_client().get()},
        consul{},
        agent(consul),
        catalog(consul),
        kv(consul){

    agent.registerService(
            ppconsul::agent::kw::name = "facade-service",
            ppconsul::agent::kw::address = "localhost",
            ppconsul::agent::kw::port = port,
            ppconsul::agent::kw::id = "facade-service-" + std::to_string(port)
    );

    auto msg_queue_name = kv.get("msg_queue_name", "none");
    if (msg_queue_name == "none") {
        spdlog::info("Message queue was not found by key msg_queue_name");
    }

    hz_queue = hz.get_queue(msg_queue_name).get();
}

std::string FacadeService::add_msg_to_logging(std::string& msg_text) {
    auto msg = Message{boost::uuids::to_string(uuid_generator()), msg_text};
    spdlog::info("Adding message: uuid = " + msg.uuid + " text = " + msg.text);
    auto url_logging_service = get_service_url_consul(consul_log_serv);
    spdlog::info("Sending POST request to chosen logging service: url = " + url_logging_service.str() \
                + "service = " + url_logging_service.str());
    cpr::Response response_logging =
            cpr::Post(url_logging_service,cpr::Payload{{msg.uuid, msg.text}});
    spdlog::info("Response of logging service: " + response_logging.text);
    return response_logging.text;
}

void FacadeService::push_msg_to_mqueue(std::string& msg_text) {
    spdlog::info("Pushing message to queue: " + msg_text);
    hz_queue->put<std::string>(msg_text);
}

std::string FacadeService::get_msgs() {
    return get_logging_service_msgs() + " : " + get_messages_service_msgs();
}

std::string FacadeService::get_logging_service_msgs() {
    spdlog::info("Getting messages from logging service");
    auto url_logging_service = get_service_url_consul(consul_log_serv);
    spdlog::info("Sending GET request to chosen logging service: url = " + url_logging_service.str());
    cpr::Response response_logging =
            cpr::Get(url_logging_service);
    spdlog::info("Response of logging service: " + response_logging.text);
    return response_logging.text;
}

std::string FacadeService::get_messages_service_msgs() {
    spdlog::info("Getting messages from messages service");
    auto url_messages_service = get_service_url_consul(consul_msg_serv);
    spdlog::info("Sending GET request to chosen messages service: url = " + url_messages_service.str());
    cpr::Response response_messages =
            cpr::Get(url_messages_service);
    spdlog::info("Response of messages service: " + response_messages.text);
    return response_messages.text;
}

cpr::Url FacadeService::get_service_url_consul(const std::string& name){
    auto services = catalog.service(name);
    auto random_service = services[rand() % services.size()];
    return "http://" + random_service.second.address + \
                ":" + std::to_string(random_service.second.port) + "/" + name;

}

