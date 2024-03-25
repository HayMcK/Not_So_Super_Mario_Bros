#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include "World.h"

class FileProcessor{
    private:
        World *myWorld;
    public:
        FileProcessor();
        ~FileProcessor();
        bool checkTXT(std::string fileName);
        void processFile(std::string inpFile, std::string outFile);
        void writeOutFile(std::string gameOut, std::string outFile);
};


#endif