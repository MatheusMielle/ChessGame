#include <print.h>

void print_header()
{
    cout << "\n          WELCOME TO A GAME OF CHESS!\n"
         << "\nHow to Play?\n"
         << "There's two players playing this game:\n"
         << "- Player 1: Controls the white pieces.\n"
         << "- Player 2: Controls the black pieces.\n"
         << "-The rules of the game can be found at https://www.ichess.net/blog/chess-pieces-moves/\n"
         << "-I truly recommend to read them before playing\n"
         << "-When it's your turn to play you should type the letter of the column the piece/spot is "
         << "followed by the number of the row.\n"
         << "-Only the first two typed characters will be recognized\n"
         << "-If you type a combination of letter and number that is not in the board or"
         << "if you type in the wrong order, the program will ask for input again.\n"
         << "-If what you type is in the right format but you selected the wrong piece"
         << "or make a forbidden move, a warning will pop up\n"
         << "-You can receive up to 5 warnings before the game ends and declare the other player as the winner.\n"
         << "\n                    Good Luck! Have Fun!\n";
}

void print_player(int color)
{
    if (color == WHITE_BOARD)
    {
        cout << "\nPlayer 1, It's your turn.\n\n";
    }
    else if (color == BLACK_BOARD)
    {
        cout << "\nPlayer 2, It's your turn.\n\n";
    }
}

void print_board(char piece[sides][sides][3])
{
    /*for (int k = 0; k < 3; k++)
    {
        for (int i = 0; i < sides; i++) // Loop as big as the array
        {
            for (int j = 0; j < sides; j++)
            {
                cout << "| " << piece[i][j][k] << " ";
            }
            cout << "|\n";
        }
        cout << "\n\n";
    }*/

    cout << "   | -A | -B | -C | -D | -E | -F | -G | -H |\n";
    cout << "___|____|____|____|____|____|____|____|____|\n";
    for (int i = 0; i < sides; i++) //Loop the numbers of time of the array
    {
        cout << i + 1 << "  ";
        for (int j = 0; j < sides; j++)
        {
            if (check_pieces(piece, i, j, WHITE_BOARD) == '0')
            {
                cout << "|  " << piece[i][j][BLANK_BOARD] << " ";
            }
            else if (check_pieces(piece, i, j, WHITE_BOARD) == '*')
            {
                cout << "| B" << piece[i][j][BLACK_BOARD] << " ";
            }
            else
            {
                cout << "| W" << piece[i][j][WHITE_BOARD] << " ";
            }
        }
        cout << "|\n";
    }
    cout << endl;
}

void print_warning(int &count, int color)
{
    if (count < 4)
    {
        cout << "\nWARNING: THIS MOVEMENT IS NOT VALID, PLEASE TRY AGAIN!\n\n";
    }
    else
    {
        cout << "\nYOU FAILED TO PROVIDE AN VALID INPUT TOO MANY TIMES\n"
             << "GO READ THE RULES AND COME BACK LATER!\n";
        if (color == 0)
        {
            cout << "Player 2 wins!\n";
            count++;
            return;
        }
        else
        {
            cout << "Player 1 wins!\n";
            count++;
            return;
        }
    }
    count++;
}

void print_winner(int color)
{
    if (color == 0)
    {
        cout << "Player 2 wins!\n";
        return;
    }
    else
    {
        cout << "Player 1 wins!\n";
        return;
    }
}