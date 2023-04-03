#ifndef _FACADESERVICE_H
#define _FACADESERVICE_H

#include <cpr/cpr.h> // https://github.com/libcpr/cpr // https://docs.libcpr.org/introduction.html#post-requests
#include <boost/uuid/random_generator.hpp> // https://www.boost.org/doc/libs/1_65_0/libs/uuid/uuid.html#boost/uuid/random_generator.hpp
#include <boost/uuid/uuid_io.hpp>
#include <spdlog/spdlog.h> // https://github.com/gabime/spdlog

#include "../domain/Message.h"

class FacadeService {
public:
    FacadeService();
    std::string add_msg(std::string& msg_text);
    std::string get_msgs();

private:
    std::string ip_logging = "127.0.0.1";
    std::string ip_messages = "127.0.0.1";

    cpr::Url url_messages_service;
    std::vector<cpr::Url> url_logging_service_vector;

    boost::uuids::random_generator uuid_generator{};

    cpr::Url get_random_logging_client();
    std::string get_logging_service_msgs();
    std::string get_messages_service_msgs();
};



#endif //_FACADESERVICE_H
