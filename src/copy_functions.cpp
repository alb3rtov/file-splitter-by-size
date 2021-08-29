#ifndef _COPY_FUNCTIONS_
#define _COPY_FUNCTIONS_

#include <iostream>
#include <string>

#include "..\include\definitions.hpp"

std::string drive_letter;
std::string directory_path;
std::string maximum_space;

void select_drive_letter()
{
    std::cout << "\nSelect drive letter: ";
    std::cin >> drive_letter;
    clear_display_banner_and_menu();
}

void select_directory()
{
    std::cout << "Select directory: ";
    std::cin >> directory_path;
    clear_display_banner_and_menu();
}

void select_maximum_space()
{
    std::cout << "Select maximum space: ";
    std::cin >> maximum_space;
    clear_display_banner_and_menu();
}

#endif