///////////////////////////////////////////////////////////////////////////////////////////////////
//
// Final Project for CS-313 - Whitworth University
//
// Developed by Matheus Mielle Silva and Fabian Gomez
// Developed on: December 16th, 2021 for CS171-3
// Updated on December 2nd, 2023 for CS313
// Updated by Matheus Mielle Silva, Fabian Gomez, Bereket Lemma, and Lex Sinclair
//
// License: Only project developers are allowed to edit or share
// this file electronically unless such permission is given by the developers.
//
// Copyright (C) Matheus Mielle Silva 2021
// Copyright (C) Fabian Gomez 2021
// Copyright (C) Bereket Lemma 2023
// Copyright (C) Lex Sinclair 2023
//
///////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cctype>
#include <string>
#include <thread>
#include <chrono>
#include "../../Socket.h"

using namespace std;

#define WHITE_BOARD 0 // Board index 0 is white
#define BLACK_BOARD 1 // Board index 1 is black
#define BLANK_BOARD 2 // Board index 2 is blank
#define sides 8       // The size of the board array
#define MYPORT 50001  // Communication Port to connect to/from

// Utility Function for clean exit of program
//  @input: message, display to the terminal to prompt for exit
//  Closes socket and exits program
int done(const string message);

/* Crates 3 boards:
    -White(index 0): contains pieces in the first 2 rows, 0 representing blank spaces,
        in the next 4 rows and * representing the opponent's pieces in the last 2 rows
    - Black(index 1): contains * representing the opponent's pieces in the first 2 rows,
        0 representing blank spaces in the next 4 rows and pieces in the last 2 rows
    -Blank (index 2): The full board is composite by ' ' */
// Input: the board array.
void assign_pieces(char piece[sides][sides][3]);

// Verify which piece was chosen by the user.
/*Input: The board array, i(for row, inputted by the user),
j (for column inputted by the user) and the color of the piece.*/
/*Output the char of the piece (p for pawn, k for king ...), 0 for
blank space and * for opponent's piece*/
char check_pieces(char array[sides][sides][3], int i, int j, int color);

// Verify if the piece the user chose is in the board
/* Converts the user input in the format string (letter and number(A1)) to the
format int i (0-7) and int j (0-7) so that it can be used in the array. */
/* Output: false for out of the array bounders input or if the input is not in the
rules format and true for input according to the rules and limits of the board array*/
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
// Output: true for valid move and false for invalid move.
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
// Output: true for valid move and false for invalid move.
bool is_move_valid(char array[sides][sides][3], int cur_i, int cur_j, int color, int new_i, int new_j);

// Returns a char for what the person wants to promote their pawn to as long as promotion is valid
char promotePawn(char array[sides][sides][3], int i, int j, int color, char piece);

// Return true or false based on checkmate
bool is_checkmate(char array[sides][sides][3], int color);

// Grab the user input
/*Input: cur_i(for row of piece in the inital position, provided by the user),
cur_j (for column of piece in the inital position, provided by the user ),
new_i(for row of the place the user want to move the piece), new_j(for column
of the place the user want to move the piece), and the color of the piece.*/
void get_input(int &cur_i, int &cur_j, int color, int &new_i, int &new_j, Socket &S);

// Change the color of the board based on the round
/* Input: color of curent player, the opposite color (if it's white the
opposite color is black) and count(the round counter)*/
void get_color(int &color, int &opposite_color, int &count);

// Display functions
string print_header(int player, string color);
void print_player(int color, string &p1, string &p2);
string print_board(char piece[sides][sides][3]);
string print_warning(int &count, int color);
string print_winner(int color);

// Swap the pieces in the board array
/* Input: array (the board array), i(the x location of one piece), j(the y location of
one piece), color of the pieces in the board array change_i (the x location of the other
piece) change_j (the y location of the other piece*/
void swap_array(char array[sides][sides][3], int i, int j, int color, int change_i, int change_j);

// promotion function
// When the pawn reaches the opposite end of the board, it will be promoted to anything but a king and pawn
void promotePawn(char array[sides][sides][3], int i, int j, int color, Socket &S);

