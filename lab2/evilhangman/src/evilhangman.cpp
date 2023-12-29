#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

vector<string> loadDictionary();
vector<string> correctSizes(const vector<string>& dictionary, const int& length);
int getLength();
int getGuessAmmount();
string getGuess(const unordered_set<string>& guessedLetters);
void showAnswers(const unordered_map<string, vector<string>>& map);
void controlAnswers(const int& length, const string& guess, unordered_map<string, vector<string>>& map, const int& numberOfGuesses);


/*The main function
 * Handles the flow of one round and
 * if the game is running or not*/
int main() {
    cout << "Welcome to Hangman." << endl;
   bool roundRunning = true;
   bool gameRunning = true;
   unordered_set<string> guessedLetters;
   string choice;
   string guess;
   string start;
   string restart;
   unordered_map<string, vector<string>> combos;
   vector<string> dictionary;
   int length;
   int numberOfGuesses;

   while(gameRunning){ //Is the game running?
       roundRunning = true;
       gameRunning = false;
       guessedLetters.clear();
       dictionary = loadDictionary();
       length = getLength();
       numberOfGuesses = getGuessAmmount();
       combos.clear();

       for(int i = 0; i < length; i++){
           start += "-";
       }

       combos[start] = correctSizes(dictionary, length);

       while(roundRunning){
           cout << "Would you like to see the ammount of matching words remaining? ";
           cin >> choice;
           if(choice == "yes"){
               showAnswers(combos);
           }

           guess = getGuess(guessedLetters);
           guessedLetters.insert(guess);
           controlAnswers(length, guess, combos, numberOfGuesses);

           for(auto it = combos.begin(); it != combos.end(); it++){
               cout << it->first << endl;
                if(it->first == start){
                    start = it->first;

                    numberOfGuesses--;
                }
                else{
                    start = it->first;
                }
                if(numberOfGuesses == 0){
                    cout << "You suck! The word was: " << it->second.at(0) << endl;
                    cout << "Would you like to play again? " <<endl;
                    cin >> restart;
                    roundRunning = false;
                    if(restart == "yes"){
                        gameRunning = true;
                    }
                }
                else if(it->second.size() == 1 && it->first == it->second.at(0)){
                    cout << "Congratulations! You Win! The word was: " << it->second.at(0) << endl;
                    cout << endl;
                    cout << "Would you like to play again? " <<endl;
                    cin >> restart;
                    roundRunning = false;
                    if(restart == "yes"){
                        gameRunning = true;
                    }
                }
                else{
                    cout << "Guesses left: " << numberOfGuesses << endl;
                    cout << "Guessed letters: ";
                    for(int i = 0; i < ALPHABET.size(); i++){
                        if(guessedLetters.count(string(1,ALPHABET.at(i)))){
                            cout << ALPHABET.at(i);
                        }
                    }
                    cout << endl;
                }
           }
       }
    }

        return 0;
}

//Loads the .txt file containing all the words
vector<string> loadDictionary(){
    ifstream input;
    string line;
    vector<string> dictionary;

    input.open("di.txt");
    while(getline(input, line)){
         dictionary.insert(dictionary.end(), line);
    }
    return dictionary;
}

//Filters the dictionary to only contain the specified length of words
vector<string> correctSizes(const vector<string>& dictionary, const int& length){
    vector<string> validWords;
    for(int i = 0; i < dictionary.size(); i++){
        if(dictionary.at(i).size() == length){
            validWords.insert(validWords.end(), dictionary.at(i));
        }
    }
    return validWords;
}

/*Handles the input of how many
 * guesses the user wants*/
int getGuessAmmount(){
    int numberOfGuesses = 0;
    while(numberOfGuesses <= 0){
     cout << endl << "Enter the ammount of guesses you want: ";
     cin >> numberOfGuesses;
    }
    return numberOfGuesses;
}

//Handles the unput of word length
int getLength(){
    int length = 0;
    while(length <= 0 || length > 29){ //Has to be a word longer than 0
    cout << "Enter the length of the word: ";
    cin >> length;
    }
    return length;
}

/*This function asks the user to guess a letter
 *If the letter has been guessed before, it asks for another letter*/
string getGuess(const unordered_set<string>& guessedLetters){
    string guess = "";
    bool validGuess = false;

    cout << endl << "Guess a letter: ";

    while(!validGuess){
        cin >> guess;
        cout << endl;
        if(!guessedLetters.count(guess)){
            for(int i = 0; i < ALPHABET.size(); i++){
                if(guess == string(1,ALPHABET.at(i))){
                    validGuess = true;
                }
            }
        }
        else{//The letter has been guessed before
            cout << "Guess another letter: ";
        }
    }
    return guess;
}

//Prints the remaining amount of possible words
void showAnswers(const unordered_map<string, vector<string>>& map){
    for(auto it = map.begin(); it != map.end(); it++){
        cout << it->second.size() << endl;
    }
}

/*This function contains the "brain" of the program. It makes
 *sure the user always loses by always selecting the largest
 *family of words not containing the previous user guesses*/
void controlAnswers(const int& length, const string& guess, unordered_map<string, vector<string>>& map, const int& numberOfGuesses){
    unordered_map<string, vector<string>> tempMap;
    string key = "";
    vector<string> words;
    vector<string> tempWords;
    string word;
    int counter = 0;
    int keyCounter = 0;
    int max = 0;
    string maxKey;

    for(auto it = map.begin(); it != map.end(); it++){
        words = it->second;
        for(int x = 0; x < words.size(); x++){
            string word = words.at(x);
            for(int i = 0; i < length; i++){
                if(string(1, word.at(i)) == guess){//If the letter == the guess we'll add it to the key
                    key += guess;
                }
                else if(it->first.at(i) == word.at(i)){
                    key += it->first.at(i);
                }
                else{
                    key += "-";
                }
            }
            tempWords.insert(tempWords.end(), word);

            if(tempMap[key].size() == 0){//If there's no word with the correct key, create it
                tempMap[key] = tempWords;
            }
            else{
                tempMap[key].insert(tempMap[key].end(), word); //There's a key, add the word to the end of the vector
            }
            key = "";
            tempWords.clear();
        }
    }
    for(auto it = tempMap.begin(); it != tempMap.end(); it++){ //Find the longest vector
        counter++;
        if(it->second.size() >= max){
            max = it->second.size();
            maxKey = it->first;
        }
    }
    if(max == 1 && counter == 2){
        for(auto it = tempMap.begin(); it != tempMap.end(); it++){
            for(int i = 0; i < length; i++){
                if(guess == string(1, maxKey.at(i)) &&  it->first != maxKey){
                    maxKey = it->first;
                }
            }
        }
    }
    else if(counter == 2 &&  numberOfGuesses == 1){
        for(auto it = tempMap.begin(); it != tempMap.end(); it++){
            for(int i = 0; i < length; i++){
                if(guess == string(1, it->first.at(i)) &&  it->first != maxKey){
                    keyCounter++;
                }
            }
            if(keyCounter == 0){
               maxKey = it->first;
            }
        }
    }
    map.clear(); //Empty the map and add the largest vector with the correct key
    map[maxKey] = tempMap[maxKey];
}




