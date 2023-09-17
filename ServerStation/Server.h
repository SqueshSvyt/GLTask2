#ifndef SERVERSTATION_SERVER_H
#define SERVERSTATION_SERVER_H

#include <iostream>
#include <fstream>

#ifdef _WIN32
//Windows part
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#elif unix
//Linux part
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstring>

#endif

int Run_server(const int& port);

#endif
