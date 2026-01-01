cmake_minimum_required(VERSION 4.0)

set(CMAKE_CXX_STANDARD 23)
project(lock-free-ds)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE
    utils
)
