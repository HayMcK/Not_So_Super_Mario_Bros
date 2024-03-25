#include "World.h"

//default constructor
World::World(){
    numLevels = 0;
    gridSize = 1;
    livesRemaining = 0;
    percCoins = 0;
    percNot = 100;
    percGmb = 0;
    percKoop = 0;
    percMsh = 0;
    wallet = 0;
    powerLevel = 0;
    myHero = nullptr;
}

//overloaded constructor
World::World(int l, int n, int v, int c, int x, int g, int k, int m){
    numLevels = l;
    gridSize = n;
    livesRemaining = v;
    percCoins = c;
    percNot = x;
    percGmb = g;
    percKoop = k;
    percMsh = m;
    wallet = 0;
    powerLevel = 0;
    myHero = new Mario(livesRemaining, 0, 0, 0, gridSize);
}

//destructor
World::~World(){}

//Function to play the game and write the results to the output file
void World::Play(std::string outFile){
    srand(time(0));
    std::ofstream output(outFile);
    int count = 0;
    bool gameIsOver = false;
    char spawnTile = '\0';
    int currRow;
    int currCol;
    while(!gameIsOver){
        for(int i = 0; i < numLevels && !gameIsOver; i++){
            output << "\n===============" << std::endl;
            output << "LEVEL " << i << std::endl;
            output << "\n";
            bool levelComplete = false;
            bool marioPlaced = false;
            Level* currLevel = new Level(i+1, gridSize, livesRemaining, percCoins, percNot, percGmb, percKoop, percMsh);
            currLevel->Map(numLevels);
            currLevel->printLevel(&output);
            output << "\n";
            spawnTile = currLevel->spawnMario(&output);
            currRow = myHero->getRow(currLevel);
            currCol = myHero->getCol(currLevel);
            count++;
            switch(spawnTile){
                case 'c':{
                    myHero->grabCoin();
                    output << "Level: " << i << ". Mario is at position " << currLevel->getMarioPos()
                    << ". Mario picked up a coin. Mario is at power level " << myHero->getPowerLevel() << ". Mario has " 
                    << myHero->getLivesRemaining() << " lives left. Mario has " << myHero->getWallet() 
                    << " coins. Mario is moving on." << std::endl;
                    currLevel->clearTile(myHero->getRow(currLevel), myHero->getCol(currLevel));
                    break;
                }
                case 'm':{
                    myHero->grabMushroom();
                    output << "Level: " << i << ". Mario is at position " << currLevel->getMarioPos()
                    << ". Mario found a mushroom. Mario is at power level " << myHero->getPowerLevel() << ". Mario has "
                    << myHero->getLivesRemaining() << " lives left. Mario has " << myHero->getWallet() 
                    << " coins. Mario is moving on." << std::endl;
                    currLevel->clearTile(myHero->getRow(currLevel), myHero->getCol(currLevel));
                    break;
                }
                case 'g':{
                    bool enemyBeaten = false;
                    output << "Level: " << i << ". Mario is at position " << currLevel->getMarioPos()
                    << ". Mario encountered a goomba";
                    while(!enemyBeaten && !gameIsOver){
                        int result = myHero->engageEnemy('g');
                        switch(result){
                            case 1:{//wins
                                output << " and won. Mario is at power level " << myHero->getPowerLevel() 
                                << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has "
                                << myHero->getWallet() << " coins. Mario will move on." << std::endl;
                                enemyBeaten = true;
                                currLevel->clearTile(myHero->getRow(currLevel), myHero->getCol(currLevel));
                                break;
                            }
                            case 2:{//loses but powerlevel above 0
                                output << " and lost, lowering his powerlevel. Mario is at power level " << myHero->getPowerLevel()
                                << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has "
                                << myHero->getWallet() << " coins. Mario will attempt to fight the goomba again.";
                                output << "\n";
                                output << "\n===============\n" << std::endl;
                                currLevel->printLevel(&output);
                                output << "\nMario fought the goomba again";
                                break;
                            }
                            case 3:{//loses but powerlevel is 0
                                output << " and lost while at power level 0, so he lost a life. Mario is at power level " 
                                << myHero->getPowerLevel() << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has " 
                                << myHero->getWallet() << " coins. Mario will attempt to fight the goomba again.";
                                output << "\n";
                                output << "\n===============\n" << std::endl;
                                currLevel->printLevel(&output);
                                output << "\nMario fought goomba again";
                                break;
                            }
                            case 4:{//loses, powerlevel 0, lives left is 0, game over
                                gameIsOver = true;
                                output << " and lost while at power level 0 with no lives left."
                                << "The game is over and Mario LOST. It took " << count << " moves." << std::endl;
                                break;
                            }
                            default:{
                                std::cout << "invalid fight outcome" << std::endl;
                                break;
                            }
                        }
                    }
                    break;
                }
                case 'k':{
                    bool enemyBeaten = false;
                    output << "Level: " << i << ". Mario is at position " << currLevel->getMarioPos()
                    << ". Mario encountered a koopa";
                    while(!enemyBeaten && !gameIsOver){
                        int result = myHero->engageEnemy('k');
                        switch(result){
                            case 1:{//wins
                                output << " and won. Mario is at power level " << myHero->getPowerLevel() 
                                << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has "
                                << myHero->getWallet() << " coins. Mario will move on." << std::endl;
                                enemyBeaten = true;
                                currLevel->clearTile(myHero->getRow(currLevel), myHero->getCol(currLevel));
                                break;
                            }
                            case 2:{//loses but powerlevel above 0
                                output << " and lost, lowering his powerlevel. Mario is at power level " << myHero->getPowerLevel()
                                << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has "
                                << myHero->getWallet() << " coins. Mario will attempt to fight the koopa again.";
                                output << "\n";
                                output << "\n===============\n" << std::endl;
                                currLevel->printLevel(&output);
                                output << "\nMario fought the koopa again";
                                break;
                            }
                            case 3:{//loses but powerlevel is 0
                                output << " and lost while at power level 0, so he lost a life. Mario is at power level " 
                                << myHero->getPowerLevel() << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has " 
                                << myHero->getWallet() << " coins. Mario will attempt to fight the koopa again.";
                                output << "\n";
                                output << "\n===============\n" << std::endl;
                                currLevel->printLevel(&output);
                                output << "\nMario fought the koopa again";
                                break;
                            }
                            case 4:{//loses, powerlevel 0, lives left is 0, game over
                                gameIsOver = true;
                                output << " and lost while at power level 0 with no lives left."
                                << "The game is over and Mario LOST. It took " << count << "moves." << std::endl;
                                break;
                            }
                            default:{
                                std::cout << "invalid fight outcome" << std::endl;
                                break;
                            }
                        }
                    }
                    break;
                }
                case 'b':{
                    bool bossBeaten = false;
                    int tempPL = myHero->getPowerLevel();
                    output << "Level: " << i << ". Mario is at position " << currLevel->getMarioPos()
                    << ". Mario encountered the boss";
                    while(!bossBeaten && !gameIsOver){
                        if(i == numLevels){
                            int result = myHero->engageEnemy('b');
                            switch(result){
                                case 1:{//wins
                                    output << " and WON, saving the princess! Mario finished the game in " << count << " moves." << std::endl;
                                    gameIsOver = true;
                                    levelComplete = true;
                                    bossBeaten = true;
                                    break;
                                }
                                case 2:{ //loses but powerlevel is 2
                                    output << " and lost, lowering his power level. Mario is at power level " << myHero->getPowerLevel()
                                    << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has " 
                                    << myHero->getWallet() << " coins. Mario will attempt to fight the boss again.";
                                    output << "\n";
                                    output << "\n===============\n" << std::endl;
                                    currLevel->printLevel(&output);
                                    output << "\nMario fought the boss again" << std::endl;
                                    tempPL = 0;
                                    break;
                                }
                                case 3:{ //loses, powerlevel is 0 or 1, loses a life
                                    output << " and lost while at power level " << tempPL << " so he lost a life. Mario is at power level " 
                                    << myHero->getPowerLevel() << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has " 
                                    << myHero->getWallet() << " coins. Mario will attempt to fight the boss again.";
                                    output << "\n";
                                    output << "\n===============\n" << std::endl;
                                    currLevel->printLevel(&output);
                                    output << "\nMario fought the boss again" << std::endl;
                                    tempPL = 0;
                                    break;
                                }
                                case 4:{ //loses, powerlevel is 0 or 1, lives left is 0, game over
                                    gameIsOver = true;
                                    output << " and lost while at power level " << tempPL << " with no lives left."
                                    << "The game is over and Mario LOST. It took " << count << " moves." << std::endl;
                                    break;
                                }
                                default:{
                                    std::cout << "invalid fight outcome" << std::endl;
                                    break;
                                }
                            }
                        }
                        else{
                            int result = myHero->engageEnemy('b');
                            switch(result){
                                case 1:{//wins
                                    output << " and WON. Mario is at power level " << myHero->getPowerLevel()
                                    << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has "
                                    << myHero->getWallet() << " coins. Mario will move to the next level." << std::endl;
                                    bossBeaten = true;
                                    levelComplete = true;
                                    break;
                                }
                                case 2:{ //loses but powerlevel is 2
                                    output << " and lost, lowering his power level. Mario is at power level " << myHero->getPowerLevel()
                                    << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has " 
                                    << myHero->getWallet() << " coins. Mario will attempt to fight the boss again.";
                                    output << "\n";
                                    output << "\n===============\n" << std::endl;
                                    currLevel->printLevel(&output);
                                    output << "\nMario fought the boss again";
                                    tempPL = 0;
                                    break;
                                }
                                case 3:{ //loses, powerlevel is 0 or 1, loses a life
                                    output << " and lost while at power level " << tempPL << " so he lost a life. Mario is at power level " 
                                    << myHero->getPowerLevel() << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has " 
                                    << myHero->getWallet() << " coins. Mario will attempt to fight the boss again.";
                                    output << "\n";
                                    output << "\n===============\n" << std::endl;
                                    currLevel->printLevel(&output);
                                    output << "\nMario fought the boss again";
                                    tempPL = 0;
                                    break;
                                }
                                case 4:{ //loses, powerlevel is 0 or 1, lives left is 0, game over
                                    gameIsOver = true;
                                    output << " and lost while at power level " << tempPL << " with no lives left."
                                    << "The game is over and Mario LOST. It took " << count << " moves." << std::endl;
                                    break;
                                }
                                default:{
                                    std::cout << "invalid fight outcome" << std::endl;
                                    break;
                                }
                            }
                        }
                    }
                    break;
                }
                case 'w':{
                    output << "Level: " << i << ". Mario is at position " << currLevel->getMarioPos() 
                    << ". Mario found a warp pipe. Mario is at power level " << myHero->getPowerLevel() << ". Mario has " 
                    << myHero->getLivesRemaining() << " lives left. Mario has " << myHero->getWallet() 
                    << " coins. Mario will WARP to the next level." << std::endl;
                    levelComplete = true;
                    break;
                }
                default:{
                    output << "Level: " << i << ". Mario is at position " << currLevel->getMarioPos()
                    << ". Mario came to an empty tile. Mario is at power level " << myHero->getPowerLevel() << ". Mario has " 
                    << myHero->getLivesRemaining() << " lives left. Mario has " << myHero->getWallet() 
                    << " coins. Mario will move on." << std::endl;
                    currLevel->clearTile(myHero->getRow(currLevel), myHero->getCol(currLevel));
                    break;
                }
            }
            
            while(!levelComplete && !gameIsOver){
                output << "\n===============\n" << std::endl;
                char tile = myHero->MarioMove(currLevel, currRow, currCol);
                currRow = myHero->getRow(currLevel);
                currCol = myHero->getCol(currLevel);
                currLevel->printLevel(&output);
                switch(tile){
                    case 'c':{
                        myHero->grabCoin();
                        output << "Level: " << i << ". Mario is at position " << currLevel->getMarioPos()
                        << ". Mario picked up a coin. Mario is at power level " << myHero->getPowerLevel() << ". Mario has " << 
                        myHero->getLivesRemaining() << " lives left. Mario has " << myHero->getWallet() << " coins. Mario is moving on." << std::endl;
                        currLevel->clearTile(myHero->getRow(currLevel), myHero->getCol(currLevel));
                        count++;
                        break;
                    }
                    case 'm':{
                        myHero->grabMushroom();
                        output << "Level: " << i << ". Mario is at position " << currLevel->getMarioPos()
                        << ". Mario found a mushroom. Mario is at power level " << myHero->getPowerLevel() << ". Mario has " << 
                        myHero->getLivesRemaining() << " lives left. Mario has " << myHero->getWallet() << " coins. Mario is moving on." << std::endl;
                        currLevel->clearTile(myHero->getRow(currLevel), myHero->getCol(currLevel));
                        count++;
                        break;
                    }
                    case 'g':{
                        bool enemyBeaten = false;
                        output << "Level: " << i << ". Mario is at position " << currLevel->getMarioPos()
                        << ". Mario encountered a goomba";
                        while(!enemyBeaten && !gameIsOver){
                            int result = myHero->engageEnemy('g');
                            switch(result){
                                case 1:{//wins
                                    output << " and won. Mario is at power level " << myHero->getPowerLevel() 
                                    << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has "
                                    << myHero->getWallet() << " coins. Mario will move on." << std::endl;
                                    enemyBeaten = true;
                                    currLevel->clearTile(myHero->getRow(currLevel), myHero->getCol(currLevel));
                                    count++;
                                    break;
                                }
                                case 2:{//loses but powerlevel above 0
                                    output << " and lost, lowering his powerlevel. Mario is at power level " << myHero->getPowerLevel()
                                    << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has "
                                    << myHero->getWallet() << " coins. Mario will attempt to fight the goomba again.";
                                    output << "\n";
                                    output << "\n===============\n" << std::endl;
                                    currLevel->printLevel(&output);
                                    output << "\nMario fought the goomba again";
                                    count++;
                                    break;
                                }
                                case 3:{//loses but powerlevel is 0
                                    output << " and lost while at power level 0, so he lost a life. Mario is at power level " 
                                    << myHero->getPowerLevel() << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has " 
                                    << myHero->getWallet() << " coins. Mario will attempt to fight the goomba again.";
                                    output << "\n";
                                    output << "\n===============\n" << std::endl;
                                    currLevel->printLevel(&output);
                                    output << "\nMario fought goomba again";
                                    count++;
                                    break;
                                }
                                case 4:{//loses, powerlevel 0, lives left is 0, game over
                                    gameIsOver = true;
                                    count++;
                                    output << " and lost while at power level 0 with no lives left."
                                    << "The game is over and Mario LOST. It took " << count << " moves." << std::endl;
                                    break;
                                }
                                default:{
                                    std::cout << "invalid fight outcome" << std::endl;
                                    break;
                                }
                            }
                        }
                        break;
                    }
                    case 'k':{
                        bool enemyBeaten = false;
                        //int tempPL = myHero->getPowerLevel();
                        output << "Level: " << i << ". Mario is at position " << currLevel->getMarioPos()
                        << ". Mario encountered a koopa";
                        while(!enemyBeaten && !gameIsOver){
                            int result = myHero->engageEnemy('k');
                            switch(result){
                                case 1:{//wins
                                    output << " and won. Mario is at power level " << myHero->getPowerLevel() 
                                    << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has "
                                    << myHero->getWallet() << " coins. Mario will move on." << std::endl;
                                    enemyBeaten = true;
                                    currLevel->clearTile(myHero->getRow(currLevel), myHero->getCol(currLevel));
                                    count++;
                                    break;
                                }
                                case 2:{//loses but powerlevel above 0
                                    output << " and lost, lowering his powerlevel. Mario is at power level " << myHero->getPowerLevel()
                                    << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has "
                                    << myHero->getWallet() << " coins. Mario will attempt to fight the koopa again.";
                                    output << "\n";
                                    output << "\n===============\n" << std::endl;
                                    currLevel->printLevel(&output);
                                    output << "\nMario fought the koopa again";
                                    count++;
                                    break;
                                }
                                case 3:{//loses but powerlevel is 0
                                    output << " and lost while at power level 0, so he lost a life. Mario is at power level " 
                                    << myHero->getPowerLevel() << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has " 
                                    << myHero->getWallet() << " coins. Mario will attempt to fight the koopa again.";
                                    output << "\n";
                                    output << "\n===============\n" << std::endl;
                                    currLevel->printLevel(&output);
                                    output << "\nMario fought the koopa again";
                                    count++;
                                    break;
                                }
                                case 4:{//loses, powerlevel 0, lives left is 0, game over
                                    gameIsOver = true;
                                    count++;
                                    output << " and lost while at power level 0 with no lives left."
                                    << "The game is over and Mario LOST. It took " << count << " moves." << std::endl;
                                    break;
                                }
                                default:{
                                    std::cout << "invalid fight outcome" << std::endl;
                                    break;
                                }
                            }
                        }
                        break;
                    }
                    case 'b':{
                        bool bossBeaten = false;
                        int tempPL = myHero->getPowerLevel();
                        output << "Level: " << i << ". Mario is at position " << currLevel->getMarioPos()
                        << ". Mario encountered the boss";
                        while(!bossBeaten && !gameIsOver){
                            if(i == numLevels-1){
                                int result = myHero->engageEnemy('b');
                                switch(result){
                                    case 1:{//wins
                                        output << " and WON, saving the princess! Mario finished the game in " << count << " moves." << std::endl;
                                        gameIsOver = true;
                                        levelComplete = true;
                                        bossBeaten = true;
                                        count++;
                                        break;
                                    }
                                    case 2:{ //loses but powerlevel is 2
                                        output << " and lost, lowering his power level. Mario is at power level " << myHero->getPowerLevel()
                                        << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has " 
                                        << myHero->getWallet() << " coins. Mario will attempt to fight the boss again.";
                                        output << "\n";
                                        output << "\n===============\n" << std::endl;
                                        currLevel->printLevel(&output);
                                        output << "\nMario fought the boss again";
                                        tempPL = 0;
                                        count++;
                                        break;
                                    }
                                    case 3:{ //loses, powerlevel is 0 or 1, loses a life
                                        output << " and lost while at power level " << tempPL << ", so he lost a life. Mario is at power level " 
                                        << myHero->getPowerLevel() << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has " 
                                        << myHero->getWallet() << " coins. Mario will attempt to fight the boss again.";
                                        output << "\n";
                                        output << "\n===============\n" << std::endl;
                                        currLevel->printLevel(&output);
                                        output << "\nMario fought the boss again";
                                        tempPL = 0;
                                        count++;
                                        break;
                                    }
                                    case 4:{ //loses, powerlevel is 0 or 1, lives left is 0, game over
                                        gameIsOver = true;
                                        count++;
                                        output << " and lost while at power level " << tempPL << " with no lives left."
                                        << "The game is over and Mario LOST. It took " << count << " moves." << std::endl;
                                        break;
                                    }
                                    default:{
                                        std::cout << "invalid fight outcome" << std::endl;
                                        break;
                                    }
                                }
                            }
                            else{
                                int result = myHero->engageEnemy('b');
                                switch(result){
                                    case 1:{//wins
                                        output << " and WON. Mario is at power level " << myHero->getPowerLevel()
                                        << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has "
                                        << myHero->getWallet() << " coins. Mario will move to the next level." << std::endl;
                                        bossBeaten = true;
                                        levelComplete = true;
                                        count++;
                                        break;
                                    }
                                    case 2:{ //loses but powerlevel is 2
                                        output << " and lost, lowering his power level. Mario is at power level " << myHero->getPowerLevel()
                                        << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has " 
                                        << myHero->getWallet() << " coins. Mario will attempt to fight the boss again.";
                                        output << "\n";
                                        output << "\n===============\n" << std::endl;
                                        currLevel->printLevel(&output);
                                        output << "\nMario fought the boss again";
                                        tempPL = 0;
                                        count++;
                                        break;
                                    }
                                    case 3:{ //loses, powerlevel is 0 or 1, loses a life
                                        output << " and lost while at power level " << tempPL << " so he lost a life. Mario is at power level " 
                                        << myHero->getPowerLevel() << ". Mario has " << myHero->getLivesRemaining() << " lives left. Mario has " 
                                        << myHero->getWallet() << " coins. Mario will attempt to fight the boss again.";
                                        output << "\n";
                                        output << "\n===============\n" << std::endl;
                                        currLevel->printLevel(&output);
                                        output << "\nMario fought the boss again";
                                        tempPL = 0;
                                        count++;
                                        break;
                                    }
                                    case 4:{ //loses, powerlevel is 0 or 1, lives left is 0, game over
                                        gameIsOver = true;
                                        count++;
                                        output << " and lost while at power level " << tempPL << " with no lives left."
                                        << "The game is over and Mario LOST. It took " << count << " moves." << std::endl;
                                        break;
                                    }
                                    default:{
                                        std::cout << "invalid fight outcome" << std::endl;
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    }
                    case 'w':{
                        output << "Level: " << i << ". Mario is at position " << currLevel->getMarioPos() 
                        << ". Mario found a warp pipe. Mario is at power level " << myHero->getPowerLevel() << ". Mario has " 
                        << myHero->getLivesRemaining() << " lives left. Mario has " << myHero->getWallet() 
                        << " coins. Mario will WARP to the next level." << std::endl;
                        levelComplete = true;
                        count++;
                        break;
                    }
                    default:{
                        output << "Level: " << i << ". Mario is at position " << currLevel->getMarioPos()
                        << ". Mario came to an empty tile. Mario is at power level " << myHero->getPowerLevel() << ". Mario has " 
                        << myHero->getLivesRemaining() << " lives left. Mario has " << myHero->getWallet() 
                        << " coins. Mario will move on." << std::endl;
                        currLevel->clearTile(myHero->getRow(currLevel), myHero->getCol(currLevel));
                        count++;
                        break;
                    }
                }
            }
            delete currLevel;
        }
    }
}