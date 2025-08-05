#include <iostream>
#include <string>
#include <assign_boards.h>
#include <checkers.h>
using namespace std;

char check_pieces(char array[sides][sides][3], int i, int j, int color)
{
    if (color == WHITE_BOARD)
    {
        switch (array[i][j][WHITE_BOARD])
        {
        case 'P':
            return 'P';
        case 'T':
            return 'T';
        case 'H':
            return 'H';
        case 'B':
            return 'B';
        case 'K':
            return 'K';
        case 'Q':
            return 'Q';
        case '*':
            return '*';
        case '0':
            return '0';
        }
    }
    else if (color == BLACK_BOARD)
    {
        switch (array[i][j][BLACK_BOARD])
        {
        case 'P':
            return 'P';
        case 'T':
            return 'T';
        case 'H':
            return 'H';
        case 'B':
            return 'B';
        case 'K':
            return 'K';
        case 'Q':
            return 'Q';
        case '*':
            return '*';
        case '0':
            return '0';
        }
    }
    return 'I';
}

bool check_input(string input, int &i, int &j)
{
    input[0] = toupper(input[0]);
    if (!isprint(input[0]) || !isalpha(input[0]) || input[0] > 'H')
    {
        return false;
    }

    if (!isprint(input[1]) || !isdigit(input[1]) || (input[1] > 8 && input[1] == 0))
    {
        return false;
    }

    i = int(input[1]) - 49;

    switch (input[0])
    {
    case 'A':
        j = 0;
        return true;
    case 'B':
        j = 1;
        return true;
    case 'C':
        j = 2;
        return true;
    case 'D':
        j = 3;
        return true;
    case 'E':
        j = 4;
        return true;
    case 'F':
        j = 5;
        return true;
    case 'G':
        j = 6;
        return true;
    case 'H':
        j = 7;
        return true;
    }
    return 0;
}

bool is_king_alive(char array[sides][sides][3])
{
    int king_count = 0;             // count how many kings are in the game
    for (int i = 0; i < sides; i++) // go through the whole white board
    {
        for (int j = 0; j < sides; j++)
        {
            if (array[i][j][WHITE_BOARD] == 'K') // update king_count if king is found
            {
                king_count++;
            }
        }
    }

    for (int i = 0; i < sides; i++) // go through the whole black board
    {
        for (int j = 0; j < sides; j++)
        {
            if (array[i][j][BLACK_BOARD] == 'K') // update king_count if king is found
            {
                king_count++;
            }
        }
    }
    // if there's 2 king at the board, the king is alive and the game continues
    if (king_count == 2)
    {
        return true;
    }
    return false;
}

bool is_pFirstmove(int i, int color)
{
    //For white pieces the pawn should be in the second row in order to be its first move
    if (color == WHITE_BOARD)
    {
        if (i != 1)
        {
            return false;
        }
    }
    //For black pieces the pawn should be in the seventh row in order to be its first move
    if (color == BLACK_BOARD)
    {
        if (i != 6)
        {
            return false;
        }
    }
    return true;
}

bool p_Valid(char array[sides][sides][3], int cur_i, int cur_j, int color, int new_i, int new_j)
{
    char piece_in_new_place = check_pieces(array, new_i, new_j, color);

    if (color == WHITE_BOARD)
    {
        // Row Movements:

        // Return false if moving backwards or it stays in the same place
        if (new_i - cur_i < 1)
        {
            return false;
        }
        // Return false if the player attempted to move more than one spot and it's not the pawn's first move.
        if ((new_i - cur_i > 1) && !is_pFirstmove(cur_i, color))
        {
            return false;
        }
        // Return false if the player attempted to move more than two spots
        if (new_i - cur_i > 2)
        {
            return false;
        }
        // Return false if moving 2 spaces forward and none of them are empty.
        if ((new_i - cur_i > 1) && (check_pieces(array, cur_i + 1, cur_j, color) != '0' || piece_in_new_place != '0'))
        {
            return false;
        }
        // Return false if moving forward and the space is not empty.
        if (piece_in_new_place != '0' && new_j == cur_j)
        {
            return false;
        }

        //Column movements:

        // Return false if the player is trying to move diagonally even without an opponent's piece in that spot.
        if ((cur_j != new_j) && (piece_in_new_place != '*'))
        {
            return false;
        }
        // If moving diagonally, piece can't move 2 spots forward.
        if ((piece_in_new_place == '*') && (new_i - cur_i != 1) && (cur_j != new_j))
        {
            return false;
        }
    }

    if (color == BLACK_BOARD)
    {
        // Row Movements:

        // Return false if moving backwards or it stays in the same place
        if (cur_i - new_i < 1)
        {
            return false;
        }
        // Return false if the player attempted to move more than one spot and it's not the pawn's first move.
        if ((cur_i - new_i > 1) && !is_pFirstmove(cur_i, color))
        {
            return false;
        }
        // Return false if the player attempted to move more than two spots
        if (cur_i - new_i > 2)
        {
            return false;
        }
        // Return false if moving 2 spaces forward and none of them are empty.
        if ((cur_i - new_i > 1) && (check_pieces(array, cur_i - 1, cur_j, color) != '0' || piece_in_new_place != '0'))
        {
            return false;
        }
        // Return false if moving forward and the space is not empty.
        if (piece_in_new_place != '0' && new_j == cur_j)
        {
            return false;
        }

        //Column movements:

        // Return false if the player is trying to move diagonally even without an opponent's piece in that spot.
        if ((cur_j != new_j) && (piece_in_new_place != '*'))
        {
            return false;
        }
        // If moving diagonally, piece can't move 2 spots forward.
        if ((piece_in_new_place == '*') && (cur_i - new_i != 1) && (cur_j != new_j))
        {
            return false;
        }
    }
    return true;
}

