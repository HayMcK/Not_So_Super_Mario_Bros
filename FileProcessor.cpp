#include "FileProcessor.h"

FileProcessor::FileProcessor(){}
FileProcessor::~FileProcessor(){}

/* A boolean function to check if the input file name
that is input in the command line is a .txt file. */
bool FileProcessor::checkTXT(std::string fileName){
    std::string end = ".txt";
    std::string tmp;
    if(fileName.length() <= 4){//make sure the file name isn't just ".txt" or shorter
        return 0;
    }
    for (int i = fileName.length()-4; i < fileName.length(); ++i){//only compare the end of the string for the filename extension type of txt
        tmp = tmp + fileName[i];
    }
    if(tmp == end){
        return 1;
    }
    else{return 0;}
}

/*
*/
void FileProcessor::writeOutFile(std::string gameOut, std::string outFile){
    if(!checkTXT(outFile)){
        std::cerr << "Error: Invalid output file name. Must be a .txt file." << std::endl;
    }
    else {
        std::ofstream myFile(outFile);
        if(!myFile)
            std::cerr << "Error: Failed to open input file." << std::endl;
    }
}

/*Function to process the input and output files*/
void FileProcessor::processFile(std::string inpFile, std::string outFile){
    if(!checkTXT(inpFile)){
        std::cerr << "Error: Invalid input file name. Must be a .txt file." << std::endl;
    }
    else{
        std::ifstream myFile(inpFile);
        if(!myFile)
            std::cerr << "Error: Failed to open input file." << std::endl;
        else{
            std::string myLine;
            int gameInst;//Game Instructions
            int count = 0;
            int l, n, v, c, x, g, k, m;
            while(!myFile.eof()){//while the file contains another line
                getline(myFile, myLine);
                gameInst = stoi(myLine);//string to int of inputs
                count++;
                switch(count){
                    case 1: l = gameInst; break;
                    case 2: n = gameInst; break;
                    case 3: v = gameInst; break;
                    case 4: c = gameInst; break;
                    case 5: x = gameInst; break;
                    case 6: g = gameInst; break;
                    case 7: k = gameInst; break;
                    case 8: m = gameInst; break;
                    default: std::cout << "Invalid input" << std::endl; break;
                }
            }
            if(c + x + g + k + m != 100){
                std::cerr << "Error: Total percent from adding coin tiles, empty tiles, goomba tiles, koopa tiles, and mushroom tiles doesn't equal 100%" << std::endl;
                std::cout << "Make sure these percentages will add to 100%" << std::endl;
            }
            else{
                srand(time(0));
                myWorld = new World(l, n, v, c, x, g, k, m);
            }
            myWorld->Play(outFile);
        }
        myFile.close();
    }
    delete myWorld;
}