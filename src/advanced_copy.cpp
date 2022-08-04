#ifndef _ADVANCED_COPY_
#define _ADVANCED_COPY__

#include <iostream>
#include "copy_functions.cpp"

/**/
void configure_sequential_copy() {
    
}


/**/
void configure_pararell_copy() {

}

/* Create a menu with advanced copy settings options */
void advanced_copy_settings() {
    std::vector<std::string> option_vector = {"1. Configure sequential copy with multiple external drives",
                                            "2. Configure pararell copy with multiple external drives", 
                                            "3. Back"};

    std::vector<void (*)()> function_vector;

    function_vector.push_back(configure_sequential_copy);
    function_vector.push_back(configure_pararell_copy);

    Menu advanced_menu(option_vector, function_vector);
    display_banner(false);
    create_generic_menu(advanced_menu, false, false);
    display_banner(false);
}

#endif