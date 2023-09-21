#include "App.h"

std::string Get_mouse_activity(){
    POINT cursor;
    std::string data = "";

    if(GetCursorPos(&cursor))
        data += std::to_string(cursor.x) + 'x' + std::to_string(cursor.y) + ' ';

    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
        data += "LMK ";

    if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
        data += "RMK ";

    if(GetAsyncKeyState(VK_XBUTTON1) & 0x8000)
        data += "X1B ";

    if(GetAsyncKeyState(VK_XBUTTON2) & 0x8000)
        data += "X2B ";

    return data;
}