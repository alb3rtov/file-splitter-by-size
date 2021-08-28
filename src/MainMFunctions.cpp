#ifndef _MAIN_M_FUNCTIONS_
#define _MAIN_M_FUNCTIONS_

#include <vector>
#include <string>
#include "..\src\main.cpp"
#include "..\src\CopyMFunctions.cpp"
#include "..\include\definitions.hpp"

void funcion1() {
    std::vector<std::string> option_vector = {"1. Cozas1",
                                            "2. Cozas12",
                                            "3. Cozas123"};
    std::vector<void (*)()> function_vector;

    function_vector.push_back(function12);
    function_vector.push_back(function13);

    Menu second_menu(option_vector, function_vector);
    display_banner(false);
    create_generic_menu(second_menu);
    display_banner(false);
}

void funcion2() {
    std::cout << "Function 2" << std::endl;
}

#endif