// THE SERVER: serves clients
int main()
{
    // Initilize socket, make sure network stack is available
    if (!Socket::Init())
    {
        cerr << "Fail to initialize WinSock!\n";
        return -1;
    }

    // Step 1: Create a TCP socket
    Socket server("tcp");

    // Step 2: Bind socket to a port (MYPORT)
    if (!server.sock_bind("", MYPORT))
    {
        string str;
        str = "Could not bind to port " + to_string(MYPORT);
        done(str);
    }

    // Step 3: Ask my socket to "listen"
    if (!server.sock_listen(1))
    {
        done("Could not get socket to listen");
    }

    cout << "Server is now listening on port " << MYPORT << endl;

    // Step 4:	Wait to accept a connection from a client.
    //			The variable conn is the "connected" socket.  This is the socket that is actually connected to the server.
    //			The socket variable server can be used to accept another connection if you want.

    Socket conn_1 = server.sock_accept();
    cout << "Player one is connected to me.\n";
    conn_1.msg_send("Connection Successful. Waiting for Player 2\n");

    Socket conn_2 = server.sock_accept();
    cout << "Player two is connected to me.\n";
    conn_2.msg_send("Connection Successful.\n");

    // Step 5: Receive/send a message from/to the client.
    conn_1.msg_send(print_header(1, "white"));
    conn_2.msg_send(print_header(2, "black"));

    // Board config
    char pieces[sides][sides][3];
    int cur_i, cur_j, new_i, new_j;
    assign_pieces(pieces);
    int round_count = 1;
    int color;
    int opposite_color;
    int warning_count = 0;
    get_color(color, opposite_color, round_count);

    // main game loop
    do
    {
        string p1;
        string p2;

        print_player(color, p1, p2);

        conn_1.msg_send(p1);
        conn_1.msg_send(print_board(pieces));

        conn_2.msg_send(p2);
        conn_2.msg_send(print_board(pieces));

        cout << p1 << endl << p2 << endl << print_board(pieces) << endl;

        this_thread::sleep_for(chrono::milliseconds(500));

        if (color == WHITE_BOARD)
        {
            conn_1.msg_send("GET");
            get_input(cur_i, cur_j, color, new_i, new_j, conn_1);
        }
        else if (color == BLACK_BOARD)
        {
            conn_2.msg_send("GET");
            get_input(cur_i, cur_j, color, new_i, new_j, conn_2);
        }

        if (is_move_valid(pieces, cur_i, cur_j, color, new_i, new_j))
        {
            if (color == WHITE_BOARD)
            {
                // conn_1.msg_send("INPUT SUCCESSFUL");
                warning_count = 0;
                if (check_pieces(pieces, new_i, new_j, color) == '*')
                {
                    pieces[new_i][new_j][opposite_color] = '0';
                    pieces[new_i][new_j][color] = '0';
                }
                swap_array(pieces, cur_i, cur_j, color, new_i, new_j);
                swap_array(pieces, cur_i, cur_j, opposite_color, new_i, new_j);
                promotePawn(pieces, new_i, new_j, color, conn_1);
                get_color(color, opposite_color, round_count);
            }
            else
            {
                // conn_2.msg_send("INPUT SUCCESSFUL");
                warning_count = 0;
                if (check_pieces(pieces, new_i, new_j, color) == '*')
                {
                    pieces[new_i][new_j][opposite_color] = '0';
                    pieces[new_i][new_j][color] = '0';
                }
                swap_array(pieces, cur_i, cur_j, color, new_i, new_j);
                swap_array(pieces, cur_i, cur_j, opposite_color, new_i, new_j);
                promotePawn(pieces, new_i, new_j, color, conn_2);
                get_color(color, opposite_color, round_count);
            }
        }
        else
        {
            if (color == WHITE_BOARD)
            {
                conn_1.msg_send(print_warning(warning_count, color));
                cout << print_warning(warning_count, color) << endl;
            }
            else
            {
                conn_2.msg_send(print_warning(warning_count, color));
                cout << print_warning(warning_count, color) << endl;
            }
        }

    } //while (true);
    // while (is_checkmate(pieces, color) == false && warning_count < 5);
    while(is_king_alive(pieces) && warning_count < 5);

    conn_1.msg_send(print_board(pieces));
    conn_2.msg_send(print_board(pieces));

    conn_1.msg_send(print_winner(color));
    conn_2.msg_send(print_winner(color));

    this_thread::sleep_for(chrono::milliseconds(500));
    conn_1.msg_send("DONE");
    conn_2.msg_send("DONE");
}

