///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Final Project for CS-171-3 - Whitworth University
//
// Developed by Matheus Mielle Silva and Fabian Gomez
// Developed on: December 16th, 2021
//
// License: Only project developers are allowed to edit or share
// this file electronically unless such permission is given by the developers.
//
// Copyright (C) Matheus M Silva 2021
// Copyright (C) Fabian Gomez 2021
//
// Credits and Sources:
// - Andrew East CS2 (Whitworth University): Help use with some brain storm ideas.
// - https://www.wholesalechess.com/pages/new-to-chess/pieces.html (Use for checkers.cpp)
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cctype>
#include <checkers.h>
#include <assign_boards.h>
#include <swap.h>
#include <print.h>
#include <get_funcs.h>

using namespace std;

int main()
{
    char pieces[sides][sides][3];
    int cur_i, cur_j, new_i, new_j;
    assign_pieces(pieces);
    int round_count = 1;
    int color;
    int opposite_color;
    get_color(color, opposite_color, round_count);
    int warning_count = 0;

    print_header();    

    do
    {
        print_player(color);
        print_board(pieces);    
        get_input(cur_i, cur_j, color, new_i, new_j);

        if (is_move_valid(pieces, cur_i, cur_j, color, new_i, new_j))
        {
            warning_count = 0;
            if (check_pieces(pieces, new_i, new_j, color) == '*')
            {
                pieces[new_i][new_j][opposite_color] = '0';
                pieces[new_i][new_j][color] = '0';
            }
            swap_array(pieces, cur_i, cur_j, color, new_i, new_j);
            swap_array(pieces, cur_i, cur_j, opposite_color, new_i, new_j);          
            get_color(color, opposite_color, round_count);
        }
        else
        {            
            print_warning(warning_count, color);
            
        }
    } while (is_king_alive(pieces) && warning_count < 5);
    if (!is_king_alive(pieces))
    {
        cout << endl;
        print_board(pieces);
        print_winner(color);
    }
}



