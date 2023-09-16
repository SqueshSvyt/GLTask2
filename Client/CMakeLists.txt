cmake_minimum_required(VERSION 3.23)
project(Client)

set(CMAKE_CXX_STANDARD 17)

add_executable(Client main.cpp ms_act.h ch_ms_ac.cpp)

target_link_libraries(Client ws2_32)