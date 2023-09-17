#include <iostream>
#include "Server.h"

int main(){
    //Basic server setting
    const int port = 27027;

    //Basic interface
    char cm;
    std::cout << "Mouse activity server: " << '\n';
    std::cout << "Do you want start server[Y/N]: ";
    std::cin >> cm;
    switch (cm) {
        case 'Y':
            try {
                if(Run_server(port) == -1){
                    std::cout << "Internal server error!";
                    return 0;
                }
            }catch(const std::exception& e){
                std::cerr << "Error: " << e.what() << std::endl;
            }
            break;
        case 'N':
            std::cout << '\n' << "exit...";
            return 0;
        default:
            std::cout << "Unknown command!";
            return 0;
    }
    return 0;
}