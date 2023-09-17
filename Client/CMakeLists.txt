cmake_minimum_required(VERSION 3.23)
project(Client)

set(CMAKE_CXX_STANDARD 17)

set(client_sources start.cpp)
set(target_lib)

if(WIN32)
    list(APPEND target_lib ws2_32)
    list(APPEND client_sources App_WIN32.cpp mouse_wingui.cpp)
elseif(UNIX)
    list(APPEND target_lib pthread)
    list(APPEND client_sources App_UNIX.cpp mouse_x_server.cpp)
endif()

add_executable(Client ${client_sources})
target_link_libraries(Client ${target_lib})