#ifndef _MAIN_
#define _MAIN_

#include <iostream>
#include <vector>
#include <string>
#include <tchar.h>
#include <iomanip>

#include "Menu.cpp"
#include "copy_functions.cpp"
#include "advanced_copy.cpp"
#include "..\include\colors.hpp"
#include "..\include\definitions.hpp"

bool first_menu = true;

/* Generate make copy menu */
void make_simple_copy_menu() {
    std::vector<std::string> option_vector = {"1. Select backup options",
                                            "2. Select directory to copy",
                                            "3. Start copy",
                                            "4. Back"};
    std::vector<void (*)()> function_vector;

    function_vector.push_back(select_backup_options);
    function_vector.push_back(select_directory);
    function_vector.push_back(make_copy);

    type_copy = 0;

    Menu second_menu(option_vector, function_vector);
    display_banner(false);
    create_generic_menu(second_menu, false, false);
    display_banner(false);
}

/* Main function */
int main()
{
    std::vector<std::string> option_vector = {"1. List all drives",
                                              "2. Make simple copy",
                                              "3. Advanced copy settings",
                                              "4. Quit"};
    std::vector<void (*)()> function_vector;

    function_vector.push_back(list_drives);
    function_vector.push_back(make_simple_copy_menu);
    function_vector.push_back(advanced_copy_settings);

    Menu main_menu(option_vector, function_vector);
    display_banner(true);
    create_generic_menu(main_menu, true, true);
}

#endif