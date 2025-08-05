#include <get_funcs.h>


void get_input(int &cur_i, int &cur_j, int color, int &new_i, int &new_j)
{
    cur_i = 0;
    cur_j = 0;
    new_i = 0;
    new_j = 0;
    string position;
    do // Until the user choice an excisting piece
    {
        cout << "What piece do you want to move? ";
        cin >> position;
    } while (!check_input(position, cur_i, cur_j));
    do // Until the user choice an excisting position
    {
        cout << "To what position? ";
        cin >> position;
    } while (!check_input(position, new_i, new_j));
}

void get_color(int &color, int &opposite_color, int &count)
{
    if (count % 2 != 0)
    {
        color = WHITE_BOARD;
        opposite_color = BLACK_BOARD;
        count++;
    }
    else
    {
        color = BLACK_BOARD;
        opposite_color = WHITE_BOARD;
        count++;
    }
    return;
}

