#ifndef _MAIN_
#define _MAIN_

#include <iostream>
#include <vector>
#include <string>
#include <tchar.h>
#include <iomanip>

#include "Menu.cpp"
#include "copy_functions.cpp"
#include "..\include\colors.hpp"
#include "..\include\definitions.hpp"

/* Generate menu based on a Menu object */
void create_generic_menu(Menu menu, bool move_output) 
{
    int counter = 1;
    bool running = true;
    bool first_iteration = true;

    while (running)
    {  
        if (first_iteration) 
        {
            first_iteration = false;
            check_current_attrs_values();
        }
        menu.display_options();
        menu.check_last_input_character(counter, running, move_output);
        menu.change_color_options(counter);
    }

    std::cout << WHITE << std::endl;
    system("clear");
}

/* Generate make copy menu */
void make_copy_menu() {
    std::vector<std::string> option_vector = {"1. Select drive letter to backup",
                                            "2. Select directory to copy",
                                            "3. Make copy",
                                            "4. Back"};
    std::vector<void (*)()> function_vector;

    function_vector.push_back(select_drive_letter);
    function_vector.push_back(select_directory);
    function_vector.push_back(make_copy);

    Menu second_menu(option_vector, function_vector);
    display_banner(false);
    create_generic_menu(second_menu, false);
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

    TCHAR tch_volume_name_buff[MAX_PATH + 1];

    ULARGE_INTEGER total_number_of_bytes = {0};
    ULARGE_INTEGER total_number_of_free_bytes = {0};

    if (u_drive_mask == 0)
    {
        std::cout << "GetLogicalDrives() failed with failure code: " << GetLastError() << std::endl;
    }

    else
    {
        std::cout << "This machine has the following logical drives:\n" << std::endl;
        std::cout << "Drive letter\tLabel\t\tTotal space\t\tFree space\t\tDrive type" << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------------" << std::endl;
        while (u_drive_mask)
        {
            if (u_drive_mask & 1)  /* Use the bitwise AND, 1–available, 0-not available */
            {
                std::cout << sz_drive << "\t\t";

                GetVolumeInformation(tch_ptr, tch_volume_name_buff, MAX_PATH + 1, NULL, NULL, NULL, NULL, 0);
                std::cout << tch_volume_name_buff << "\t\t";

                GetDiskFreeSpaceEx(tch_ptr, NULL, &total_number_of_bytes, &total_number_of_free_bytes);
                std::cout << std::fixed << std::setprecision(2) << convert_to_gigabytes(total_number_of_bytes) << " GB   " << "\t\t";
                std::cout << std::fixed << std::setprecision(2) << convert_to_gigabytes(total_number_of_free_bytes) << " GB   " << "\t\t";

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
    std::vector<std::string> option_vector = {"1. List all drives",
                                              "2. Make a copy",
                                              "3. Quit"};
    std::vector<void (*)()> function_vector;

    function_vector.push_back(list_drives);
    function_vector.push_back(make_copy_menu);

    Menu main_menu(option_vector, function_vector);
    display_banner(true);
    create_generic_menu(main_menu, true);
}

#endif