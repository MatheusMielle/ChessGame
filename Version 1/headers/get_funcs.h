#ifndef GET_H
#define GET_H
#include <iostream>
#include <string.h>
#include <assign_boards.h>
#include <checkers.h>
using namespace std;

// Grab the user input
/*Input: cur_i(for row of piece in the inital position, provided by the user), 
cur_j (for column of piece in the inital position, provided by the user ), 
new_i(for row of the place the user want to move the piece), new_j(for column 
of the place the user want to move the piece), and the color of the piece.*/
void get_input(int &cur_i, int &cur_j, int color, int &new_i, int &new_j);

// Change the color of the board based on the round 
/* Input: color of curent player, the opposite color (if it's white the 
opposite color is black) and count(the round counter)*/ 
void get_color(int &color, int &opposite_color, int &count);


#endif