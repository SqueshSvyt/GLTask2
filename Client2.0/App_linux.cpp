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

    std::string ActiveKey = "";
    std::thread Mouse_Activity(checkMouseEventshelp, std::ref(ActiveKey));

    // Limit to send
    int counter = 1200;
    while (1) {
        //Read mouse cursor
        std::string data = Get_mouse_activity();

        usleep(500000);

        std::string temp = ActiveKey;
        data += temp;
        std::cout << temp << ' ';
        send(clientSocket, data.c_str(), data.size(), 0);
        if (counter == 0) break;
        counter--;
    }

    Mouse_Activity.detach();

    close(clientSocket);

    return 0;
}