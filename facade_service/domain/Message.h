#ifndef FACADE_SERVICE_MESSAGE_H
#define FACADE_SERVICE_MESSAGE_H

#include <string>

struct Message{
    std::string uuid;
    std::string text;

    Message(std::string uuid, std::string text) : uuid(std::move(uuid)), text(std::move(text)){}
};

#endif //FACADE_SERVICE_MESSAGE_H
