#include "Hangman.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>
#include <string> 
#include <map>
#include <ctime>
#include <cstdlib>

Hangman::Hangman(std::string path)
{

	std::ifstream inFile(path);					// enter in phrases form hangman.txt
	if (!inFile.fail())
	{
		while (!inFile.eof())
		{
			if (!inFile.eof())
			{
				getline(inFile, phrase);
				phrases.push_back(phrase);		// put phrases in vector called phrases
			}
		}
	}
	else
	{											// fail catch
		std::cout << "Error opening file for write\n";
		exit(EXIT_FAILURE);
	}

	inFile.close();
}


Hangman::~Hangman()
{
}

char Hangman::getCharResponse()
{
	char userInput;

	std::cin >> userInput;//input that user chooses

	while (std::cin.fail())//if char input fails
	{
		std::cin.clear();
		std::cin.ignore();
		std::cin >> userInput;
	}

	//return result
	return userInput;
}

void Hangman::welcome() const					// main menu
{
	system("cls");
	std::cout << "\t******************************** HANGMAN ********************************\n\n"
		<< "\t This game you will be guessing letters until you geuess the correct phrase or\n"  
		<< "\t word\n"
		<< "\t You have 7 guesses!\n\n"
		<< "\t Good luck!!\n\n"
		<< "\t Press (Y) to play  or (N) to not play\n";
}

