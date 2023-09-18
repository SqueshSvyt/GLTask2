#ifndef CLIENT_APP_H
#define CLIENT_APP_H

#include <string>

#ifdef _WIN32
//Network
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

//Read mouse info
#include <windows.h>

#elif unix
//Network
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstring>

//Read mouse info
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#endif

std::string Get_mouse_activity();

int Connect_to_server(const char* &ip, const int &port);

#endif //CLIENT_APP_H
