#include "App.h"

//Cursor broken for Debian and event don`t work

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

        char keys[32];
        XQueryKeymap(display, keys);

        if (keys[0] & (1 << 0))
            data += "LMK ";

        if (keys[2] & (1 << 0))
            data += "RMK ";

        if (keys[2] & (1 << 3))
            data += "X1B ";

        if (keys[2] & (1 << 4))
            data += "X2B ";

        XCloseDisplay(display);
    }

    return data;
}