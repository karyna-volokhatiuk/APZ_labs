cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME messages_service)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp controller/MessagesController.cpp controller/MessagesController.h service/MessagesService.cpp service/MessagesService.h repository/MessagesRepository.cpp repository/MessagesRepository.h)

include(cmake_files/FindLibHttpServer.cmake)
target_include_directories(${PROJECT_NAME} PRIVATE ${LIBHTTPSERVER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBHTTPSERVER_LIBRARIES})

find_package(spdlog REQUIRED)
target_include_directories(${PROJECT_NAME} PRIVATE spdlog)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog)

find_package(hazelcast-cpp-client CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} hazelcast-cpp-client::hazelcast-cpp-client)
