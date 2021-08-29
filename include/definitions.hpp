#ifndef _DEFINITIONS_
#define _DEFINITIONS_

#include <iostream>
#include <fstream>
#include <thread>

#include "..\src\Menu.cpp"
#include "..\include\colors.hpp"

#define KEY_UP 72           /* Up arrow character */
#define KEY_DOWN 80         /* Down arrow character */
#define KEY_ENTER '\r'      /* Enter key character */

/* Display banner */
void display_banner(bool slow)
{
    system("clear");
    std::string line;
    std::fstream file("banner");
    
    while (getline(file, line))
    {
        std::cout << line << std::endl;
        if (slow) {
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }
}

/* Clear and display banner and current menu */
void clear_display_banner_and_menu() {
    system("clear");
    display_banner(false);
}

#endif