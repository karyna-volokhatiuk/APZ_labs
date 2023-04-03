#ifndef LOGGING_SERVICE_LOGGINGCONTROLLER_H
#define LOGGING_SERVICE_LOGGINGCONTROLLER_H

#include "../service/InMemoryLoggingService.h"
#include "../service/HazelcastLoggingService.h"
#include "../domain/Message.h"

#include <httpserver.hpp> // https://github.com/etr/libhttpserver
#include <spdlog/spdlog.h> // https://github.com/gabime/spdlog
#include <hazelcast/client/hazelcast.h>

namespace hs = httpserver;

class LoggingController : public hs::http_resource {
public:
    LoggingController();
    std::shared_ptr<hs::http_response> render_POST(const hs::http_request &req) override;
    std::shared_ptr<hs::http_response> render_GET(const hs::http_request &req) override;

private:
#ifdef DEBUG
    InMemoryLoggingService ls;
#else
    HazelcastLoggingService ls;
#endif
};


#endif //LOGGING_SERVICE_LOGGINGCONTROLLER_H
