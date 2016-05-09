//Cat Fortman


//hangman game();
//game.welcome();
//while still want to play;
//(main)

//file with phrases
//vector for phrases
//set for guesses
//counter for guesses
//look for letter in string if true go in guesses counter if false go in wrong guesses/ good and wrong guesses in set
//vector of words / phrases with spaces

#include "Hangman.h"
#include <iostream>
#include <string>

int main()
{
	std::string path = "hangman.txt"; // my text file path name
	Hangman game(path);				  // constructor takes path as argument
	game.welcome();					  // displays welcome message
	char userInput;					  // user input
	userInput = toupper(game.getCharResponse());	// makes response to play uppercase
		
		while(userInput == 'Y'){										// while you dont quit
			game.initGame();											// initialize game
			game.play();												// play the game

			std::cout << "Do you want to play again? (y/n) \n";			
			userInput = toupper(game.getCharResponse());				// makes response to play uppercase
		} while (userInput == 'Y');
}