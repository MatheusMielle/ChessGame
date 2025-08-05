#ifndef SWAP_H
#define SWAP_H

#include <assign_boards.h>

// Swap the pieces in the board array
/* Input: array (the board array), i(the x location of one piece), j(the y location of 
one piece), color of the pieces in the board array change_i (the x location of the other 
piece) change_j (the y location of the other piece*/
void swap_array(char array[sides][sides][3], int i, int j, int color, int change_i, int change_j);

#endif