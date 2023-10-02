#include <iostream>
#include "App.h"

int Connect_to_server(const char* &ip, const int &port) { // Connect to server gets mouse activity

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

    std::string ActiveKey = ""; // I don't see locking of this variable
    std::thread Mouse_Activity(checkMouseEventshelp, std::ref(ActiveKey));

    // Limit to send
    int counter = 1200; // for loop will look better
    while (1) {
        //Read mouse cursor
        std::string data = Get_mouse_activity();

        usleep(500000); // chrono sleep

        std::string temp = ActiveKey;
        data += temp;
        std::cout << temp << ' ';
        send(clientSocket, data.c_str(), data.size(), 0);
        if (counter == 0) break;
        counter--;
    }

    Mouse_Activity.detach(); // looks suspicious

    close(clientSocket);

    return 0;
}