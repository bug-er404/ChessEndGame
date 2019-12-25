/**
*  main.cpp
*  Main for the Chess End Game Configurations Project.
*  Defines the entry point.
*
*
*   Created by Salil Maharjan on 11/27/19.
*  Copyright © 2019 Salil Maharjan. All rights reserved.
*/

#include <iostream>
#include <fstream>
#include "ChessBoard.hpp"
#include "GlobalCounter.hpp"


int main(int argc, const char * argv[]) {
    
    // Text file has comma separated position (x,y) of white king, white rook and black king.
    char* initializationFile = (char*)"initial.board.data";
    std::string buffer;
    // Seeding for random numbers
    srand((int)time(0));
    
    // Variable to process and store the positions to initialize the game.
    Position whiteKing;
    Position whiteRook;
    Position blackKing;
    
    // Clearing text file if they exist,
    // B/c the write method is append
    std::ofstream ofs;
    ofs.open("Maharjan-game.data", std::ios::out | std::ios::trunc);
    ofs.close();
    ofs.open("Maharjan-Steps-Fall2019.data", std::ios::out | std::ios::trunc);
    ofs.close();
    
    // Open file and check if it opened correctly.
    std::ifstream inf(initializationFile);
    if(!inf)
    {
        std::cerr << "Could not open the file: " << initializationFile << std::endl;
        exit(1);
    }
    // Get the position line.
    getline(inf,buffer);
    
    // Setting positions
    whiteKing.x = (buffer[2]-'0')-1;
    whiteKing.y = (buffer[0]-'a');
    whiteRook.x = (buffer[7]-'0')-1;
    whiteRook.y = (buffer[5]-'a');
    blackKing.x = (buffer[12]-'0')-1;
    blackKing.y = (buffer[10]-'a');

    ChessBoard myGame = ChessBoard(whiteRook, whiteKing, blackKing);
    myGame.displayBoard();
    

    // Writing to the Final output text file:
    // Initializing data
    std::ofstream writeFile;
    writeFile.open("Maharjan-game.data", std::ios::app);
    if(writeFile.is_open())
        writeFile<<buffer<<std::endl;
    writeFile.close();
    
    
    
    // Counter for 50 move draw check:
    // We end the game in ChessBoard class so that the results are printed.
    int fiftyMoveDraw = 51;
    int temp;
    while(fiftyMoveDraw!=0)
    {
        temp = myGame.simulateNextState();
        // Checkmate reached
        if(temp==1)
            break;
        myGame.displayBoard();
        fiftyMoveDraw--;
        
    }
    
    
}
