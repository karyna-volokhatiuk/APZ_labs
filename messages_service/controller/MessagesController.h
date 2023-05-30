#ifndef MESSAGES_SERVICE_MESSAGESCONTROLLER_H
#define MESSAGES_SERVICE_MESSAGESCONTROLLER_H

#include <spdlog/spdlog.h> // https://github.com/gabime/spdlog
#include <httpserver.hpp> // https://github.com/etr/libhttpserver
namespace hs = httpserver;
#include "../service/MessagesService.h"

class MessagesController : public hs::http_resource {
public:
    MessagesController(int port);
    std::shared_ptr<hs::http_response> render_GET(const hs::http_request &req) override;
    void save_msgs_from_queue();
private:
    MessagesService ms;
};


#endif //MESSAGES_SERVICE_MESSAGESCONTROLLER_H
