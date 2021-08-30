#ifndef _COPY_FUNCTIONS_
#define _COPY_FUNCTIONS_

#include <iostream>
#include <string>
#include <regex>
#include <sys/stat.h>
#include <filesystem>

#include "..\include\definitions.hpp"

std::string drive_letter;
std::string directory_path;
std::string maximum_space;

/* Check all attributes values to print if contain smth */
void check_current_attrs_values()
{
    std::cout << "\n\n\n\n\n\n\n"
              << std::endl;

    if (!drive_letter.empty())
    {
        std::cout << BHIYELLOW << "\nCurrent selected drive letter: " << drive_letter;
    }

    if (!directory_path.empty())
    {
        std::cout << BHIYELLOW << "\nCurrent selected directory path: " << directory_path;
    }

    if (!maximum_space.empty())
    {
        std::cout << BHIYELLOW << "\nCurrent selected maximum space: " << maximum_space << " GB";
    }
}

/* Returns bool that indicates if a given path exists */
bool is_path_exist(const std::string &s)
{
    struct stat buffer;
    return (stat(s.c_str(), &buffer) == 0);
}

/* Request drive letter to user */
void select_drive_letter()
{
    do
    {
        std::cout << "\nSelect drive letter (e.g.: E): ";
        std::cin >> drive_letter;
    } while (!std::regex_match(drive_letter, std::regex("[A-Za-z]")) && (drive_letter.size() != 1));
    drive_letter.append(":\\");

    clear_display_banner_and_menu();
    check_current_attrs_values();
}

/* Request directory where make the backup to user */
void select_directory()
{
    do
    {
        std::cout << "Select directory: ";
        std::cin >> directory_path;
    } while (!is_path_exist(directory_path));

    clear_display_banner_and_menu();
    check_current_attrs_values();
}

/* Request maximum space for the backup to user */
void select_maximum_space()
{
    do
    {
        std::cout << "Select maximum space (no decimals): ";
        std::cin >> maximum_space;
    } while (!std::regex_match(maximum_space, std::regex("[[:digit:]]+")));

    clear_display_banner_and_menu();
    check_current_attrs_values();
}

/* List all files in directory and sub-directories */
long long int list_all_files(std::string directory_path, std::vector<std::string> &files)
{
    long long int total_size = 0;
    std::string path;

    for (const auto &entry : std::filesystem::directory_iterator(directory_path))
    {
        path = entry.path().string();

        if (std::filesystem::is_directory(path))
        {
            total_size = total_size + list_all_files(path, files);
        }
        else
        {
            files.push_back(path);
            //std::cout << path << "  " << std::filesystem::file_size(path) << std::endl;
            total_size = total_size + std::filesystem::file_size(path);
        }
    }

    return total_size;
}

/* Main function to make copy */
void make_copy()
{   
    std::vector<std::string> files;
    long long int size = 0;

    std::cout << "\n\n\n\n\n\n\n" << std::endl;

    if (!drive_letter.empty() && !directory_path.empty() && !maximum_space.empty())
    {
        size = list_all_files(directory_path, files);
        std::cout << "Total size: " << size << " bytes" << std::endl;
        /*
        if (!CopyFileA(prueba.c_str(), "F:\\Bomb-Defusal-Manual.pdf", 0))
        {
            std::cout << "Error: " << GetLastError() << std::endl;
        }
        else
        {
            std::cout << "Okay " << std::endl;
        }*/
    }
    else
    {
        std::cout << BHIRED << "\nYou need to select a drive letter, a directory and a maximum space." << std::endl;
    }
}

#endif