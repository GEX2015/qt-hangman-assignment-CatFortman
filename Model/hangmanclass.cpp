////////////////////////////////////////////////////////////
///     Cat Fortman
///     QT
///     Hangman project
///
///////////////////////////////////////////////////////////

#include "hangmanClass.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <sstream>
#include <string>
#include <map>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>

const std::vector<Picture> hangmanClass::_pictureList ={ Picture::ONE,
                                                 Picture::TWO,
                                                 Picture::THREE,
                                                 Picture::FOUR,
                                                 Picture::FIVE,
                                                 Picture::SIX,
                                                 Picture::SEVEN
                                                     };

hangmanClass::hangmanClass()
{
    loadPhrases();
    shufflePhrases();
}


hangmanClass::~hangmanClass()
{
}

char hangmanClass::getCharResponse()
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

std::string hangmanClass::showHiddenPhrase()
{
    return dash;
}

std::string hangmanClass::showPhrase()
{
    return spaces;
}

void hangmanClass::initGame()
{
    //clears variables for next game
    _correctGuesses.clear();					// clears correct guesses
    misses.clear();								// clears misses
    spaces = "";								// clears the word with spaces
    dash = "";									// clears the dash word
}

void hangmanClass::loadPhrases()
{
    std::ifstream inFile("C:\\hangman.txt");					// enter in phrases form hangman.txt
    if (!inFile.fail())
    {
        do{
            getline(inFile, phrase);
            phrases.push_back(phrase);		// put phrases in vector called phrases
        }while (!inFile.eof());

        inFile.close();
    }
    else
    {											// fail catch
        std::cout << "Error opening file for write\n";
        exit(EXIT_FAILURE);
    }

}


void hangmanClass::shufflePhrases()
{
    srand ( (unsigned int)time(NULL) );
    std::random_device rng;
    std::mt19937 urng(rng());
    std::shuffle(phrases.begin(), phrases.end(), urng);
}

Picture hangmanClass::showGallows()
{

    switch (misses.size())
    {
    case 0:\
        return Picture::ONE;
        break;
    case 1:
        return Picture::TWO;
        break;
    case 2:
        return Picture::THREE;
        break;
    case 3:
        return Picture::FOUR;
        break;
    case 4:
        return Picture::FIVE;
        break;
    case 5:
        return Picture::SIX;
        break;
    default:
        return Picture::SEVEN;
        break;
    }
}

void hangmanClass::processGuess(std::string guess)
{
    if(won() || lost())
        return;

    size_t found = spaces.find(guess);													// finds the characters guess

    if (found != std::string::npos)														// if it is found enter loop
    {
        size_t found = spaces.find(guess, 0);
        while (found != std::string::npos)											// if it occurs more than once
        {
            dash.replace(found, 1, guess);
            found = spaces.find(guess, found + 1);
        }
        _correctGuesses[guess]++;
    }

    else
    {
        misses[guess]++;
    }
}

std::string hangmanClass::newPhrase()
{
    phrase = phrases[0];

    for (auto p : phrase)						// make dash word
    {
        if (p == ' ')			    // checks for space
        {
            dash.append("  ");
        }
        else
        {
            dash.append("_ ");
        }
    }


    for (auto p : phrase)						// make word/phrase with spaces
    {
        spaces.push_back(p);
        spaces.push_back(' ');
    }


    _correctGuesses[" "]++;

    return dash;
}

bool hangmanClass::won()
{
    for (auto c : phrase)
    {
        std::string s(1, c); // convert char to string
        auto it = _correctGuesses.find(s);
        if (it == _correctGuesses.end())
        {
            return false;
        }
    }
    return true;
}

bool hangmanClass::lost()
{
    if (misses.size() >= ALLOWED_MISSES)
    {
        return true;
    }
    else
        return false;
}

bool hangmanClass::letterGuessed(std::string guess)
{
    auto itr2 = misses.find(guess);													// checks if you already guessed by iterator not equaling the end
    if (itr2 != misses.end())
    {
        return true;
    }

    auto itr = _correctGuesses.find(guess);
    if (itr != _correctGuesses.end())											    // if you already guessed it
    {
        return true;
    }

    return false;
}
