#include <hazelcast/client/hazelcast_client.h>
#include <thread>

void optimistic_locking(const std::string& key) {

    auto hz = hazelcast::new_client().get();
    auto map = hz.get_map("map").get();


    for (size_t k = 0; k < 1000; k++) {
        for(;;) {
            auto old_val = map->get<std::string, int>(key).get();
            int new_val = *old_val;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            new_val++;
            if (map->replace(key, *old_val, new_val).get()) {
                break;
            }
        }
    }
    hz.shutdown().get();
}

void pessimistic_locking(const std::string& key) {

    auto hz = hazelcast::new_client().get();
    auto map = hz.get_map("map").get();


    for (size_t k = 0; k < 1000; k++) {
        map->lock(key).get();
        try {
            auto val = map->get<std::string, int>(key).get();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            ++(*val);
            map->put(key, *val).get();
            map->unlock(key).get();
        } catch (hazelcast::client::exception::iexception& e) {
            map->unlock(key).get();
            throw e;
        }
    }
    hz.shutdown().get();
}

void without_locking(const std::string& key) {

    auto hz = hazelcast::new_client().get();
    auto map = hz.get_map("map").get();

    for (size_t k = 0; k < 1000; k++) {
        auto val = map->get<std::string, int>(key).get();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        ++(*val);
        map->put(key, *val).get();
    }
    hz.shutdown().get();
}

int main() {
    char locking_type = 'w';

    switch(locking_type) {
        case 'o':
            std::cout << "Test optimistic_locking";
            break;
        case 'p':
            std::cout << "Test pessimistic_locking";
            break;
        case 'w':
            std::cout << "Test without_locking";
            break;
    }
    std::cout << std::endl;

    std::string key = "1";

    auto hz = hazelcast::new_client().get();
    auto map = hz.get_map("map").get();

    map->put<std::string, int>(key, 0).get();

    std::vector<std::thread> threads;

    std::cout << "Starting" << std::endl;

    for (size_t i = 0; i < 3; i++) {
        std::cout << "thread " << i << std::endl;
        switch(locking_type) {
            case 'o':
                threads.emplace_back(optimistic_locking, key);
                break;
            case 'p':
                threads.emplace_back(pessimistic_locking, key);
                break;
            case 'w':
                threads.emplace_back(without_locking, key);
                break;
        }
    }

    std::cout << "\nFinishing" << std::endl;
    for (size_t i = 0; i < 3; i++) {
        threads[i].join();
        std::cout << "thread " << i << std::endl;
    }
    std::cout << "Finished";

    std::cout << "Result " << *(map->get<std::string, int>(key).get()) << std::endl;
    hz.shutdown().get();

    return 0;
}