int done(const string message)
{
    Socket::Cleanup();
    cout << message;
    cin.get();
    exit(0);
}

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
    // For white pieces the pawn should be in the second row in order to be its first move
    if (color == WHITE_BOARD)
    {
        if (i != 1)
        {
            return false;
        }
    }
    // For black pieces the pawn should be in the seventh row in order to be its first move
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

        // Column movements:

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

        // Column movements:

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
    int true_count = 0; // Increase if the user attempt to move the King

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
    // Using the function for the tower for checking the vertical and horizontal moves of the queen
    if (t_Valid(array, cur_i, cur_j, color, new_i, new_j))
    {
        return true;
    }
    // Using the function for the bishop for checking diagonal moves of the queen
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

void promotePawn(char array[sides][sides][3], int i, int j, int color, Socket &S)
{
    char piece = check_pieces(array, i, j, color); // Can check what piece is latter in the debuging
    string promotionChoice;
    bool right_pice = false;
    // Pawn are the only one that can promote
    // Pawn can oly move forwar. Therefore, in can only promote in square 0 and 7
    if (piece == 'P' && (i == 7 || i == 0))
    {

        while (!right_pice)
        {
            // Allow the player to choose the promoted piece
            S.msg_send("PROMOTE");
            this_thread::sleep_for(chrono::milliseconds(500));
            S.msg_send("Choose a piece to promote the pawn to! (T for Rook, H for Knight, B for Bishop, Q for Queen): ");
            promotionChoice = S.msg_recv();

            // cout << "Choose a piece to promote the pawn to! (T for Rook, H for Knight, B for Bishop, Q for Queen): ";
            // cin >> promotionChoice;
            switch (toupper(promotionChoice[0]))
            {
            case 'T':
                array[i][j][color] = 'T'; // Return a 'T' because is what the programang understand. The wors ROOK is not a thing in this code
                right_pice = true;
                break;
            case 'H':
                array[i][j][color] = 'H';
                right_pice = true;
                break;
            case 'B':
                array[i][j][color] = 'B';
                right_pice = true;
                break;
            case 'Q':
                array[i][j][color] = 'Q';
                right_pice = true;
                break;
            default:
                S.msg_send("Promote Fail! Promoting it to a Knight!");
                array[i][j][color] = 'H';
            }
        }
    }
}

bool is_checkmate(char array[sides][sides][3], int color)
{
    // Check if the king is in check
    if (!is_king_alive(array))
    {
        return false; // King is not in check, no checkmate
    }
    // Check if there are any legal moves for the king
    for (int i = 0; i < sides; i++)
    {
        for (int j = 0; j < sides; j++)
        {
            char piece = array[i][j][color];
            if (piece == 'K')
            { // Check all possible king moves
                // Generate all legal moves for the king
                for (int di = -1; di <= 1; di++)
                {
                    for (int dj = -1; dj <= 1; dj++)
                    {
                        if (di == 0 && dj == 0)
                            continue; // Skip the king's current position

                        int new_i = i + di;
                        int new_j = j + dj;
                        // check if the new position is valid and not occupied by other pieces
                        //  Check if the new position is valid and not occupied by a friendly piece
                        if (new_i >= 0 && new_i < sides && new_j >= 0 && new_j < sides &&
                            array[new_i][new_j][color] != 'K')
                        {
                            // Make a temporary move to the new position
                            // if (!is_king_in_check(array, color))
                            //{
                            //    // King can escape check with this move, not checkmate
                            //    array[i][j][color] = temp_piece;
                            //    array[new_i][new_j][color] = '-';
                            //    return false;
                            //}

                            // Undo the temporary move
                            // array[i][j][color] = temp_piece;
                            // array[new_i][new_j][color] = '-';
                        }
                    }
                }
            }
        }
    }

    // No legal moves for the king in check, checkmate
    return true;
}

void get_input(int &cur_i, int &cur_j, int color, int &new_i, int &new_j, Socket &S)
{
    cur_i = 0;
    cur_j = 0;
    new_i = 0;
    new_j = 0;
    string position;
    do // Until the user choice an exiting piece
    {
        S.msg_send("What piece do you want to move? ");
        position = S.msg_recv();
        cout << "Player " << color+1 << " chose piece "<< position << endl;
    } while (!check_input(position, cur_i, cur_j));
    do // Until the user choice an existing position
    {
        S.msg_send("To what position? ");
        position = S.msg_recv();
        cout << "Player " << color+1 << " moved piece to "<< position << endl;
    } while (!check_input(position, new_i, new_j));
}

