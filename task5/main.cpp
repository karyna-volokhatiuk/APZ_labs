#include <hazelcast/client/hazelcast.h>

using namespace hazelcast::client;

void produce(int producer_id) {

    auto hz = hazelcast::new_client().get();
    auto queue = hz.get_queue("my-bounded-queue").get();

    for (int i = 0; i < 100; ++i) {
        queue->put<int>(i).get();
        std::cout << "Producer " << producer_id << ": " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
    queue->put(-1);
    std::cout << "Producer finished" << std::endl;
    hz.shutdown().get();
}

void consume(int consumer_id) {

    auto hz = hazelcast::new_client().get();
    auto queue = hz.get_queue("my-bounded-queue").get();

    while(true) {
        auto item = queue->take<int>().get();
        std::cout << "Consumer " << consumer_id << ": " << item << std::endl;
        if (item == -1) {
            queue->put<int>(-1).get();
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }

    std::cout << "Consumer finished" << std::endl;
    hz.shutdown().get();
}

int main() {

    std::vector<std::thread> threads;
    std::cout << "thread 1: starting producer 1" << std::endl;
    threads.emplace_back(produce, 1);
    std::cout << "thread 2: starting consumer 1" << std::endl;
    threads.emplace_back(consume, 1);
    std::cout << "thread 3: starting consumer 2" << std::endl;
    threads.emplace_back(consume, 2);

    std::cout << "\nFinishing" << std::endl;
    for (size_t i = 0; i < 3; i++) {
        threads[i].join();
        std::cout << "thread " << i << std::endl;
    }
    std::cout << "Finished";

    return 0;
}