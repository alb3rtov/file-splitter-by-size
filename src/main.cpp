#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include "..\include\colors.h"
#include <unistd.h>
#include <fstream>
#include <thread>

#define KEY_UP 72 //Up arrow character
#define KEY_DOWN 80 //Down arrow character
#define KEY_ENTER '\r' //Enter key character

/* Set color attribute */
void color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/* Set cursor position */
void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

/* Change color option */
void change_color(int size, int Set[], std::vector<int> color_list) {
    for (int i = 0; i < size; i++) {
        Set[i] = color_list.at(i);
    }
}

/* Display banner */
void display_banner() {
    std::string line;
    std::fstream file("banner");
    
    while (getline (file, line)) {
        std::cout << line << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}

/* Main function */
int main() {
    int Set[] = {12,7,7};
    std::vector<int> color_list;
    int counter = 1;
    char key;
    bool running = true;

    system("clear");
    display_banner();

    while (running) {
        gotoxy(10,10);
        color(Set[0]);
        std::cout << "1. List USB drives";

        gotoxy(10,11);
        color(Set[1]);
        std::cout << "2. Make a copy";

        gotoxy(10,12);
        color(Set[2]);
        std::cout << "3. Quit";
        
        key = _getch();

        if (key == KEY_UP && (counter >= 2 && counter <= 3)) { // 72 up arrow key
            counter--;
        }

        if (key == KEY_DOWN && (counter >= 1 && counter <= 2)) { // 80 down arrow key
            counter++;
        }

        if (key == KEY_ENTER) {

            if (counter == 1) {
                std::cout << "\nMenu 1 is open" << std::endl;
            }

            if (counter == 2) {
                std::cout << "\nMenu 2 is open" << std::endl;
            }

            if (counter == 3) {
                std::cout << "\nMenu 3 is open" << std::endl;
                running = false;
            }
        }
        
        if (counter == 1) {
            color_list.push_back(12);
            color_list.push_back(7);
            color_list.push_back(7);
        }
        
        else if (counter == 2) {
            color_list.push_back(7);
            color_list.push_back(12);
            color_list.push_back(7);
        }

        else if (counter == 3) {
            color_list.push_back(7);
            color_list.push_back(7);
            color_list.push_back(12);
        }

        change_color(sizeof(Set)/sizeof(Set[0]), Set, color_list);
        color_list.clear();
    }
    std::cout << "\e[0;37m" << std::endl;
    system("clear");
    return 0;
}