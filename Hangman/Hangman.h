#pragma once
#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <sstream>

class Hangman
{
public:
	Hangman(std::string path);					// opens hamgman.txt and gets phrases
	~Hangman();
	void welcome() const;						// displays welcome message
	void play();								// begins the hangman game
	char getCharResponse();						// get sthe char response
	void initGame();							// initializes the game

private:
	std::string phrase;							// holds one phrase
	std::vector <std::string> phrases;			// holds the phrases
	std::map<char, bool> lettersInPhrase;		// holds all the letters in the phrase

	static const int ALLOWED_MISSES = 7;		// constant allowed misses

	bool won = false;

	int round = 0;								// keeps track of games played

	std::set<std::string> guesses;				// guessed letters in all
	std::map<std::string, int> correctGuesses;	// correct guesses in vector
	std::map<std::string, int> misses;			// missed letters in vector
	std::vector<std::string> phraseWSpaces;		// my phrases with spaces 
	std::vector<std::string> dashes;			// the dash word
	std::string dash;							// string to convert word with dashes
	std::string full;							// string to convert original word to have spaces
	int correctGuessed = 0;						// counts how many corrcet guesses
};

