#ifndef LOGGING_SERVICE_MESSAGE_H
#define LOGGING_SERVICE_MESSAGE_H

#include <string>

struct Message{
    std::string uuid;
    std::string text;

    Message(std::string uuid, std::string text) : uuid(std::move(uuid)), text(std::move(text)){}
};

#endif //LOGGING_SERVICE_MESSAGE_H
