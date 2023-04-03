#ifndef LOGGING_SERVICE_HAZELCASTLOGGINGSERVICE_H
#define LOGGING_SERVICE_HAZELCASTLOGGINGSERVICE_H

#include <spdlog/spdlog.h> // https://github.com/gabime/spdlog
#include <hazelcast/client/hazelcast.h>
using namespace hazelcast::client;

#include "../domain/Message.h"

class HazelcastLoggingService {
public:
    HazelcastLoggingService();
    void add_log(const Message& msg);
    std::vector<Message> get_logs();
private:
    hazelcast::client::hazelcast_client hz;
    std::shared_ptr<imap> hz_map;
};



#endif //LOGGING_SERVICE_HAZELCASTLOGGINGSERVICE_H
