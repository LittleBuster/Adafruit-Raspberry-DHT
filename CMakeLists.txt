cmake_minimum_required(VERSION 2.8)
project(dht22)

include_directories(".")
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pedantic -Wall -O2")
set(SRC_LIST piio.cpp dht22.cpp)

add_library(${PROJECT_NAME} SHARED ${SRC_LIST})

install (FILES build/libdht22.so DESTINATION /usr/lib/)
install (FILES dht22.h DESTINATION /usr/include/)
