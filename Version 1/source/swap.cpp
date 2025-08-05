#include <assign_boards.h>
#include <swap.h>
#include <iostream>
using namespace std;


void swap_array(char array[sides][sides][3], int i, int j, int color, int change_i, int change_j)
{
    char temp = array[i][j][color];                               // Save the piece in temp
    array[i][j][color] = array[change_i][change_j][color]; // Replace the piece for other
    array[change_i][change_j][color] = temp;               // Input the store piece in temp
}