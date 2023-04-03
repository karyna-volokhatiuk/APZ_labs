#ifndef LOGGING_SERVICE_INMEMORYLOGGINGSERVICE_H
#define LOGGING_SERVICE_INMEMORYLOGGINGSERVICE_H

#include <spdlog/spdlog.h> // https://github.com/gabime/spdlog
#include <tbb/concurrent_unordered_map.h>

#include "../domain/Message.h"

class InMemoryLoggingService {
public:
    InMemoryLoggingService();
    void add_log(const Message& msg);
    std::vector<Message> get_logs();
private:
    tbb::concurrent_unordered_map<std::string , std::string> uuid_msgs_map;
};


#endif //LOGGING_SERVICE_INMEMORYLOGGINGSERVICE_H
