#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <cstdlib>
#include <ctime>

class Level{
    private:
        char*** myLevel;
        int lvlNum;
        int gridSize;
        int initialLives;
        int percCoins;
        int percNot;
        int percGmb;
        int percKoop;
        int percMsh;
    public:
        Level();
        Level(int l,int n, int v, int c, int x, int g, int k, int m);
        ~Level();
        void Map(int maxLevels);
        int NumSpacesOf(int inp);
        char spawnMario(std::ostream* output);
        char placeMario(int row, int col);
        void clearTile(int row, int col);
        void printLevel(std::ostream* output);
        std::string getMarioPos();
        char getPosInfo(int row, int col);
        int getGridSize();
};

#endif