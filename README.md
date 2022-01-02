# ChessGame
The project was elaborated as the final project for Computer Science I at Whitworth University.

The project consists of a chess game that can be played by 2 players. 

This project was co-created by Fabian Gomez.

Developed by Matheus Mielle Silva and Fabian Gomez

Developed on: December 16th, 2021

License: Only project developers are allowed to edit or share this file electronically unless such permission is given by the developers.

Copyright (C) Matheus M Silva 2021

Copyright (C) Fabian Gomez 2021

1.	The purpose of this project is to create a chess game. Is going to display a representation of a chessboard on the screen. Is a 1 vs 1 game. The users will be able to choose a piece and then choose where they want to move it. The program will keep asking the user for input if he enters information out of bound. The program will get rid of an eliminated piece. The program calculates the behavior of each individual piece, for example, a tower can just move in a straight line. The program ends when one of the kings is captured or the user attempts an invalid move more than 5 times.

2.	Assumptions: 

a.	If the user enters a number less than 1 or greater than 8 and a letter greater than H, the program wouldn’t work. It will do something random or weird.

b.	The user could choose a new position but there might be a current piece blocking the way and the program will still locate the piece in the new position.

c.	User make a mistake inputting the location of the piece he wants to move or the location where he want to move the piece.

d.	User could try to swap one of his pieces with another of his pieces.

3.	Reason for the design

a.	We choose to use functions instead of an array because is what we know how to use better than classes and we feel more confident with them.

b.	We choose a 3D array because it could hold all the important information we needed for the board: the white and black pieces and their corresponding color. This makes it all more compact, cleaner, and easy to understand for us.

c.	We create one function for every piece. This is for good functionalization; every function should do one specific task.

d.	For the checker we mainly use if statement. The reason is that most of the pieces except the pawn can move in four different positions. Depending in the new current location of the piece and the new location the program determines in what direction the piece is going.

e.	Inside of the if statement we have more if statements, do while loops and for loop. We have a combine the do while loop with a for loop. The reason in that we tried a nested for loop and we were not able to make it work so we tried something different. The if statements are to make sure that all the condition to move the piece the user choose are fulfilled.

4.	Cite

a.	Libraries:

i.	#include <iostream>
  
ii.	#include <cctype>
  
iii.	#include <checkers.h>
  
iv.	#include <assign_boards.h>
  
v.	#include <string.h>
  
vi.	#include <swap.h>
  
vii.	#include <print.h>
  
viii.	#include <get_funcs.h>
  
ix.	using namespace std;
  
b.	Website:
  
i.	To verify the independent behavior of every piece https://www.wholesalechess.com/pages/new-to-chess/pieces.html
  
c.	Credit to: 
  
i.	Andre East student at Whitworth University currently enroll in Computer Science II. He helps use with a brainstorm about making a specific function for every single piece in the board.
 




		
	
	














	
	

