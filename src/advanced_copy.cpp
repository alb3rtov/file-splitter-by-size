#ifndef _ADVANCED_COPY_
#define _ADVANCED_COPY__

#include <iostream>
#include "copy_functions.cpp"

/* Create menu for sequential copy */
void create_menu_sequential_copy() {

    std::vector<std::string> option_vector = {"1. Select directory to copy",
                                              "2. Start copy",
                                              "3. Back"};
    std::vector<void (*)()> function_vector;

    function_vector.push_back(select_directory);
    function_vector.push_back(make_copy);

    Menu sequential_copy_menu(option_vector, function_vector);
    display_banner(false);
    create_generic_menu(sequential_copy_menu, false, false);
    display_banner(false);
}

/* Set drive letters of external drives */
void configure_sequential_copy() {

    std::string num_drives;

    do {
        std::cout << "\n\nHow many drives will you use?: ";
        std::getline(std::cin, num_drives);

    } while(!is_digit(num_drives));

    /*
    std::stringstream ss;
    int num;
    ss << num_drives;
    ss >> num;
    */
    int num = convert_string_int(num_drives);

    std::cout << "\nConnect all the external drives and press enter...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    list_drives();

    std::cout << "\n\nChoose the drives letters\n";

    int cnt = 1;

    while (num > 0) {
        std::string next_drive;
        
        std::cout << "\nDrive letter number " << cnt << ": ";
        std::getline(std::cin, next_drive);

        if (drive_letter_found(next_drive)) {
            num--;
            cnt++;
            drives_letters.push_back(next_drive);
        } else {
            std::cout << "\nDrive letter " << next_drive << " doesn't exists";
        }
    }

    type_copy = SEQUENTIAL;
    create_menu_sequential_copy();       
}

/*  */
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