bool t_Valid(char array[sides][sides][3], int cur_i, int cur_j, int color, int new_i, int new_j)
{
    if (cur_i > new_i && cur_j == new_j) // Piece moves up
    {
        int i = cur_i - 1; // checking above current position
        int j = cur_j;     // since moving up j doesn't change
        do
        {
            if (check_pieces(array, i, j, color) != '0')
            {
                if (check_pieces(array, i, j, color) == '*')
                {
                    if (i == new_i)
                    {
                        return true;
                    }
                }
                return false;
            }
            i--;
        } while (i > new_i - 1);
        return true;
    }
    else if (cur_i == new_i && cur_j < new_j) // Pice move right
    {
        int i = cur_i;     // since moving right i doesn't change
        int j = cur_j + 1; // checking the right of current position
        do
        {
            if (check_pieces(array, i, j, color) != '0')
            {
                if (check_pieces(array, i, j, color) == '*')
                {
                    if (j == new_j)
                    {
                        return true;
                    }
                }
                return false;
            }
            j++;
        } while (j < new_j + 1);
        return true;
    }
    else if (cur_i < new_i && cur_j == new_j) // Piece move down
    {
        int i = cur_i + 1; // checking bellow current position
        int j = cur_j;     // since moving down j doesn't change
        do
        {
            if (check_pieces(array, i, j, color) != '0')
            {
                if (check_pieces(array, i, j, color) == '*')
                {
                    if (i == new_i)
                    {
                        return true;
                    }
                }
                return false;
            }
            i++;
        } while (i < new_i + 1);
        return true;
    }
    else if (cur_i == new_i && cur_j > new_j) // Piece move left
    {
        int i = cur_i;     // since moving left i doesn't change
        int j = cur_j - 1; // checking left of current position
        do
        {
            if (check_pieces(array, i, j, color) != '0')
            {
                if (check_pieces(array, i, j, color) == '*')
                {
                    if (j == new_j)
                    {
                        return true;
                    }
                }
                return false;
            }
            j--;
        } while (j > new_j - 1);
        return true;
    }
    else // if the tower is not move in only one direction, return false
    {
        return false;
    }
    return true;
}

bool h_Valid(char array[sides][sides][3], int cur_i, int cur_j, int color, int new_i, int new_j)
{
    int true_count = 0; // increase one if the horse is going on one of the 8 possible moves

    if (cur_i - 2 == new_i && cur_j - 1 == new_j) // two up, one left
    {
        true_count++;
    }
    else if (cur_i - 1 == new_i && cur_j - 2 == new_j) // one up, two left
    {
        true_count++;
    }
    else if (cur_i + 1 == new_i && cur_j - 2 == new_j) // one down, two left
    {
        true_count++;
    }
    else if (cur_i + 2 == new_i && cur_j - 1 == new_j) // two down, one left
    {
        true_count++;
    }
    else if (cur_i + 2 == new_i && cur_j + 1 == new_j) // two down, one right
    {
        true_count++;
    }
    else if (cur_i + 1 == new_i && cur_j + 2 == new_j) // one down, two right
    {
        true_count++;
    }
    else if (cur_i - 1 == new_i && cur_j + 2 == new_j) // one up, two right
    {
        true_count++;
    }
    else if (cur_i - 2 == new_i && cur_j + 1 == new_j) // two up, one right
    {
        true_count++;
    }

    if (true_count > 0) // if the choice is a valid move
    {
        // verify if there's no same color piece in that spot
        if (check_pieces(array, new_i, new_j, color) == '0' || check_pieces(array, new_i, new_j, color) == '*')
        {
            return true;
        }
    }
    return false;
}

