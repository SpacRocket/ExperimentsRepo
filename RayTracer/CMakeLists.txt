cmake_minimum_required(VERSION 3.0.0)
project(raytracer VERSION 0.1.0)
set_property(GLOBAL PROPERTY CXX_STANDARD 20)

include(CTest)
enable_testing()

add_executable(raytracer main.cpp)
target_compile_features(raytracer PUBLIC cxx_std_20)

target_include_directories(raytracer PUBLIC ./include)
target_include_directories(raytracer PUBLIC ./include/hittable)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
