#ifndef _DEFINITIONS_
#define _DEFINITIONS_

#include <iostream>
#include <fstream>
#include <thread>
#include <vector>

#include "..\src\Menu.cpp"
#include "..\include\colors.hpp"

#define KEY_UP 72           /* Up arrow character */
#define KEY_DOWN 80         /* Down arrow character */
#define KEY_ENTER '\r'      /* Enter key character */

std::vector<std::string> drive_list;

/* Returns a double of conversion of bytes to GB */
double convert_to_gigabytes(ULARGE_INTEGER total_bytes) {
    double kb = 0;
	double mb = 0;
	double gb = 0;

    kb = total_bytes.QuadPart/1024;
    mb = kb/1024;
    gb = mb/1024;

    return gb;
}

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