#include <vector>
#include <string>

class Menu
{
private:
    std::vector<std::string> _option_list;
    int *_Set;

public:
    Menu(std::vector<std::string> option_list);

    std::vector<std::string> get_option_list();
    int *get_set();

    void display_options();
    void color(int color);
    void gotoxy(int x, int y);
    void check_last_input_character(int &counter, bool &running);
    void change_color_options(int counter);
    void change_color(std::vector<int> color_list);
};