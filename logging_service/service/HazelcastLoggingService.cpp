#include "HazelcastLoggingService.h"

HazelcastLoggingService::HazelcastLoggingService() :
    hz{hazelcast::new_client().get()}, hz_map{hz.get_map("my-distributed-map").get()}{
    spdlog::info("Creating HazelcastLoggingService");
};

void HazelcastLoggingService::add_log(const Message& msg) {
    spdlog::info("Add message to HazelcastLoggingService: uuid = " + msg.uuid + ", text = " + msg.text);
    hz_map->put<std::string, std::string>(msg.uuid, msg.text).get();
    spdlog::info("Message was added");
};

std::vector<Message> HazelcastLoggingService::get_logs() {
    spdlog::info("Getting logs from HazelcastLoggingService");
    std::vector<Message> logs;
    for (const auto &[msg_uuid, msg_text] : hz_map->entry_set<std::string, std::string>().get()) {
        logs.emplace_back(msg_uuid, msg_text);
        spdlog::info("Got log: uuid = " + msg_uuid + ", text = " + msg_text);
    }
    return logs;
};