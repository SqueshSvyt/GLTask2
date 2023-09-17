#include "Server.h"

int Run_server(const int& port) {

    int serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (serverSocket == -1) {
        std::cerr << "Failed to create socket: " << strerror(errno) << '\n';
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        std::cerr << "Failed to bind socket: " << strerror(errno) << '\n';
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 1) == -1) {
        std::cerr << "Listen failed: " << strerror(errno) << '\n';
        close(serverSocket);
        return 1;
    }

    std::cout << "Server listening on port " << port << "..." << '\n';

    int clientSocket;
    sockaddr_in clientAddr;
    socklen_t clientAddrSize = sizeof(clientAddr);
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);

    if (clientSocket == -1) {
        std::cerr << "Failed to accept client connection: " << strerror(errno) << '\n';
        close(serverSocket);
        return 1;
    }

    std::ofstream logFile("mouse_activity.txt");
    logFile << "Get info from: " << inet_ntoa(clientAddr.sin_addr) << ":" << ntohs(clientAddr.sin_port) << '\n';

    while (true) {
        char buffer[256];
        int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead <= 0) {
            break; // Connection closed or error
        }
        buffer[bytesRead] = '\0';
        std::string str(buffer);
        logFile << str << '\n';
        std::cout << str << '\n';
    }

    logFile.close();
    close(clientSocket);
    close(serverSocket);

    return 0;
}