#ifndef _COPY_FUNCTIONS_
#define _COPY_FUNCTIONS_

#include <iostream>
#include <string>

#include "..\include\definitions.hpp"

std::string drive_letter;
std::string directory_path;
std::string maximum_space;

void check_current_attrs_values()
{
    std::cout << "\n\n\n\n\n\n" << std::endl;

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
        std::cout << BHIYELLOW << "\nCurrent selected maximum space: " << maximum_space;
    }
}

void select_drive_letter()
{
    std::cout << "\nSelect drive letter: ";
    std::cin >> drive_letter;
    clear_display_banner_and_menu();
    check_current_attrs_values();
}

void select_directory()
{
    std::cout << "Select directory: ";
    std::cin >> directory_path;
    clear_display_banner_and_menu();
    check_current_attrs_values();
}

void select_maximum_space()
{
    std::cout << "Select maximum space: ";
    std::cin >> maximum_space;
    clear_display_banner_and_menu();
    check_current_attrs_values();
}

#endif