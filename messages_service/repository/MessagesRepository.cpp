#include "MessagesRepository.h"

void MessagesRepository::add_msg(const std::string& msg_text) {
    msgs_vector.push_back(msg_text);
}

std::vector<std::string> MessagesRepository::get_msgs() {
    return msgs_vector;
}