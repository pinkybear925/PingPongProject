cmake_minimum_required(VERSION 3.20)
project(PingPongProject)
set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(server src/server.cpp)
add_executable(client src/client.cpp)