void get_color(int &color, int &opposite_color, int &count)
{
    if (count % 2 != 0)
    {
        color = WHITE_BOARD;
        opposite_color = BLACK_BOARD;
        count++;
    }
    else
    {
        color = BLACK_BOARD;
        opposite_color = WHITE_BOARD;
        count++;
    }
    return;
}

string print_header(int player, string color)
{
    string s;

    s = "\n          WELCOME TO A GAME OF CHESS!\n";
    s += "\nHow to Play?\n";
    s += "There's two players playing this game:\n";
    s += "-You are Player ";
    s += to_string(player);
    s += "\n-You controls the ";
    s += color;
    s += " pieces.\n";
    s += "-The rules of the game can be found at https://www.ichess.net/blog/chess-pieces-moves/\n";
    s += "-I truly recommend to read them before playing\n";
    s += "-When it's your turn to play you should type the letter of the column the piece/spot is ";
    s += "followed by the number of the row.\n";
    s += "-Only the first two typed characters will be recognized\n";
    s += "-If you type a combination of letter and number that is not in the board or";
    s += "if you type in the wrong order, the program will ask for input again.\n";
    s += "-If what you type is in the right format but you selected the wrong piece";
    s += "or make a forbidden move, a warning will pop up\n";
    s += "-You can receive up to 5 warnings before the game ends and declare the other player as the winner.\n";
    s += "\n                    Good Luck! Have Fun!\n";

    return s;
}

void print_player(int color, string &p1, string &p2)
{
    p1 = "";
    p2 = "";

    if (color == WHITE_BOARD)
    {
        p1 += "\nPlayer 1, It's your turn.\n\n";
        p2 += "\nIt's player 1 turn!\n\n";
    }
    else if (color == BLACK_BOARD)
    {
        p2 += "\nPlayer 2, It's your turn.\n\n";
        p1 += "\nIt's player 2 turn!\n\n";
    }
}

string print_board(char piece[sides][sides][3])
{
    string s = "";

    s += "   | -A | -B | -C | -D | -E | -F | -G | -H |\n";
    s += "___|____|____|____|____|____|____|____|____|\n";
    for (int i = 0; i < sides; i++) // Loop the numbers of time of the array
    {
        s += to_string(i + 1);
        s += "  ";

        for (int j = 0; j < sides; j++)
        {
            if (check_pieces(piece, i, j, WHITE_BOARD) == '0')
            {
                s += "|  ";
                s += piece[i][j][BLANK_BOARD];
                s += " ";
            }
            else if (check_pieces(piece, i, j, WHITE_BOARD) == '*')
            {
                s += "| B";
                s += piece[i][j][BLACK_BOARD];
                s += " ";
            }
            else
            {
                s += "| W";
                s += piece[i][j][WHITE_BOARD];
                s += " ";
            }
        }
        s += "|\n";
    }
    s += "\n";

    return s;
}

string print_warning(int &count, int color)
{
    string s = "";

    if (count < 4)
    {
        s += "\nWARNING: THIS MOVEMENT IS NOT VALID, PLEASE TRY AGAIN!\n\n";
    }
    else
    {
        s += "\nYOU FAILED TO PROVIDE AN VALID INPUT TOO MANY TIMES\n";
        s += "GO READ THE RULES AND COME BACK LATER!\n";

        if (color == 0)
        {
            s += "Player 2 wins!\n";
            count++;
            return s;
        }
        else
        {
            s += "Player 1 wins!\n";
            count++;
            return s;
        }
    }
    count++;

    return s;
}

string print_winner(int color)
{
    string s;
    if (color == 0)
    {
        s += "Player 2 wins!\n";
        return s;
    }
    else
    {
        s += "Player 1 wins!\n";
        return s;
    }
}

void swap_array(char array[sides][sides][3], int i, int j, int color, int change_i, int change_j)
{
    char temp = array[i][j][color];                        // Save the piece in temp
    array[i][j][color] = array[change_i][change_j][color]; // Replace the piece for other
    array[change_i][change_j][color] = temp;               // Input the store piece in temp
}


