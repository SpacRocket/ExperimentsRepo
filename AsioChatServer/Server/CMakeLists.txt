cmake_minimum_required(VERSION 3.22)
project(Server)

find_package(Boost REQUIRED system)


set(CMAKE_CXX_STANDARD 14)
set(Source_Files main.cpp include/asio_generic_server.h include/chat_handler.h)

add_executable(Server ${Source_Files})
target_link_libraries(Server PUBLIC Boost::system)
target_include_directories(Server PUBLIC include){