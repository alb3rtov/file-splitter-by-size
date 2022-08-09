#ifndef _DEFINITIONS_
#define _DEFINITIONS_

#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <sys/stat.h>
#include <regex>

#include "..\src\Menu.cpp"
#include "..\include\colors.hpp"

#define KEY_UP 72           /* Up arrow character */
#define KEY_DOWN 80         /* Down arrow character */
#define KEY_ENTER '\r'      /* Enter key character */
#define SEQUENTIAL 1
#define PARARELL 2

std::vector<std::string> drive_list;
std::vector<std::string> drives_letters;
std::string drive_letter;
std::string copy_full_path;
std::string directory_path;
int type_copy;
int drive_type;

/* Convert string to int */
int convert_string_int(std::string str) {
    int num;
    std::stringstream ss;
    ss << str;
    ss >> num;

    return num;
}

/* Check if string is a number */
bool is_digit(std::string x){
    bool num;
    std::regex e ("^-?\\d+");

    if (std::regex_match (x,e)) {
        num = true;
    } else {
        num = false;
    }
    
    return num;
}

/*  Returns a double of conversion of bytes to MB */
double convert_to_megabytes(ULARGE_INTEGER total_bytes) {
    double kb = 0;
    double mb = 0;
    
    kb = total_bytes.QuadPart/1024;
    mb = kb/1024;

    return mb;
}

/* Returns a double of conversion of bytes to GB */
double convert_to_gigabytes(ULARGE_INTEGER total_bytes) {

	double mb = convert_to_megabytes(total_bytes);
	double gb = 0;

    gb = mb/1024;

    return gb;
}

/* Convert mb to long int */
double convert_to_mb_from_long_int(long long int size)
{
    double kb_size = size / 1024;
    double mb_size = kb_size / 1024;

    return mb_size;
}

/* Convert long long int bytes to double gigabytes */
double convert_to_gb_from_long_int(long long int size)
{
    double gb_size = convert_to_mb_from_long_int(size) / 1024;
    return gb_size;
}

/* Convert elapsed time to minutes if is necessary */
void get_elapsed_time(double elapsed_time)
{
    if (elapsed_time > 60)
    {
        int minutes = elapsed_time / 60;
        double d_minutes = elapsed_time / 60;
        int seconds = (d_minutes - minutes) * 60;
        std::cout << "Elapsed time: " << minutes << " minutes " << seconds << " seconds. ";
    }
    else
    {
        std::cout << "Elapsed time: " << elapsed_time << " seconds. ";
    }
}

/* Returns bool that indicates if a given path exists */
bool is_path_exist(const std::string &s)
{
    struct stat buffer;
    return (stat(s.c_str(), &buffer) == 0);
}

/* Creates a directory of a given name/path */
void create_directory(std::string directory) {
    if (!CreateDirectoryA(directory.c_str(), 0))
    {
        if (GetLastError() != ERROR_ALREADY_EXISTS)
        {
            std::cout << "Error: " << GetLastError() << std::endl;
        }
    }
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
    system("cls");
    display_banner(false);
}

/* Get type of drive */
void DisplayDriveType(int iParam)
{
    switch (iParam)
    {
    case DRIVE_UNKNOWN:
        std::cout << "Drive type unknown" << std::endl;
        drive_type = DRIVE_UNKNOWN;
        break;

    case DRIVE_NO_ROOT_DIR:
        std::cout << "No drive for that root path" << std::endl;
        drive_type = DRIVE_NO_ROOT_DIR;
        break;

    case DRIVE_REMOVABLE:
        std::cout << "Removable drive" << std::endl;
        drive_type = DRIVE_REMOVABLE;
        break;

    case DRIVE_FIXED:
        std::cout << "Fixed drive" << std::endl;
        drive_type = DRIVE_FIXED;
        break;

    case DRIVE_REMOTE:
        std::cout << "Network drive" << std::endl;
        drive_type = DRIVE_REMOTE;
        break;

    case DRIVE_CDROM:
        std::cout << "CD ROM drive" << std::endl;
        drive_type = DRIVE_CDROM;
        break;
    }
}

/* Check all attributes values to print if contain smth */
void check_current_attrs_values()
{
    std::cout << "\n\n\n\n\n\n\n"
              << std::endl;
    
    if (type_copy == SEQUENTIAL || type_copy == PARARELL) {
        for (int i = 0; i < drives_letters.size(); i++) {
            std::string fix_drive_letter = drives_letters[i].substr(0, drives_letters[i].size()-2);
            std::cout << BHIYELLOW << "\nSelected drive letter (" << i+1 << "): " << fix_drive_letter;
        }
    } else {
        if (!drive_letter.empty()) {  
            std::string fix_drive_letter = drive_letter.substr(0, drive_letter.size()-2);
            std::cout << BHIYELLOW << "\nCurrent selected drive letter: " << fix_drive_letter;
        }

        if (!copy_full_path.empty()) {
            std::cout << BHIYELLOW << "\nCurrent selected directory where make the copy: " << copy_full_path;
        }
    }

    if (!directory_path.empty()) {
        std::cout << BHIYELLOW << "\nCurrent selected directory path to copy: " << directory_path;
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
        std::cout << "\nThis machine has the following logical drives:\n" << std::endl;
        std::cout << "Drive letter\tLabel\t\tTotal space\t\tFree space\t\tDrive type" << std::endl;
        std::cout << "-----------------------------------------------------------------------------------------------" << std::endl;
        while (u_drive_mask)
        {
            if (u_drive_mask & 1)  /* Use the bitwise AND, 1–available, 0-not available */
            {
                std::cout << sz_drive << "\t\t";
                std::string drive_letter_str;
                std::stringstream ss;
                ss << sz_drive;
                ss >> drive_letter_str;
                drive_list.push_back(drive_letter_str);

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

/* Generate menu based on a Menu object */
void create_generic_menu(Menu menu, bool move_output, bool first_menu) 
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
            if (first_menu) { /* Print drives first time */
                //first_menu = false;
                list_drives();
            }
        }
        menu.display_options();
        menu.check_last_input_character(counter, running, move_output);
        menu.change_color_options(counter);
    }

    std::cout << WHITE << std::endl;
    system("clear");
}

#endif