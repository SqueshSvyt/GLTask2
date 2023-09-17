#include <iostream>
#include "App.h"

int main(){
    //Setting
    const char *ip = "127.0.0.1";
    const int port = 27027;

    char cm;
    std::cout << "Mouse logger: " << '\n';
    std::cout << "Start log your info [Y/N]: ";
    std::cin >> cm;
    switch (cm) {
        case 'Y':
            try {
                if(Connect_to_server(ip, port) == -1){
                    std::cout << "Connecting error!";
                    return 0;
                }
            }catch(const std::exception& e){
                std::cerr << "Error: " << e.what() << std::endl;
            }
            break;
        case 'N':
            std::cout << '\n' << "Exit...";
            return 0;
        default:
            std::cout << "Unknown command!";
            return 0;
    }
    return 0;
}