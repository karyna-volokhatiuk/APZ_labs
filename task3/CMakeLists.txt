cmake_minimum_required(VERSION 3.15)

set(PROJECT_NAME task3)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)

find_package(hazelcast-cpp-client CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE hazelcast-cpp-client::hazelcast-cpp-client)
