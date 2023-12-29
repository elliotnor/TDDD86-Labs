//Boogle main file

#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include <string>



static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {        // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};


Boggle::Boggle(){
    this->lexicon = Lexicon(DICTIONARY_FILE);
    cubes = Grid<char>(BOARD_SIZE, BOARD_SIZE);
}


void Boggle::loadCustomBoard(string customBoard){
    for(unsigned int i = 0; i < NUM_CUBES; i++){
        cubes[i / BOARD_SIZE][i % BOARD_SIZE] = customBoard[i];
    }
}


void Boggle::Randomizer(){
    for(int i = 0; i < NUM_CUBES; i++){
            cubes[i / BOARD_SIZE][i % BOARD_SIZE] = CUBES[i][rand() % 6];
        }
    shuffle(cubes);
}

Grid<char> Boggle::getCubes(){
    return this->cubes;
}
bool Boggle::isNewWord(string& word){
    return computerWords.find(word) == computerWords.end() && playerWords.find(word) == playerWords.end();
}

void Boggle::addWordToPlayer(string& word){
    playerWords.insert(word);
}

void Boggle::addWordToComputer(string& word){
    computerWords.insert(word);
}

set<string> Boggle::getPlayerWords(){
    return playerWords;
}

set<string> Boggle::getComputerWords(){
    return computerWords;
}

void Boggle::clearAllWords(){
    playerWords.clear();
    computerWords.clear();
}

int Boggle::getPlayerScore(){
    return playerScore;
}

int Boggle::getComputerScore(){
    return computerScore;
}

void Boggle::increasePlayerScore(const int& increase){
    playerScore += increase;
}

void Boggle::increaseComputerScore(const int& increase){
    computerScore += increase;
}

void Boggle::clearAllScores(){
    playerScore = 0;
    computerScore = 0;
}

bool Boggle::findWord(string& word){
    set<pair<int,int>> visitedCubes;
    if(this->lexicon.contains(word)){
        if(word.length() >= MIN_WORD_LENGTH){
            if(isNewWord(word)){
                for(int y = 0; y < this->BOARD_SIZE; y++){
                    for(int x = 0; x < this->BOARD_SIZE; x++){
                        if(findWordAt(word, y,x, visitedCubes)){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Boggle::findWordAt(string& word, const int& y, const int& x, set<pair<int, int>>& visitedCubes){
    set<pair<int, int>> tempVisitedCubes;
    if(word.length() == 0){
        return true;
    }
    string tempWord = word.substr(1);
    if(trim(toUpperCase(string(1,word[0]))) == trim(toUpperCase(string(1, cubes[y][x])))){
        if(visitedCubes.find(pair<int, int>(y,x)) == visitedCubes.end()){
            visitedCubes.insert(pair<int,int>(y,x));
            for(int tempY = y-1; tempY <= y+1; tempY++){
                for(int tempX = x-1; tempX <= x+1; tempX++){
                    if(cubes.inBounds(tempY, tempX) && !(x == tempX && y == tempY)){
                        tempVisitedCubes = visitedCubes;
                        if(findWordAt(tempWord, tempY, tempX, tempVisitedCubes)){
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

void Boggle::findAllWords(){
    set<pair<int, int>> visitedCubes;
    string start;
    for(int y = 0; y < this->BOARD_SIZE; y++){
        for(int x = 0; x < this->BOARD_SIZE; x++){
            start = trim(toUpperCase(string(1,cubes[y][x])));
            getWord(start, y, x, visitedCubes);
        }
    }
}

void Boggle::getWord(string& start, const int& y, const int& x, set<pair<int, int>>& visitedCubes){
    set<pair<int, int>> tempVisitedCubes;
    tempVisitedCubes = visitedCubes;
    tempVisitedCubes.insert(pair<int,int>(y,x));
    string tempWord;
    if(this->lexicon.contains(start)){
        if(isNewWord(start) && start.length() >= 4){
            increaseComputerScore(start.length());
            computerWords.insert(start);
        }
    }
    for(int tempY = y-1; tempY <= y+1; tempY++){
        for(int tempX = x-1; tempX <= x+1; tempX++){
            if(visitedCubes.find(pair<int, int>(tempY,tempX)) == visitedCubes.end()){
                if(cubes.inBounds(tempY, tempX) && !(x == tempX && y == tempY)){
                    tempWord = start + trim(toUpperCase(string(1,cubes[tempY][tempX])));
                    if(this->lexicon.containsPrefix(tempWord)){
                        getWord(tempWord, tempY, tempX, tempVisitedCubes);
                    }
                }
            }
        }
    }
}
