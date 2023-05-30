#ifndef LOGGING_SERVICE_LOGGINGSERVICE_H
#define LOGGING_SERVICE_LOGGINGSERVICE_H

#include <spdlog/spdlog.h> // https://github.com/gabime/spdlog
#include <hazelcast/client/hazelcast.h>
#include <ppconsul/agent.h> // https://github.com/oliora/ppconsul/tree/master // https://developer.hashicorp.com/consul/downloads
#include <ppconsul/kv.h>
#include <ppconsul/catalog.h>

using namespace hazelcast::client;
using ppconsul::Consul;

#include "../domain/Message.h"

class LoggingService {
public:
    LoggingService(int port);
    void add_log(const Message& msg);
    std::vector<Message> get_logs();
private:
    hazelcast::client::hazelcast_client hz;

    Consul consul;
    ppconsul::agent::Agent agent;
    ppconsul::catalog::Catalog catalog;
    ppconsul::kv::Kv kv;

    std::shared_ptr<imap> hz_map;
};



#endif //LOGGING_SERVICE_LOGGINGSERVICE_H
