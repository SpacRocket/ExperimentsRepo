cmake_minimum_required(VERSION 3.0.0)
project(MultiThreadingBasics VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(MultiThreadingBasics main.cpp)
set_property(TARGET MultiThreadingBasics PROPERTY CXX_STANDARD 20)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
