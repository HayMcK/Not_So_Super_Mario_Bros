#include "FileProcessor.h"

int main(int argc, char **argv){
    FileProcessor marioGame;
    marioGame.processFile(argv[1], argv[2]);
    return 0;
}