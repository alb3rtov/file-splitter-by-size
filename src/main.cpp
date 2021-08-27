#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <thread>

#include "..\src\Menu.cpp"
#include "..\include\colors.h"

/* Display banner */
void display_banner()
{
    std::string line;
    std::fstream file("banner");
    system("clear");

    while (getline(file, line))
    {
        std::cout << line << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

/* Main function */
int main()
{
    int counter = 1;
    bool running = true;
    std::vector<std::string> option_list = {"1. List USB drives",
                                            "2. Make a copy",
                                            "3. Quit"};
    Menu main_menu(option_list);
    display_banner();

    while (running)
    {
        main_menu.display_options();
        main_menu.check_last_input_character(counter, running);
        main_menu.change_color_options(counter);
    }

    std::cout << WHITE << std::endl;
    system("clear");
}