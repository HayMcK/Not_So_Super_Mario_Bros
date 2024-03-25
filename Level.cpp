#include "Level.h"

//default constructor
Level::Level(){
    lvlNum = 0;
    gridSize = 1;
    initialLives = 0;
    percCoins = 0;
    percNot = 100;
    percGmb = 0;
    percKoop = 0;
    percMsh = 0;
}

//overloaded constructor
Level::Level(int l, int n, int v, int c, int x, int g, int k, int m){
    lvlNum = l;
    gridSize = n;
    initialLives = v;
    percCoins = c;
    percNot = x;
    percGmb = g;
    percKoop = k;
    percMsh = m;
}

//destrucor
Level::~Level(){
    for (int i = 0; i < lvlNum; i++){
        for (int j = 0; j < gridSize; j++)
            delete[] myLevel[i][j];
        delete[] myLevel[i];
    }
    delete[] myLevel;
}

//function to return the total number of spaces for a given input
int Level::NumSpacesOf(int inp){
    int totalSpaces = (gridSize * gridSize)-2;
    return ((inp * totalSpaces)/100);
}

//function to create the map of each level
void Level::Map(int maxLevels){
    myLevel = new char **[lvlNum];
    bool placed = false;
    for (int i = 0; i < lvlNum; i++) {
        myLevel[i] = new char*[gridSize];
        for (int j = 0; j < gridSize; j++)
            myLevel[i][j] = new char[gridSize];
    }
    
    for(int i = 0; i < gridSize; ++i){
        for ( int j = 0; j < gridSize; ++j)
            myLevel[lvlNum-1][i][j] = ' ';   
    }

    while(!placed){
        int row = rand() % gridSize;
        int col = rand() % gridSize;
        if(lvlNum == maxLevels){
            placed = true;
        }
        else if(myLevel[lvlNum-1][row][col] == ' '){
            myLevel[lvlNum-1][row][col] = 'w';
            placed = true;
        }
        else   
            placed = false;
    }
    placed = false;
    
    while(!placed){
        int row = rand() % gridSize;
        int col = rand() % gridSize;
        if(myLevel[lvlNum-1][row][col] == ' '){
            myLevel[lvlNum-1][row][col] = 'b';
            placed = true;
        }
        else   
            placed = false;
    }
    placed = false;

    int numCoins = NumSpacesOf(percCoins);
    int numNot = NumSpacesOf(percNot);
    int numGmb = NumSpacesOf(percGmb);
    int numKoop = NumSpacesOf(percKoop);
    int numMsh = NumSpacesOf(percMsh);

    for (int i = 0; i < numCoins; i++) {
        while(!placed){
            int row = rand() % gridSize;
            int col = rand() % gridSize;
            if(myLevel[lvlNum-1][row][col] == ' '){
                myLevel[lvlNum-1][row][col] = 'c';
                placed = true;
            }
            else
                placed = false;
        }  
        placed = false;
    }
    for (int i = 0; i < numGmb; i++) {
        while(!placed){
            int row = rand() % gridSize;
            int col = rand() % gridSize;
            if(myLevel[lvlNum-1][row][col] == ' '){
                myLevel[lvlNum-1][row][col] = 'g';
                placed = true;
            }
            else
                placed = false;
        }  
        placed = false;
    }
    for (int i = 0; i < numKoop; i++) {
        while(!placed){
            int row = rand() % gridSize;
            int col = rand() % gridSize;
            if(myLevel[lvlNum-1][row][col] == ' '){
                myLevel[lvlNum-1][row][col] = 'k';
                placed = true;
            }
            else
                placed = false;
        }  
        placed = false;
    }
    for (int i = 0; i < numMsh; i++) {
        while(!placed){
            int row = rand() % gridSize;
            int col = rand() % gridSize;
            if(myLevel[lvlNum-1][row][col] == ' '){
                myLevel[lvlNum-1][row][col] = 'm';
                placed = true;
            }
            else
                placed = false;
        }  
        placed = false;  
    }
    for(int i = 0; i < gridSize; i++){
        for( int j = 0; j < gridSize; ++j){
            if(myLevel[lvlNum-1][i][j] == ' ')
                myLevel[lvlNum-1][i][j] = 'x';
        }
    }
}

//function to initially spawn mario
char Level::spawnMario(std::ostream* output){
    char original = '\0';
    int row = rand() % gridSize;
    int col = rand() % gridSize;
    original = myLevel[lvlNum-1][row][col];
    myLevel[lvlNum-1][row][col] = 'H';
    *output << "Mario is starting in position (" << row << ", " << col << ")" << std::endl;
    *output << "\n===============\n" << std::endl; 
    printLevel(output);
    return original;
}

//function to place mario 
char Level::placeMario(int row, int col){
    char original = myLevel[lvlNum-1][row][col];
    myLevel[lvlNum-1][row][col] = 'H';
    return original;
}

//function to make a tile an empty space
void Level::clearTile(int row, int col){
    myLevel[lvlNum-1][row][col] = 'x';
}

//function to print a level grid
void Level::printLevel(std::ostream* output){
    for(int i = 0; i < gridSize; i++){
        for( int j = 0; j < gridSize; ++j)
            *output << myLevel[lvlNum-1][i][j];
        *output << "\n";
    }
    *output << "\n";
}

//function that returns what object the tile is
char Level::getPosInfo(int row, int col){
    return myLevel[lvlNum-1][row][col];
}

//function to find the position on the map mario is
std::string Level::getMarioPos(){
    std::string myPos = "";
    for(int i = 0; i < gridSize; i++){
        for( int j = 0; j < gridSize; ++j){
            if (getPosInfo(i, j) == 'H'){
                myPos = "(" + std::to_string(i) + ", " + std::to_string(j) + ")";
            }
        }
    }
    return myPos;
}

//return size of the grid
int Level::getGridSize(){
    return gridSize;
}