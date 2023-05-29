cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME facade_service)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp controller/FacadeController.cpp controller/FacadeController.h domain/Message.h service/FacadeService.cpp service/FacadeService.h)

include(cmake_files/FindLibHttpServer.cmake)

include(cmake_files/FindLibCpr.cmake)

target_include_directories(${PROJECT_NAME} PRIVATE ${LIBHTTPSERVER_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBHTTPSERVER_LIBRARIES})

target_include_directories(${PROJECT_NAME} PRIVATE ${LIBCPR_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${LIBCPR_LIBRARIES})


find_package(spdlog REQUIRED)

target_include_directories(${PROJECT_NAME} PRIVATE spdlog)
target_link_libraries(${PROJECT_NAME} spdlog::spdlog)

find_package(hazelcast-cpp-client CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} hazelcast-cpp-client::hazelcast-cpp-client)
