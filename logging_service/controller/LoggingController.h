#ifndef LOGGING_SERVICE_LOGGINGCONTROLLER_H
#define LOGGING_SERVICE_LOGGINGCONTROLLER_H

#include "../service/LoggingService.h"
#include "../domain/Message.h"

#include <httpserver.hpp> // https://github.com/etr/libhttpserver
#include <spdlog/spdlog.h> // https://github.com/gabime/spdlog
#include <hazelcast/client/hazelcast.h>

namespace hs = httpserver;

class LoggingController : public hs::http_resource {
public:
    LoggingController(int port);
    std::shared_ptr<hs::http_response> render_POST(const hs::http_request &req) override;
    std::shared_ptr<hs::http_response> render_GET(const hs::http_request &req) override;

private:
    LoggingService ls;
};


#endif //LOGGING_SERVICE_LOGGINGCONTROLLER_H
