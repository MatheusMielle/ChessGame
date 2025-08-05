#include <assign_boards.h>
#include <iostream>
#include <string.h>
using namespace std;

void assign_pieces(char piece[sides][sides][3])
{
    string pieces = "THBKQBHT"; // The name of the white and black pieces

    // Set up Whiteboard
    // Set up Blackboard
    // Set up blank

    for (int i = 0; i < sides; i++) // Loop as big as the array
    {
        for (int j = 0; j < sides; j++)
        {
            switch (i)
            {
            case 0:
                piece[i][j][WHITE_BOARD] = pieces[j];
                piece[i][j][BLACK_BOARD] = '*';
                break;
            case 1:
                piece[i][j][WHITE_BOARD] = 'P';
                piece[i][j][BLACK_BOARD] = '*';
                break;
            case 2:
                piece[i][j][WHITE_BOARD] = '0';
                piece[i][j][BLACK_BOARD] = '0';
                break;
            case 3:
                piece[i][j][WHITE_BOARD] = '0';
                piece[i][j][BLACK_BOARD] = '0';
                break;
            case 4:
                piece[i][j][WHITE_BOARD] = '0';
                piece[i][j][BLACK_BOARD] = '0';
                break;
            case 5:
                piece[i][j][WHITE_BOARD] = '0';
                piece[i][j][BLACK_BOARD] = '0';
                break;
            case 6:
                piece[i][j][WHITE_BOARD] = '*';
                piece[i][j][BLACK_BOARD] = 'P';
                break;
            case 7:
                piece[i][j][WHITE_BOARD] = '*';
                piece[i][j][BLACK_BOARD] = pieces[j];
                break;
            }
            piece[i][j][BLANK_BOARD] = ' ';
        }
    }
}