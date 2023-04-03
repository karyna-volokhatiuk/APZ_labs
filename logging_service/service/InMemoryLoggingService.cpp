#include "InMemoryLoggingService.h"

InMemoryLoggingService::InMemoryLoggingService() {
    spdlog::info("Creating InMemoryLoggingService");

};

void InMemoryLoggingService::add_log(const Message& msg) {
    spdlog::info("Add message to InMemoryLoggingService: uuid = " + msg.uuid + ", text = " + msg.text);
    uuid_msgs_map.insert(std::pair(msg.uuid, msg.text));
    spdlog::info("Message was added");
};

std::vector<Message> InMemoryLoggingService::get_logs() {
    spdlog::info("Getting logs from HazelcastLoggingService");
    std::vector<Message> logs;
    for (auto& [msg_uuid, msg_text] : uuid_msgs_map) {
        logs.emplace_back(msg_uuid, msg_text);
        spdlog::info("Got log: uuid = " + msg_uuid + ", text = " + msg_text);
    }
    return logs;
};