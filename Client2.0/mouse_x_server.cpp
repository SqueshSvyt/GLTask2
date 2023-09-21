#include "App.h"

#define MOUSEFILE "/dev/input/event4"

std::string Get_mouse_activity() {
    Display* display = XOpenDisplay(nullptr);
    std::string data = "";

    if (display) {
        int root_x, root_y;
        Window root, child;
        unsigned int mask;

        if (XQueryPointer(display, DefaultRootWindow(display), &root, &child, &root_x, &root_y, &root_x, &root_y, &mask)) {
            data += std::to_string(root_x) + 'x' + std::to_string(root_y) + ' ';
        }

        XCloseDisplay(display);
    }

    return data;
}

void checkMouseEventshelp(std::string& stopFlag) {
    std::ifstream mouseFile(MOUSEFILE, std::ios::binary);

    if(mouseFile.is_open() == -1){
        std::cout << "Cant read mouse click!";
        return;
    }

    struct input_event ie;
    while (mouseFile.read(reinterpret_cast<char *>(&ie), sizeof(struct input_event))) {    
        stopFlag = "";
        if (ie.type == EV_KEY) {
            if (ie.code == BTN_LEFT) {
                if (ie.value == 1) {
                    stopFlag = " LMK";
                    usleep(500000);
                } 
            } else if (ie.code == BTN_RIGHT) {
                if (ie.value == 1) {
                    stopFlag = " RMK";
                    usleep(500000);
                } 
            }
        } 
    }
    mouseFile.close();
}