void Hangman::play()
{
	if (round > phrases.size()) // makes sure to start over the text file 
	{
		round = 0;
	}

	for (auto p: phrases)						// make dash word
	{
		int length = p.length();
		for (int i = 0; i < length; i++)
		{
			if( p.at(i) == (' '))			    // checks for space
			{
				dash.append("  ");
			}
			else
			{
				dash.append("_ ");
			}
		}

		dashes.push_back(dash);
		dash = "";
	}

	for (auto p : phrases)						// make word/phrase with spaces
	{
		std::string word = p;
		int length = p.length();
		for (int i = 0; i < length; i++)
		{
			char letter = word.at(i);
			full.push_back(letter);
			full.push_back(' ');
		}
		phraseWSpaces.push_back(full);
		full = "";
	}

	int r = rand() % 16;							// gets random number for word
	
	std::cout << "\n\n\tOkay so here is your word! \n\n";

	std::string hidden = dashes[r];					// this is the dash word
	std::string word = phraseWSpaces[r];			// this is the phrase with spaces

	size_t extraCount = phrases[r].find(' ', 0);	// finds the spaces in phrase
	while (extraCount != std::string::npos)			    // adds extra correct guess count to balance the phrases with spaces
	{
		extraCount = phrases[r].find(' ', extraCount+1);
		correctGuessed++;
	}

	while((misses.size() != ALLOWED_MISSES) && (won != true) )		// while the user doesn't win or they miss too many letters
	{
		std::cout << "\t\t Phrase/Word: " << hidden << "\n";		// shows hidden phrase
		std::cout << "\t\t Misses: ";								
		for (auto& e : misses)										// shows missed characters
		{
			std::cout  << e.first << " ";
		}
		std::cout << "\n\t\t Misses left: " << (ALLOWED_MISSES - misses.size()) << "\n\n"; // shows misses left
		std::cout << "Please enter your guess\n";

		std::string guess;																	// gets users guess
		std::cin >> guess;
		
		size_t found = word.find(guess);													// finds the characters guess

		if (found != std::string::npos)														// if it is found enter loop
		{
			auto itr = correctGuesses.find(guess);									
			auto itr2 = misses.find(guess);

			if (itr != correctGuesses.end())											    // if you already guessed it
			{
				std::cout << "\nYou already guessed that letter! \n" << std::endl;
			}
			else
			{
				size_t found = word.find(guess, 0);
				while (found != std::string::npos)											// if it occurs more than once
				{
					hidden.replace(found, 1, guess);
					found = word.find(guess, found + 1);
					correctGuessed++;														// incriment correct guessed
				}
				correctGuesses[guess]++;
				std::cout << "\nGood job! You guessed a correct letter! :3 \n" << std::endl;
				guesses.insert(guess);														// insert guess into guesses
				if (correctGuessed == phrases[r].length())								// if you guess all the right letters
				{
					won = true;
					std::cout << "\t\t " << hidden << "\n";
					std::cout << "\nHOORAY!!!! You won!!! \n\n" << std::endl;
				}
			}
		}
		else
		{
			auto itr2 = misses.find(guess);													// checks if you already guessed by iterator not equaling the end
			if (itr2 != misses.end())
			{
				std::cout << "\nYou already guessed that letter! \n" << std::endl;
			}																						// prints the hangman depedning on guesses
			else
			{
				std::cout << "\nI'm sorry you guessed incorrectly :( \n" << std::endl;
				misses[guess]++;

				if (misses.size() == 1)
				{
					std::cout << "   _____ \n";
					std::cout << "  |     |\n";
					std::cout << "  |     O\n";
					std::cout << "  |    \n";
					std::cout << "  |     \n";
					std::cout << "  |    \n";
					std::cout << " _|_\n";
					std::cout << "|   |_______\n";
					std::cout << "|           |\n";
					std::cout << "|___________|\n";
				}
				else if (misses.size() == 2)
				{
					std::cout << "   _____ \n";
					std::cout << "  |     |\n";
					std::cout << "  |     O\n";
					std::cout << "  |     |\n";
					std::cout << "  |     \n";
					std::cout << "  |    \n";
					std::cout << " _|_\n";
					std::cout << "|   |_______\n";
					std::cout << "|           |\n";
					std::cout << "|___________|\n";

				}
				if (misses.size() == 3)
				{
					std::cout << "   _____ \n";
					std::cout << "  |     |\n";
					std::cout << "  |     O\n";
					std::cout << "  |    /|\n";
					std::cout << "  |     \n";
					std::cout << "  |   \n";
					std::cout << " _|_\n";
					std::cout << "|   |_______\n";
					std::cout << "|           |\n";
					std::cout << "|___________|\n";

				}
				if (misses.size() == 4)
				{
					std::cout << "   _____ \n";
					std::cout << "  |     |\n";
					std::cout << "  |     O\n";
					std::cout << "  |    /|\\\n";
					std::cout << "  |     \n";
					std::cout << "  |    \n";
					std::cout << " _|_\n";
					std::cout << "|   |_______\n";
					std::cout << "|           |\n";
					std::cout << "|___________|\n";

				}
				if (misses.size() == 5)
				{
					std::cout << "   _____ \n";
					std::cout << "  |     |\n";
					std::cout << "  |     O\n";
					std::cout << "  |    /|\\\n";
					std::cout << "  |     |\n";
					std::cout << "  |    \n";
					std::cout << " _|_\n";
					std::cout << "|   |_______\n";
					std::cout << "|           |\n";
					std::cout << "|___________|\n";

				}
				if (misses.size() == 6)
				{
					std::cout << "   _____ \n";
					std::cout << "  |     |\n";
					std::cout << "  |     O\n";
					std::cout << "  |    /|\\\n";
					std::cout << "  |     |\n";
					std::cout << "  |      \\\n";
					std::cout << " _|_\n";
					std::cout << "|   |_______\n";
					std::cout << "|           |\n";
					std::cout << "|___________|\n";

				}
				if (misses.size() == 7)
				{
					std::cout << "   _____ \n";
					std::cout << "  |     |\n";
					std::cout << "  |     O\n";
					std::cout << "  |    /|\\\n";
					std::cout << "  |     |\n";
					std::cout << "  |    / \\\n";
					std::cout << " _|_\n";
					std::cout << "|   |_______\n";
					std::cout << "|           |\n";
					std::cout << "|___________|\n";

				}
			}
		}
	}
	

	round++;															// adds another round
}

void Hangman::initGame()
{
	//clears variables for next game
	won = false;								// makes won false
	guesses.clear();							// clears guesses
	correctGuesses.clear();						// clears correct guesses
	misses.clear();								// clears misses
	phraseWSpaces.clear();						// clears my phrases with spaces 
	dashes.clear();								// clears the dash word
	correctGuessed = 0;							// clears corrcetGuesses
}

