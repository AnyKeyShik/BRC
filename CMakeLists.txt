cmake_minimum_required(VERSION 3.10)
project(BRС)

set(CMAKE_CXX_STANDARD 11)

include_directories(include src)

add_executable(BRC
        main.cpp src/crypto.cpp include/crypto.h src/utils.cpp include/utils.h)
