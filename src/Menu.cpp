#ifndef _MENU_
#define _MENU_

#include <iostream>
#include <windows.h>
#include <conio.h>

#include "..\include\Menu.hpp"
#include "..\include\definitions.hpp"

Menu::Menu(std::vector<std::string> option_list, std::vector<void (*)()> function_vector)
{
    this->_option_vector = option_list;
    this->_function_vector = function_vector;
    this->_Set = get_set();
}

std::vector<std::string> Menu::get_option_vector()
{
    return this->_option_vector;
}

int *Menu::get_set()
{
    int size = this->_option_vector.size();
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
    for (int i = 0; i < this->_option_vector.size(); i++)
    {
        gotoxy(10, 10 + i);
        color(this->_Set[i]);
        std::cout << this->_option_vector.at(i);
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

/* Check last input character from user's keyboard */
void Menu::check_last_input_character(int &counter, bool &running, bool move_output)
{
    char key = _getch();

    if (key == KEY_UP && (counter >= 2 && counter <= this->_option_vector.size()))
    {
        counter--;
    }

    else if (key == KEY_DOWN && (counter >= 1 && counter <= this->_option_vector.size()-1))
    {
        counter++;
    }

    else if (key == KEY_ENTER)
    {   
        for (int i = 0; i < this->_option_vector.size(); i++) {
            if (counter == this->_option_vector.size()) {
                running = false; /* Exit */
            }
            else if (counter == i+1) {
                clear_display_banner_and_menu();
                if (move_output) {
                    gotoxy(0,12 + this->_option_vector.size());  
                }
                             
                this->_function_vector.at(i)();
            }
        }
    }
}

/* Change the color of the menu options depending on the selected one */
void Menu::change_color_options(int counter)
{
    std::vector<int> color_vector;

    for (int i = 0; i < this->_option_vector.size(); i++) 
    {
        if (counter == i+1) {
            color_vector.push_back(12);
        } else {
            color_vector.push_back(7);
        }
    }

    change_color(color_vector);
}

/* Change color option */
void Menu::change_color(std::vector<int> color_vector)
{
    for (int i = 0; i < this->_option_vector.size(); i++)
    {
        this->_Set[i] = color_vector.at(i);
    }
}

#endif