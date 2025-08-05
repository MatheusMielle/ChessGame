#ifndef CHECKERS_H
#define CHECKERS_H
#include <iostream>
#include <string.h>
#include <assign_boards.h>
#include <checkers.h>
using namespace std;

//Verify which piece was chosen by the user.
/*Input: The board array, i(for row, inputted by the user), 
j (for column inputted by the user) and the color of the piece.*/
/*Output the char of the piece (p for pawn, k for king ...), 0 for 
blank space and * for opponent's piece*/  
char check_pieces (char array[sides][sides][3], int i, int j, int color);

// Verify if the piece the user chose is in the board
/* Converts the user input in the format string (letter and number(A1)) to the 
format int i (0-7) and int j (0-7) so that it can be used in the array. */
/* Output: false for out of the array bounders input or if the input is not in the 
rules format and true for inputaccording to the rules and limits of the board array*/
bool check_input(string input, int &i, int &j);

// Check if the both king are currently in the game
// Input: the board array
// output: true for both king in the game and false for less than 2 kings 
bool is_king_alive(char array[sides][sides][3]);

// Verify if it's the first time that that pawn is moving
// Input: i(give the row of the pawn) and the color of the pawn
// Output: true for first move and false for not the first move.
bool is_pFirstmove(int i, int color);

/*Each function bellow will verify if the one specific piece can move 
in the direction requested.*/
/*Input: The board array, cur_i(for row of piece in the inital position), 
cur_j (for column of piece in the inital position), new_i(for row of the place the 
user want to move the piece), new_j(for column of the place the user want to move 
the piece), and the color of the piece.*/
//Output: true for valid move and false for invalid move.
bool p_Valid(char array[sides][sides][3], int cur_i, int cur_j, int color, int new_i, int new_j);
bool t_Valid(char array[sides][sides][3], int cur_i, int cur_j, int color, int new_i, int new_j);
bool h_Valid(char array[sides][sides][3], int cur_i, int cur_j, int color, int new_i, int new_j);
bool b_Valid(char array[sides][sides][3], int cur_i, int cur_j, int color, int new_i, int new_j);
bool k_Valid(char array[sides][sides][3], int cur_i, int cur_j, int color, int new_i, int new_j);
bool q_Valid(char array[sides][sides][3], int cur_i, int cur_j, int color, int new_i, int new_j);

// Call valid functions depending on the piece chosen by the user
/*Input: The board array, cur_i(for row of piece in the inital position), 
cur_j (for column of piece in the inital position), new_i(for row of the place the 
user want to move the piece), new_j(for column of the place the user want to move 
the piece), and the color of the piece.*/
//Output: true for valid move and false for invalid move.
bool is_move_valid(char array[sides][sides][3], int cur_i, int cur_j, int color, int new_i, int new_j);


#endif

