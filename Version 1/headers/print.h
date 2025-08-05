#ifndef PRINT_H
#define PRINT_H
#include <iostream>
#include <string.h>
#include <assign_boards.h>
#include <checkers.h>
using namespace std;

void print_header();

void print_player(int color);

// Utility to show the board to the user.
// Input: board array.
void print_board(char piece[sides][sides][3]);

void print_warning(int &count, int color);

void print_winner(int color);




#endif