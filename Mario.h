#ifndef MARIO_H
#define MARIO_H

#include "Level.h"

class Mario{
    private:
        int currLives;
        int powerLevel;
        int wallet;
        int enemiesDefeated;
        int gridSize;
    public:
        Mario();
        Mario(int l, int p, int c, int e, int n);
        ~Mario();
        int getLivesRemaining();
        int getWallet();
        int getPowerLevel();
        int getEnemiesDefeated();
        int getRow(Level *currLevel);
        int getCol(Level *currLevel);
        char MarioMove(Level *currLevel, int row, int col);
        char moveUp(Level *currLevel, int row, int col);
        char moveDown(Level *currLevel, int row, int col);
        char moveLeft(Level *currLevel, int row, int col);
        char moveRight(Level *currLevel, int row, int col);
        int engageEnemy(char b);
        void grabCoin();
        void grabMushroom();
        
};

#endif