#ifndef APZ_LABS_MESSAGESSERVICE_H
#define APZ_LABS_MESSAGESSERVICE_H

#include <hazelcast/client/hazelcast.h>
using namespace hazelcast::client;
#include "../repository/MessagesRepository.h"

class MessagesService {
public:
    MessagesService();
    void save_msgs_from_queue();
    std::vector<std::string> get_saved_msgs();
private:
    hazelcast::client::hazelcast_client hz;
    std::shared_ptr<iqueue> hz_queue;

    MessagesRepository msgs_rep;
};


#endif //APZ_LABS_MESSAGESSERVICE_H
