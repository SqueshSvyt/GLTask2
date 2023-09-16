#include <iostream>
#include <winsock2.h>
#include "ms_act.h"

#define _SERVER_IP "127.0.0.1"
#define _PORT 27027

#pragma comment(lib, "ws2_32.lib")

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock." << std::endl;
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(_SERVER_IP);
    serverAddr.sin_port = htons(_PORT);

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to server." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }
    std::cout << "Connected!" << '\n';
    int counter = 120;
    while (true) {
        std::string data = Get_mouse_activity();
        send(clientSocket, data.c_str(), data.size(), 0);
        Sleep(500);
        if(counter == 0) break;
        counter--;
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
