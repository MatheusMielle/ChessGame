#ifndef ASSIGN_H
#define ASSIGN_H

#define WHITE_BOARD 0 // Board index 0 is white
#define BLACK_BOARD 1 // Board index 1 is black
#define BLANK_BOARD 2 // Board index 2 is blank
#define sides 8       // The size of the board array

/* Crates 3 boards: 
    -White(index 0): contains pieces in the first 2 rows, 0 representing blank spaces,
        in the next 4 rows and * representing the opponent's pieces in the last 2 rows
    - Black(index 1): contains * representing the opponent's pieces in the first 2 rows, 
        0 representing blank spaces in the next 4 rows and pieces in the last 2 rows
    -Blank (index 2): The full board is composite by ' ' */
// Input: the board array.    
void assign_pieces(char piece[sides][sides][3]);

#endif