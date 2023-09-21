#include <iostream>
#include "App.h"

int Connect_to_server(const char* &ip, const int &port) {

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
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    serverAddr.sin_port = htons(port);

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Failed to connect to server." << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected!" << '\n';

    //Limit to send(10 min send)
    int counter = 1200;
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
