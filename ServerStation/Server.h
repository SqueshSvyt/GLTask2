#ifndef SERVERSTATION_SERVER_H
#define SERVERSTATION_SERVER_H

#include <iostream>
#include <fstream>

#ifdef _WIN32
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#elif __UNIX__
//Unix part include

#endif

int Run_server(const int& port);

#endif
