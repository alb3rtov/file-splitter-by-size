#ifndef _MAIN_
#define _MAIN_

#include <iostream>
#include <vector>
#include <string>
#include <tchar.h>

#include "Menu.cpp"
#include "..\include\colors.hpp"
#include "..\include\definitions.hpp"

/* Generate make copy menu */
void make_copy_menu() {
    std::vector<std::string> option_vector = {"1. Cozas1",
                                            "2. Cozas12",
                                            "3. Cozas123",
                                            "4. Back"};
    std::vector<void (*)()> function_vector;

    //function_vector.push_back(function12);
    //function_vector.push_back(function13);
    //function_vector.push_back(function12);

    Menu second_menu(option_vector, function_vector);
    display_banner(false);
    create_generic_menu(second_menu);
    display_banner(false);
}

/* Get type of drive */
void DisplayDriveType(int iParam)
{
    switch (iParam)
    {
    case DRIVE_UNKNOWN:
        std::cout << "Drive type unknown" << std::endl;
        break;

    case DRIVE_NO_ROOT_DIR:
        std::cout << "No drive for that root path" << std::endl;
        break;

    case DRIVE_REMOVABLE:
        std::cout << "Removable drive" << std::endl;
        break;

    case DRIVE_FIXED:
        std::cout << "Fixed drive" << std::endl;
        break;

    case DRIVE_REMOTE:
        std::cout << "Network drive" << std::endl;
        break;

    case DRIVE_CDROM:
        std::cout << "CD ROM drive" << std::endl;
        break;
    }
}

/* Display all logical drives information of the machine */
void list_drives()
{
    TCHAR sz_buffer[256];
    TCHAR *tch_ptr = sz_buffer;
    GetLogicalDriveStrings(255, sz_buffer);

    TCHAR sz_drive[] = _T(" A:");
    DWORD u_drive_mask = GetLogicalDrives();

    if (u_drive_mask == 0)
    {
        std::cout << "GetLogicalDrives() failed with failure code: " << GetLastError() << std::endl;
    }

    else
    {
        std::cout << "This machine has the following logical drives:\n" << std::endl;
        while (u_drive_mask)
        {
            if (u_drive_mask & 1)  /* Use the bitwise AND, 1–available, 0-not available */
            {
                std::cout << sz_drive << " ";
                DisplayDriveType(GetDriveType(tch_ptr));
                tch_ptr += _tcslen(tch_ptr) + 1;
            }
            ++sz_drive[1];
            u_drive_mask >>= 1; /* shift the bitmask binary right */
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

    function_vector.push_back(list_drives);
    function_vector.push_back(make_copy_menu);

    Menu main_menu(option_vector, function_vector);
    display_banner(true);
    create_generic_menu(main_menu);
}

#endif