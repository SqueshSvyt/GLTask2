cmake_minimum_required(VERSION 3.23)
project(ServerStation)

set(CMAKE_CXX_STANDARD 17)

set(server_sources start.cpp)
set(target_lib)

if(WIN32)
    list(APPEND target_lib ws2_32)
    list(APPEND server_sources ServerWin32.cpp)
elseif(UNIX)
    list(APPEND target_lib pthread)
    list(APPEND server_sources ServerUnix.cpp)
endif()

add_executable(ServerStation ${server_sources})
target_link_libraries(ServerStation ${target_lib})