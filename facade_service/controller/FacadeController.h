#ifndef _FACADECONTROLLER_H
#define _FACADECONTROLLER_H

#include <spdlog/spdlog.h> // https://github.com/gabime/spdlog
#include <httpserver.hpp> // https://github.com/etr/libhttpserver

#include "../service/FacadeService.h"

namespace hs = httpserver;

class FacadeController : public hs::http_resource {
public:
    FacadeController();
    std::shared_ptr<hs::http_response> render_POST(const hs::http_request &req) override;
    std::shared_ptr<hs::http_response> render_GET(const hs::http_request &req) override;

private:
    FacadeService fs;
};


#endif //_FACADECONTROLLER_H
