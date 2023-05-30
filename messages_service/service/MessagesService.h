#ifndef APZ_LABS_MESSAGESSERVICE_H
#define APZ_LABS_MESSAGESSERVICE_H

#include <hazelcast/client/hazelcast.h>
#include <ppconsul/agent.h> // https://github.com/oliora/ppconsul/tree/master // https://developer.hashicorp.com/consul/downloads
#include <ppconsul/kv.h>
#include <ppconsul/catalog.h>

using namespace hazelcast::client;
using ppconsul::Consul;

#include "../repository/MessagesRepository.h"

class MessagesService {
public:
    MessagesService(int port);
    void save_msgs_from_queue();
    std::vector<std::string> get_saved_msgs();

private:
    hazelcast::client::hazelcast_client hz;

    Consul consul;
    ppconsul::agent::Agent agent;
    ppconsul::catalog::Catalog catalog;
    ppconsul::kv::Kv kv;

    std::shared_ptr<iqueue> hz_queue;

    MessagesRepository msgs_rep;
};


#endif //APZ_LABS_MESSAGESSERVICE_H
