#include <spdlog/spdlog.h> // https://github.com/gabime/spdlog
#include "MessagesService.h"

MessagesService::MessagesService(int port) :
        hz{hazelcast::new_client().get()},
        consul{},
        agent(consul),
        catalog(consul),
        kv(consul){

    agent.registerService(
            ppconsul::agent::kw::name = "messages-service",
            ppconsul::agent::kw::address = "localhost",
            ppconsul::agent::kw::port = port,
            ppconsul::agent::kw::id = "messages-service-" + std::to_string(port)
    );

    auto msg_queue_name = kv.get("msg_queue_name", "none");
    if (msg_queue_name == "none") {
        spdlog::info("Message queue was not found by key msg_queue_name");
    }

    hz_queue = hz.get_queue(msg_queue_name).get();

};

void MessagesService::save_msgs_from_queue() {
    auto new_msg = hz_queue->take<std::string>().get();
    spdlog::info("Message service took new msg from queue: " + *new_msg);
    msgs_rep.add_msg(*new_msg);

};

std::vector<std::string> MessagesService::get_saved_msgs(){
    spdlog::info("Getting saved messages from MessagesService");
    auto msgs = msgs_rep.get_msgs();
    for (const auto &msg : msgs) {
        spdlog::info("Got saved msg: " + msg);
    }
    return msgs;
};