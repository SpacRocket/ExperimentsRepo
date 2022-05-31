cmake_minimum_required(VERSION 3.22)
project(Server)

find_package(Boost REQUIRED system)

set(CMAKE_CXX_STANDARD 20)
set(Source_Files Server.cpp SimpleClient.cpp include/net_connection.h include/client.h include/server.h include/net_tsqueue.h include/net_server.h include/net_client.h)

add_executable(Server ${Source_Files})
add_executable(SimpleClient SimpleClient.cpp)

target_link_libraries(Server PUBLIC Boost::system)
target_include_directories(Server PUBLIC include)

target_link_libraries(SimpleClient PUBLIC Boost::system)
target_include_directories(SimpleClient PUBLIC include)
