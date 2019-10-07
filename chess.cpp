// chess.cpp
#include "ChessEngine.h"

/** helper function to get player name from user input */
std::string getPlayerName(std::string message);

/** gets player names, constructs a chessEngine and starts playing */ 
int main()
{
	std::string whiteName, blackName;
	
	whiteName = getPlayerName("Enter white player name:\n");
	blackName = getPlayerName("Enter black player name:\n");
	ChessEngine game {whiteName, blackName};
	game.run();
	return 0;
}


// as Yoni explained in the tirgul - it's okay to use std::getline into a std::string 
// because std::string takes from the input stream in chunks and resize std::string on the heap,
// so there's no chance for buffer overflow or accessing illegal places on the heap

/**
* @param message a message to be printed when prompting for input
* @return the name the user inputted
*/
std::string getPlayerName(std::string message)
{
	std::string input;
	std::cout << message;
	std::getline(std::cin, input); // No fear for overflow
	return input;
}
