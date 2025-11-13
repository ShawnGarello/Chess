/* 
 * File:   main.cpp
 * Author: Shawn Garello
 * Created on May 28,2025
 * Purpose  Project 2 OOP - Board Game: Chess
 *          Continuation from Project 1 purpose of this version
 *          Is just continuation from V4.Final version. Converted
 *          everything in old code to classes. Adding 5 more things
 *          Needed in check off list.
 *           
 */
//System Libraries
#include <iostream>  //I/O Library
#include <iomanip>
#include <cstring>
#include <iomanip>
#include <fstream>
#include "Board.h"
#include "AbsPiece.h"
#include "GameRec.h"

using namespace std;

//User Libraries

//Global Constants Only
//Well known Science, Mathematical and Laboratory Constants

//Function Prototypes
void dsplyB(Board *board, int r, int c);

//Execution of Code Begins Here
int main(int argc, char** argv) {
    //Set the random number seed here

    //Declare all variables for this function
    fstream txtFile,binFile;
    Board *b;

    //Initialize all known variables
    txtFile.open("GameRecord.txt",ios::out|ios::trunc);
    binFile.open("GameRecord.bin",ios::in|ios::out|ios::trunc|ios::binary);
    b = new Board;
    b->setBrd(8,8);
    GameRec game(b);
    
    //Process Inputs to Outputs -> Mapping Process
    //Maps known values to the unknown objectives
    
    //Display the Inputs/Outputs
    game.dsplyBd(b,8,8);
    game.gamePly(b,binFile,txtFile);
    
    //Clean up the code, close files, deallocate memory, etc....
    txtFile.close();
    binFile.close();

    //Exit stage right
    return 0;
}
//Function Implementations