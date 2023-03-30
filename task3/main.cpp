#include <hazelcast/client/hazelcast.h>
#include <string>

using namespace hazelcast::client;

int main()
{
    auto hz = hazelcast::new_client().get();
    auto map = hz.get_map("my-distributed-map").get();

    for (size_t i = 0; i < 1000; ++i) {
        map->put<std::string, std::string>(std::to_string(i), "value_" + std::to_string(i)).get();
    }

    return 0;
}