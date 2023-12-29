//Boggle game logic file


#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
#include <string>

/*
 * Plays one game of Boggle using the given boggle game state object.
 */

void printBoard(Boggle& boggle){
    Grid<char> cubes = boggle.getCubes();
    for(int y = 0; y < cubes.numRows(); y++){
        for(int x = 0; x < cubes.numCols(); x++){
            cout<<cubes[y][x]<< " ";
    }
        cout <<endl;
    }
}

void printPlayerWords(Boggle& boggle){
    set<string> playerWords = boggle.getPlayerWords();
    cout << "Your words " << "(" << playerWords.size() << "): { ";
    for(auto it : playerWords){
        cout << it << " ";
    }
    cout << "}" << endl;
}

void printComputerWords(Boggle& boggle){
    set<string> computerWords = boggle.getComputerWords();
    cout << "It's my turn!" << endl;
    cout << "My words " << "(" << computerWords.size() << "): { ";
    for(auto it : computerWords){
        cout << it << " ";
    }
    cout << "}" << endl;
    }


void getPlayerGuesses(Boggle& boggle){
    bool done = false;
    string guess;

    while(!done){
        cout << "Type a word (or press Enter to end your turn): ";
        getline(cin, guess);
        cout << endl;
        clearConsole();
        printBoard(boggle);
        cout << endl;
        if(guess.empty()){
            break;
        }
        guess = trim(toUpperCase(guess));
        if(boggle.findWord(guess)){
            boggle.increasePlayerScore(guess.length());
            boggle.addWordToPlayer(guess);
            printPlayerWords(boggle);
            cout << "You found a new word! " << guess << endl;
        }
        else{
            printPlayerWords(boggle);
            cout << "Invalid Guess " << endl;
        }
    }
}

void playOneGame(Boggle& boggle){
    string boardConfig;
    const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVXYZ";
    bool validConfig = false;
    boggle.clearAllWords();
    boggle.clearAllScores();
    if(!yesOrNo("Would you like a randomized board? (Y/N)? ")){
        cout << endl;
        while(!validConfig){
             cout << "Please enter a valid board configuration:" << endl;
            int counter = 0;
            getline(cin,boardConfig);
            cout << endl;
            if(boardConfig.size() == 16){
                for(int i = 0; i < 16; i++){
                    for(int a = 0; a < ALPHABET.size(); a++){
                        if(trim(toUpperCase(string(1, boardConfig[i]))) == string(1,ALPHABET[a])){
                            counter++;
                        }
                    }
                }
            }
            if(counter == 16){
                validConfig = true;
            }
        }
        boggle.loadCustomBoard(boardConfig);
    }
    else{
        boggle.Randomizer();
    }
    printBoard(boggle);
    getPlayerGuesses(boggle);
    boggle.findAllWords();
    printComputerWords(boggle);
    int playerScore = boggle.getPlayerScore();
    int computerScore = boggle.getComputerScore();
    cout << endl;
    if(playerScore > computerScore){
        cout << "You won! ";
    }
    else if(playerScore == computerScore){
        cout << "It's a draw! ";
    }
    else{
        cout << "Ha ha ha, I destroyed you. Better luck next time, puny human. ";
    }
    cout << "Your Score: " << playerScore << ". My Score: " << computerScore << endl;
}




/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}

