cmake_minimum_required(VERSION 3.23)
project(ServerStation)

set(CMAKE_CXX_STANDARD 17)

add_executable(ServerStation main.cpp)
target_link_libraries(ServerStation ws2_32)