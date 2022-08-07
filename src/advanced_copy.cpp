#ifndef _ADVANCED_COPY_
#define _ADVANCED_COPY__

#include <iostream>
#include "copy_functions.cpp"

/* Menu for sequential copy */
void configure_sequential_copy() {

    std::string num_drives;
    std::cout << "\n\nHow many drives will you use?: ";
    std::getline(std::cin, num_drives);

    std::cout << "\n\nConnect all the external drives and press enter...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    list_drives();

    std::cout << "\n\nChoose the drives letters";
    
    std::stringstream ss;
    int num;
    ss << num_drives;
    ss >> num;

    std::vector<std::string> list_selected_drives;

    for (int i = 0; i < num; i++) {
        std::string next_drive;
        std::cout << "\n\nDrive letter number " << i+1 << ": ";
        std::getline(std::cin, next_drive);
        list_selected_drives.push_back(next_drive);
    }
    
    /* 
    std::vector<std::string> option_vector = {"1. List all drives",
                                              "2. Select directory to copy",
                                              "3. Quit"};
    std::vector<void (*)()> function_vector;*/
    
       
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