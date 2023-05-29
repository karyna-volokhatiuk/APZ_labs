#include <spdlog/spdlog.h> // https://github.com/gabime/spdlog
#include "MessagesService.h"

MessagesService::MessagesService() : hz{hazelcast::new_client().get()},
    hz_queue{hz.get_queue("my-distributed-queue").get()}{};

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