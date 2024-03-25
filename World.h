#ifndef WORLD_H
#define WORLD_H

#include "Mario.h"
#include <fstream>
class World{
    private:
        //Level **myLevel;
        Mario *myHero;
        int numLevels;
        int gridSize;
        int livesRemaining;
        int percCoins;
        int percNot;
        int percGmb;
        int percKoop;
        int percMsh;
        int wallet;
        int powerLevel;
    public:
        World();
        World(int l, int n, int v, int c, int x, int g, int k, int m);
        ~World();
        void Play(std::string outFile);
};


#endif