bool b_Valid(char array[sides][sides][3], int cur_i, int cur_j, int color, int new_i, int new_j)
{
    if (cur_i > new_i && cur_j < new_j) // Piece moves diagonally up right
    {
        int i = cur_i - 1;
        do
        {
            for (int j = cur_j + 1; j < new_j + 1; j++)
            {
                if (check_pieces(array, i, j, color) != '0')
                {
                    if (check_pieces(array, i, j, color) == '*')
                    {
                        if (i == new_i && j == new_j)
                        {
                            return true;
                        }
                    }
                    return false;
                }
                i--;
            }
        } while (i > new_i - 1);
        return true;
    }
    else if (cur_i < new_i && cur_j < new_j) // Pieces moves diagonally down right
    {
        int i = cur_i + 1;
        do
        {
            for (int j = cur_j + 1; j < new_j + 1; j++)
            {
                if (check_pieces(array, i, j, color) != '0')
                {
                    if (check_pieces(array, i, j, color) == '*')
                    {
                        if (i == new_i && j == new_j)
                        {
                            return true;
                        }
                    }
                    return false;
                }
                i++;
            }
        } while (i < new_i + 1);
        return true;
    }
    else if (cur_i > new_i && cur_j > new_j) // Pieces moves diagonally up left
    {
        int i = cur_i - 1;
        do
        {
            for (int j = cur_j - 1; j > new_j - 1; j--)
            {
                if (check_pieces(array, i, j, color) != '0')
                {
                    if (check_pieces(array, i, j, color) == '*')
                    {
                        if (i == new_i && j == new_j)
                        {
                            return true;
                        }
                    }
                    return false;
                }
                i--;
            }
        } while (i > new_i - 1);
        return true;
    }
    else if (cur_i < new_i && cur_j > new_j) // Pieces moves diagonally down left
    {
        int i = cur_i + 1;
        do
        {
            for (int j = cur_j - 1; j > new_j - 1; j--)
            {
                if (check_pieces(array, i, j, color) != '0')
                {
                    if (check_pieces(array, i, j, color) == '*')
                    {
                        if (i == new_i && j == new_j)
                        {
                            return true;
                        }
                    }
                    return false;
                }
                i++;
            }
        } while (i < new_i + 1);
        return true;
    }
    return false;
}
bool k_Valid(char array[sides][sides][3], int cur_i, int cur_j, int color, int new_i, int new_j)
{
    int true_count = 0; // Increase if the user attemp to move the King

    if (cur_i - 1 == new_i && cur_j - 1 == new_j) // Pice move one diagonally up left
    {
        true_count++;
    }
    else if (cur_i - 1 == new_i && cur_j == new_j) // Piece move on up
    {
        true_count++;
    }
    else if (cur_i - 1 == new_i && cur_j + 1 == new_j) // Piece move on diagonally up right
    {
        true_count++;
    }
    else if (cur_i == new_i && cur_j + 1 == new_j) // Piece move one right
    {
        true_count++;
    }
    else if (cur_i + 1 == new_i && cur_j + 1 == new_j) // Piece move one diagonally down right
    {
        true_count++;
    }
    else if (cur_i + 1 == new_i && cur_j == new_j) // Piece move one down
    {
        true_count++;
    }
    else if (cur_i + 1 == new_i && cur_j - 1 == new_j) // Piece move one diagonally down left
    {
        true_count++;
    }
    else if (cur_i == new_i && cur_j - 1 == new_j) // Piece move one one left
    {
        true_count++;
    }

    if (true_count > 0) // if the choice is a valid move
    {
        // verify if there's no same color piece in that spot
        if (check_pieces(array, new_i, new_j, color) == '0' || check_pieces(array, new_i, new_j, color) == '*')
        {
            return true;
        }
    }
    return false;
}

bool q_Valid(char array[sides][sides][3], int cur_i, int cur_j, int color, int new_i, int new_j)
{
    //Using the function for the tower for checking the vertical and horizontal moves of the queen
    if (t_Valid(array, cur_i, cur_j, color, new_i, new_j))
    {
        return true;
    }
    //Using the function for the bishop for checking diagonal moves of the queen
    else if (b_Valid(array, cur_i, cur_j, color, new_i, new_j))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool is_move_valid(char array[sides][sides][3], int cur_i, int cur_j, int color, int new_i, int new_j)
{
    switch (check_pieces(array, cur_i, cur_j, color))
    {
    case 'P':
        return p_Valid(array, cur_i, cur_j, color, new_i, new_j);
    case 'T':
        return t_Valid(array, cur_i, cur_j, color, new_i, new_j);
    case 'H':
        return h_Valid(array, cur_i, cur_j, color, new_i, new_j);
    case 'B':
        return b_Valid(array, cur_i, cur_j, color, new_i, new_j);
    case 'K':
        return k_Valid(array, cur_i, cur_j, color, new_i, new_j);
    case 'Q':
        return q_Valid(array, cur_i, cur_j, color, new_i, new_j);
    }
    return false;
}
