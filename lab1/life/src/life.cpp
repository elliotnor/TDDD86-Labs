//This program animates the Conway game of life

#include <iostream>
#include "grid.h"
#include "lifeutil.h"
#include <string>
#include <fstream>

using namespace std;

Grid<string> createGrid();
void welcomeScreen();
void print(const Grid<string>& grid);
void checkGrid(Grid<string>& grid);
int checkNeighbors(const int& y, const int& x, const Grid<string>& grid);

/*The main function and main loop
 * Constitutes the order of the program
*/
int main() {
    bool running = true;

    string action;

    welcomeScreen();

    Grid<string> grid = createGrid();

    while(running){
        print(grid);
        cout << "a)nimate  t)ick  q)uit? ";
        cin >> action;
        if(action == "a"){
            while(running){
                pause(100);
                clearConsole();
                checkGrid(grid);
                print(grid);
            }
        }
        else if(action == "t"){
            checkGrid(grid);
        }
        else if(action == "q"){
            running = false;
        }
    }
    cout << "Have a nice Life! " << endl;
    return 0;
}

// Generates and returns a new grid
Grid<string> createGrid(){

    string filename;
    int row;
    int column;
    ifstream input;
    string line;

    cout << endl;
    cout << "Grid input filename? ";
    cin >> filename;

    input.open(filename.c_str());

    for(int i = 0; i < 2; i++){
        if(i == 0){
            getline(input, line);
            row = stoi(line);
        }
        else{
            getline(input, line);
            column = stoi(line);
        }
    }
    Grid<string> grid = Grid<string>(row, column);

    for(int y = 0; y < row; y++){
        getline(input, line);
        for(int x = 0; x < column; x++){
            grid[y][x] = line[x];
        }
    }
    return grid;
}

//Prints the welcoming screen
void welcomeScreen(){

    cout << "Welcome to the TDDD86 Game of Life, " << endl
         << "a simulation of the lifecycle of a bacteria colony." << endl
         << "Cells (X) live and die by the following rules:" << endl
         << "- A cell with 1 or fewer neighbours dies." << endl
         << "- Locations with 2 neighbours remain stable." << endl
         << "- Locations with 3 neighbours will create life." << endl
         << "- A cell with 4 or more neighbours dies." << endl;
}

//Prints the selected grid in the terminal
void print(const Grid<string>& grid){
    int row = grid.nRows;
    int column = grid.nCols;

    for(int y = 0; y < row; y++){
        for(int x = 0; x < column; x++){
            cout << grid.get(y,x);
        }
        cout << endl;
    }
}

/*Decides what the next generation
 * of the grid looks like. By going
 * through all the valid cells in the grid.
*/
void checkGrid(Grid<string>& grid){
    Grid<string> tempGrid = grid;

    int counter = 0;
    int row = grid.nRows;
    int column = grid.nCols;

    for(int y = 0; y < row; y++){
        for(int x = 0; x < column; x++){
           counter = checkNeighbors(y, x, grid);
           if(counter == 0 || counter == 1 || counter >= 4){
               tempGrid[y][x] = "-";
           }
           else if(counter == 3){
               tempGrid[y][x] = "X";
           }
       }
   }
    grid = tempGrid;
}

/*Checks the surrounding neighboring cells of a specific cell.
 * Returns the amount of neighbors for one cell
*/
int checkNeighbors(const int& y, const int& x, const Grid<string>& grid){
    int counter = 0;
    for(int y2 = y - 1; y2 < y + 2; y2++){
       for(int x2 = x - 1; x2 < x + 2; x2++){
          if(grid.inBounds(y2, x2)){
            if(grid[y2][x2] == "X" && !(y2 == y && x2 == x)){
               counter++;
            }
          }
       }
    }
    return counter;
}




