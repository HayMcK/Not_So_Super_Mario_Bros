#include "Mario.h"

//default constructor
Mario::Mario(){
    currLives = 1;
    powerLevel = 0;
    wallet = 0;
    enemiesDefeated = 0;
    gridSize = 0;
}

//overloaded constructor
Mario::Mario(int l, int p, int c, int e, int n){
    currLives = l;
    powerLevel = p;
    wallet = c;
    enemiesDefeated = e;
    gridSize = n;
}

//destructor
Mario::~Mario(){}

//return lives remaining
int Mario::getLivesRemaining(){
    return currLives;
}

//return coins in wallet
int Mario::getWallet(){
    return wallet;
}

//return current power level
int Mario::getPowerLevel(){
    return powerLevel;
}

//return # of enemies defeated
int Mario::getEnemiesDefeated(){
    return enemiesDefeated;
}

//retrun row of mario
int Mario::getRow(Level *currLevel){
    for(int i = 0; i < gridSize; i++){
        for( int j = 0; j < gridSize; ++j){
            if (currLevel->getPosInfo(i, j) == 'H'){
                return i;
            }
        }
    }
    return -1;
}

//return col of mario
int Mario::getCol(Level *currLevel){
    for(int i = 0; i <gridSize; i++){
        for( int j = 0; j < gridSize; ++j){
            if (currLevel->getPosInfo(i, j) == 'H'){
                return j;
            }
        }
    }
    return -1;
}

//randomly select a number between 1 and 4 and move mario in that designated direction
char Mario::MarioMove(Level *currLevel, int row, int col){
    int randNum = (rand() % 4) + 1;
    switch(randNum){
        case 1: return moveUp(currLevel, row, col); break;
        case 2: return moveDown(currLevel, row, col); break;
        case 3: return moveLeft(currLevel, row, col); break;
        case 4: return moveRight(currLevel, row, col); break;
        default: return '\0';
    }
}

//moves mario down
char Mario::moveDown(Level *currLevel, int row, int col){
    if(row == gridSize-1){
        int row = 0;
        char temp = currLevel->getPosInfo(row, col);
        currLevel->placeMario(row, col);
        return temp;
    }
    else{
        row ++;
        char temp = currLevel->getPosInfo(row, col);
        currLevel->placeMario(row, col);
        return temp;
    }
}

//moves mario up
char Mario::moveUp(Level *currLevel, int row, int col){
    if(row == 0){
        row = gridSize-1;
        char temp = currLevel->getPosInfo(row, col);
        currLevel->placeMario(row, col);
        return temp;
    }
    else{
        row--;
        char temp = currLevel->getPosInfo(row, col);
        currLevel->placeMario(row, col);
        return temp;
    }
}

//moves mario left
char Mario::moveLeft(Level *currLevel, int row, int col){
    if(col == 0){
        col = gridSize-1;
        char temp = currLevel->getPosInfo(row, col);
        currLevel->placeMario(row, col);
        return temp;
    }
    else{
        col--;
        char temp = currLevel->getPosInfo(row, col);
        currLevel->placeMario(row, col);
        return temp;
    }
}

//moves mario right
char Mario::moveRight(Level *currLevel, int row, int col){
    if(col == gridSize-1){
        col = 0;
        char temp = currLevel->getPosInfo(row, col);
        currLevel->placeMario(row, col);
        return temp;
    }
    else{
        col++;
        char temp = currLevel->getPosInfo(row, col);
        currLevel->placeMario(row, col);
        return temp;
    }
}

//engage in fighting an enemy in accordance to their rule set
int Mario::engageEnemy(char enemy){
    if(enemy == 'b'){
        int winChance = (rand() % 100) + 1;
        if(winChance > 50){//loses
            if(powerLevel <= 1)
                if(currLives == 0){//loses, power level isn't 2, lives left is 0, so game over
                    return 4;
                }
                else{//loses and power level is 0 or 1, so loses life
                    enemiesDefeated = 0;
                    powerLevel = 0;
                    currLives--;
                    return 3;
                }
            else{//loses and powerlevel was 2
                powerLevel = 0;
                return 2; 
            }
        }
        else{//wins
            enemiesDefeated++;
            if(enemiesDefeated == 7){
                currLives++;
                enemiesDefeated = 0;
            }
            return 1; 
        }
    }
    else if(enemy == 'k'){
        int winChance = (rand() % 100) + 1;
        if(winChance > 65){//loses
            if(powerLevel == 0){
                if(currLives == 0){//loses, power level is 0, lives left is 0, so game over
                    return 4;
                }
                else{//loses and power level is 0, so loses life
                    enemiesDefeated = 0;
                    currLives--;
                    powerLevel = 0;
                    return 3;
                }
            }
            else{//loses and powerlevel was above 0
                powerLevel--;
                return 2; 
            }
        }
        else{//wins
            enemiesDefeated++;
            if(enemiesDefeated == 7){
                currLives++;
                enemiesDefeated = 0;
            }
            return 1;
        }

    }
    else if(enemy == 'g'){
        int winChance = (rand() % 100) + 1;
        if(winChance > 80){//loses
            if(powerLevel == 0){
                if(currLives == 0){//loses, power level is 0, lives left is 0, so game over
                    return 4;
                }
                else{//loses and power level is 0, so loses life
                    currLives--;
                    enemiesDefeated = 0;
                    powerLevel = 0;
                    return 3;
                }
            }
            else{//loses and powerlevel was above 0
                powerLevel--;
                return 2; 
            }
        }
        else{//wins
            enemiesDefeated++;
            if(enemiesDefeated == 7){
                currLives++;
                enemiesDefeated = 0;
            }
            return 1;
        }
    }
    else return -1;
}

//mario interacts with a coin adding it to his wallet
void Mario::grabCoin(){
    if(wallet == 19){
        currLives++;
        wallet = 0;
    }
    else
        wallet++;
}

//mario grabs a mushroom, updating his powerlevel unless it is already 2
void Mario::grabMushroom(){
    if (powerLevel != 2)
        powerLevel++;
}

