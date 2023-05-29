#ifndef APZ_LABS_MESSAGESREPOSITORY_H
#define APZ_LABS_MESSAGESREPOSITORY_H

#include <vector>
#include <string>

class MessagesRepository {
public:
    void add_msg(const std::string& msg_text);
    std::vector<std::string> get_msgs();

private:
    std::vector<std::string> msgs_vector;
};


#endif //APZ_LABS_MESSAGESREPOSITORY_H
