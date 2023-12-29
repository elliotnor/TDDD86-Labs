#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"
#include "shuffle.h"
#include <set>

using namespace std;

class Boggle {
public:
    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;
    Lexicon lexicon;

    Boggle();

    // Generates a board containing the chars from the input.
    void loadCustomBoard(string customBoard);

    // Generates a board containing a random cube value in each position.
    void Randomizer();

    // Returns grid cubes.
    Grid<char> getCubes();

    // Checks if word is already located in "playerWords" or "computerWords".
    // Returns true only if it is not found in either.
    bool isNewWord(string& word);

    // Adds word to set "playerWords".
    void addWordToPlayer(string& word);

    // Adds word to set "computerWords".
    void addWordToComputer(string& word);

    // Returns set "playerWords".
    set<string> getPlayerWords();

    // Returns set "computerWords".
    set<string> getComputerWords();

    // Clears sets "playerWords" and "computerWords".
    void clearAllWords();

    // Returns the value of playerScore.
    int getPlayerScore();

    // Returns the value of computerScore.
    int getComputerScore();

    // Increases playerScore by a given amount.
    void increasePlayerScore(const int& increase);

    // Increases computerScore by a given amount.
    void increaseComputerScore(const int& increase);

    // Sets playerScore and computerScore to 0.
    void clearAllScores();

    // Initiates the search for a word on the board. Generates the coordinates for "findWordAt".
    // Returns true if it has been located on the board.
    bool findWord(string& word);

    // Checks if the word can be found starting at a specific coordinate.
    // Returns true if it has been able to find every letter in the word in a vaĺid way.
    bool findWordAt(string& word, const int& y, const int& x, set<pair<int, int>>& visitedCubes2);

    // Generates coordinates on the board and initiates getWord for each of those coordinates.
    // Used by the computer.
    void findAllWords();

    // Recursively finds all words that can be gernerate starting at a specific coordinate.
    // Adds every located word to computerWords.
    void getWord(string& start, const int& y, const int& x, set<pair<int, int>>& visitedCubes2);


private:
    Grid<char> cubes;
    set<string> computerWords;
    set<string> playerWords;
    int playerScore;
    int computerScore;
};
#endif
