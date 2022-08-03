#ifndef _DEFINITIONS_
#define _DEFINITIONS_

#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <sys/stat.h>

#include "..\src\Menu.cpp"
#include "..\include\colors.hpp"

#define KEY_UP 72           /* Up arrow character */
#define KEY_DOWN 80         /* Down arrow character */
#define KEY_ENTER '\r'      /* Enter key character */

std::vector<std::string> drive_list;
int drive_type;

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

#endif