#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <string>

#include "..\include\Menu.hpp"
#include "..\include\definitions.hpp"

Menu::Menu(std::vector<std::string> option_list)
{
    this->_option_list = option_list;
    this->_Set = get_set();
}

std::vector<std::string> Menu::get_option_list()
{
    return this->_option_list;
}

int *Menu::get_set()
{
    int size = this->_option_list.size();
    int *Set = new int[size];

    for (int i = 0; i < size; i++)
    {
        Set[i] = (i == 0) ? 12 : 7;
    }

    return Set;
}

/* Show the options of the menu */
void Menu::display_options()
{
    for (int i = 0; i < this->_option_list.size(); i++)
    {
        gotoxy(10, 10 + i);
        color(this->_Set[i]);
        std::cout << this->_option_list.at(i);
    }
}

/* Set color attribute */
void Menu::color(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/* Set cursor position */
void Menu::gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


void Menu::check_last_input_character(int &counter, bool &running)
{
    char key = _getch();

    if (key == KEY_UP && (counter >= 2 && counter <= 3))
    {
        counter--;
    }

    else if (key == KEY_DOWN && (counter >= 1 && counter <= 2))
    {
        counter++;
    }

    else if (key == KEY_ENTER)
    {
        switch (counter)
        {
        case 1:
            std::cout << "\nMenu 1 is open" << std::endl;
            break;
        case 2:
            std::cout << "\nMenu 2 is open" << std::endl;
            break;
        case 3:
            running = false;
            break;
        }
    }
}

/* Change the color of the menu options depending on the selected one */
void Menu::change_color_options(int counter)
{
    std::vector<int> color_list;

    for (int i = 0; i < this->_option_list.size(); i++) 
    {
        if (counter == i+1) {
            color_list.push_back(12);
        } else {
            color_list.push_back(7);
        }
    }

    change_color(color_list);
}

/* Change color option */
void Menu::change_color(std::vector<int> color_list)
{
    for (int i = 0; i < this->_option_list.size(); i++)
    {
        this->_Set[i] = color_list.at(i);
    }
}
