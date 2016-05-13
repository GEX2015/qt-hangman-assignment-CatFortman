////////////////////////////////////////////////////////////
///     Cat Fortman
///     QT
///     Hangman project
///
///////////////////////////////////////////////////////////

#ifndef HANGMANCLASS_H
#define HANGMANCLASS_H
#pragma once

#include <string>
#include <map>
#include <iostream>
#include <vector>
#include <set>
#include <sstream>

enum class Picture { ONE,
                    TWO,
                    THREE,
                    FOUR,
                    FIVE,
                    SIX,
                    SEVEN
                  };

class hangmanClass
{
public:
    hangmanClass();								// opens hamgman.txt and gets phrases
    ~hangmanClass();

    void initGame();							// initializes the game

    void processGuess(std::string guess);

    char getCharResponse();						// get sthe char response

    Picture showGallows();
    std::string showHiddenPhrase();
    std::string showPhrase();

    std::string newPhrase();

    void loadPhrases();
    void shufflePhrases();

    bool letterGuessed(std::string guess);

    bool won();
    bool lost();

private:
    std::string phrase;							// holds one phrase
    std::vector <std::string> phrases;			// holds the phrases

    static const int ALLOWED_MISSES = 6;		// constant allowed misses

    std::map<std::string, int> _correctGuesses;	// correct guesses in map
    std::map<std::string, int> misses;			// missed letters in map
    std::string dash;							// string to convert word with dashes
    std::string spaces;							// string to convert original word to have spaces

    static const std::vector<Picture> _pictureList;
};


#endif // HANGMANCLASS_H
