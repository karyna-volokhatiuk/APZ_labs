#ifndef _FACADESERVICE_H
#define _FACADESERVICE_H

#include <cpr/cpr.h> // https://github.com/libcpr/cpr // https://docs.libcpr.org/introduction.html#post-requests
#include <boost/uuid/random_generator.hpp> // https://www.boost.org/doc/libs/1_65_0/libs/uuid/uuid.html#boost/uuid/random_generator.hpp
#include <boost/uuid/uuid_io.hpp>
#include <spdlog/spdlog.h> // https://github.com/gabime/spdlog
#include <string>
#include <hazelcast/client/hazelcast.h>
#include <ppconsul/agent.h> // https://github.com/oliora/ppconsul/tree/master // https://developer.hashicorp.com/consul/downloads
#include <ppconsul/kv.h>
#include <ppconsul/catalog.h>

using namespace hazelcast::client;
using ppconsul::Consul;

#include "../domain/Message.h"

class FacadeService {
public:
    FacadeService(int port);
    std::string add_msg_to_logging(std::string& msg_text);
    std::string get_msgs();
    void push_msg_to_mqueue(std::string& msg_text);


private:
    hazelcast::client::hazelcast_client hz;

    Consul consul;
    ppconsul::agent::Agent agent;
    ppconsul::catalog::Catalog catalog;
    ppconsul::kv::Kv kv;

    std::shared_ptr<iqueue> hz_queue;

    std::string consul_log_serv = "logging-service";
    std::string consul_msg_serv = "messages-service";

    boost::uuids::random_generator uuid_generator{};

    std::string get_logging_service_msgs();
    std::string get_messages_service_msgs();

    cpr::Url get_service_url_consul(const std::string& name);
};



#endif //_FACADESERVICE_H
