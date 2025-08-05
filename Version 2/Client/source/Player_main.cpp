///////////////////////////////////////////////////////////////////////////////////////////////////
// Player_main.cpp																				 //
// Client interface for a chess game server					                 					 //
// Last updated 12/11/2023																		 //
// Originally developed by Ed Walker															 //
// Adapted by Kent Jones, Scott Griffith, and Qian Mao										   	 //
// Adapted by Matheus Silva, Fabian Gomez, Bereket Lemma and Lex Sinclair for C313 Final Project //
///////////////////////////////////////////////////////////////////////////////////////////////////.

// Obs.: on windows, use -lws2_32 when compiling

#include <iostream>		  //terminal output
#include <string>		  //Creation of messages
#include <thread>		  //Get user's input while connected to the server
#include "../../Socket.h" //Build winSock wrapper, shared definition by both client and server
#include <chrono>
using namespace std;
using std::cout;

// Communication Port to connect to/from
const int MYPORT = 50001;

// Utility Function for clean exit of program
//  @input: message, display to the terminal to prompt for exit
//  Closes socket and exits program
int done(const string message)
{
	Socket::Cleanup();
	cout << message;
	cin.get();
	exit(0);
}

void userInputThread(string &msg)
{

	getline(cin, msg);
}

// THE CLIENT: Connects to Server Application
int main()
{

	// Initialize socket, make sure network stack is available
	if (!Socket::Init())
	{
		cerr << "Fail to initialize WinSock!\n";
		return -1;
	}

	// Step 1: Create a TCP socket
	Socket client("tcp");

	// Step 2: Connect to server
	// The client will need to input the IP of the server they want to connect to
	// We are using 0.0.0.0 so any other server won't work
	bool validIP = false;
	string IPAddress = "";
	do
	{
		cout << "Please provide server IP to connect to your game:(x.x.x.x)" << endl;
		cin >> IPAddress;
		cout << "Attempting to connect to server:" << MYPORT << endl;
		if (!client.sock_connect(IPAddress, MYPORT))
		{
			cout << "Could not connect to server. Try again!" << endl;
			validIP = false;
		}
		else
		{
			validIP = true;
		}

	} while (validIP == false);

	cout << "Connected to chess server " << IPAddress << ":" << MYPORT << endl;

	cin.ignore();

	// Step 3: Successfully connected to server.  We can now send (and receive) messages.
	string msg;
	string recv;

	bool is_done = false;

	while (!is_done)
	{
		recv = client.msg_recv();

		if (recv == "GET")
		{
			// Get piece and the position to move
			for (int i = 0; i < 2; i++)
			{
				recv = client.msg_recv();
				cout << recv;
				thread userInput(userInputThread, ref(msg));
				userInput.join();
				// cout << msg << endl;
				client.msg_send(msg);
			}
		}
		else if (recv == "PROMOTE")
		{
			recv = client.msg_recv();
			cout << recv;
			thread userInput(userInputThread, ref(msg));
			userInput.join();
			client.msg_send(msg);
		}
		else if (recv == "DONE")
		{
			is_done = true;
		}
		else
		{
			cout << recv;
		}
	}

	done("Press enter to exit");
	return 0;
}
