#include <iostream>
#include "App.h"

int Connect_to_server(const char* &ip, const int &port) {

    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    serverAddr.sin_port = htons(port);

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Failed to connect to server." << std::endl;
        close(clientSocket);
        return 1;
    }

    std::cout << "Connected!" << std::endl;

    // Limit to send(10 min send)
    int counter = 1200;
    while (true) {
        std::string data = Get_mouse_activity();
        send(clientSocket, data.c_str(), data.size(), 0);
        usleep(500000);
        if (counter == 0) break;
        counter--;
    }

    close(clientSocket);

    return 0;
}