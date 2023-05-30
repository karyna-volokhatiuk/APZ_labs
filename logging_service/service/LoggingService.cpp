#include "LoggingService.h"

LoggingService::LoggingService(int port) :
        hz{hazelcast::new_client().get()},
        consul{},
        agent(consul),
        catalog(consul),
        kv(consul){

    spdlog::info("Creating HazelcastLoggingService");
    agent.registerService(
            ppconsul::agent::kw::name = "logging-service",
            ppconsul::agent::kw::address = "localhost",
            ppconsul::agent::kw::port = port,
            ppconsul::agent::kw::id = "logging-service-" + std::to_string(port)
    );

    auto map_name = kv.get("map_name", "none");
    if (map_name == "none") {
        spdlog::info("Map was not found by key map_name");
    }

    hz_map = hz.get_map(map_name).get();

};

void LoggingService::add_log(const Message& msg) {
    spdlog::info("Add message to HazelcastLoggingService: uuid = " + msg.uuid + ", text = " + msg.text);
    hz_map->put<std::string, std::string>(msg.uuid, msg.text).get();
    spdlog::info("Message was added");
};

std::vector<Message> LoggingService::get_logs() {
    spdlog::info("Getting logs from HazelcastLoggingService");
    std::vector<Message> logs;
    for (const auto &[msg_uuid, msg_text] : hz_map->entry_set<std::string, std::string>().get()) {
        logs.emplace_back(msg_uuid, msg_text);
        spdlog::info("Got log: uuid = " + msg_uuid + ", text = " + msg_text);
    }
    return logs;
};