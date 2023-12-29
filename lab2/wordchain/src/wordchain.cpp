#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_set>


using namespace std;
const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void welcomeScreen();
unordered_set<string> loadDictionary();
stack<string> wordChain(const string& w1,const string& w2, const unordered_set<string>& dictionary);
unordered_set<string> getNeighbors(const string& w1, const unordered_set<string>& dictionary);
void printResult(const stack<string>& s);

//The main function
int main() {
    string w1;
    string w2;
    welcomeScreen();
    unordered_set<string> dictionary = loadDictionary(); //Load the dictionary

    cout << "Please type two words: ";
    cin >> w1 >> w2;
    cout << endl;

    printResult(wordChain(w1, w2, dictionary));
    return 0;
}

//Prints the welcome screen
void welcomeScreen(){
    cout << "Welcome to TDDD86 Word Chain." << endl
         << "If you give me two English words, I will transform the" << endl
         << "first into the second by changing one letter at a time." << endl
         << endl;
}

//Load the dictionary containing all the words
unordered_set<string> loadDictionary(){
    unordered_set<string> dictionary;
    ifstream input;
    string line;
    input.open("dictionary.txt");
    while(getline(input, line)){
        dictionary.insert(dictionary.end(), line);
    }
    return dictionary;
}



stack<string> wordChain(const string& w1,const string& w2, const unordered_set<string>& dictionary){
    unordered_set<string> neighbors = getNeighbors(w1, dictionary);
    set<string> usedNeighbors;
    queue<stack<string>> queue;
    stack<string> s;
    stack<string> sTemp;

    s.push(w1);
    queue.push(s);
    while(!queue.empty()){
        s = queue.front();
        queue.pop();
        if(s.top() == w2){
            return s;
        }
        else{
            neighbors = getNeighbors(s.top(), dictionary);
            for(string n: neighbors){
                if(!usedNeighbors.count(n)){
                  usedNeighbors.insert(usedNeighbors.end(), n);
                  sTemp = s;
                  sTemp.push(n);
                  queue.push(sTemp);
                }
           }
        }
    }
    return s;
}

//This fucntion finds neighboring words
unordered_set<string> getNeighbors(const string& w1, const unordered_set<string>& dictionary){
    unordered_set<string> neighbors;
    for(int i = 0; i < w1.size(); i++){
        string wTemp = w1;
        for(int j = 0; j < ALPHABET.size(); j++){
            wTemp[i] = ALPHABET[j];
            if(wTemp != w1){
                if(dictionary.count(wTemp)){
                    if(!neighbors.count(wTemp)){
                       neighbors.insert(neighbors.end(), wTemp);
                    }
                }
            }
        }
    }
    return neighbors;
}

//Prints the resulting chain of words
void printResult(const stack<string>& s){
    stack<string> sTemp = s;
    while (!sTemp.empty()){
        cout << sTemp.top() << " ";
        sTemp.pop();
    }
    cout << endl;
}
