#ifndef _MAIN_
#define _MAIN_

#include <iostream>
#include <vector>
#include <string>
#include <tchar.h>

#include "Menu.cpp"
#include "MainMFunctions.cpp"
#include "..\include\colors.hpp"
#include "..\include\definitions.hpp"

void DisplayDriveType(int iParam)
{
    switch (iParam)
    {
    case DRIVE_UNKNOWN:
        printf("Drive type unknown.\n");
        break;

    case DRIVE_NO_ROOT_DIR:
        printf("No drive for that root path.\n");
        break;

    case DRIVE_REMOVABLE:
        printf("Removable drive.\n");
        break;

    case DRIVE_FIXED:
        printf("Fixed drive.\n");
        break;

    case DRIVE_REMOTE:
        printf("Network drive.\n");
        break;

    case DRIVE_CDROM:
        printf("CD ROM drive.\n");
        break;
    }
}

LPCSTR GetString(std::string str)
{
    return str.c_str();
}

void list_removable_drives()
{
    TCHAR szBuffer[256];
    TCHAR *tchPtr = szBuffer;
    GetLogicalDriveStrings(255, szBuffer);

    TCHAR szDrive[] = _T(" A:");
    DWORD uDriveMask = GetLogicalDrives();

    if (uDriveMask == 0)
    {
        std::cout << "\n\nGetLogicalDrives() failed with failure code: " << GetLastError() << std::endl;
    }

    else
    {
        std::cout << "\n\nThis machine has the following logical drives:\n" << std::endl;
        while (uDriveMask)
        {
            if (uDriveMask & 1)  /* Use the bitwise AND, 1–available, 0-not available */
            {
                std::cout << szDrive << " ";
                DisplayDriveType(GetDriveType(tchPtr));
                tchPtr += _tcslen(tchPtr) + 1;
            }
            ++szDrive[1];
            uDriveMask >>= 1; /* shift the bitmask binary right */
        }
    }
}

/* Main function */
int main()
{
    std::vector<std::string> option_vector = {"1. List USB drives",
                                              "2. Make a copy",
                                              "3. Quit"};
    std::vector<void (*)()> function_vector;

    function_vector.push_back(list_removable_drives);
    function_vector.push_back(funcion2);

    Menu main_menu(option_vector, function_vector);
    display_banner(true);
    create_generic_menu(main_menu);
}

#endif