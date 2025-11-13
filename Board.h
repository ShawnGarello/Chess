/*
 * File: Board.h
 * Author: Shawn Garello
 * Created on May 5/29/2025, 1:45 AM
 * Purpose: Board class specification includes things
 *          of boards like creating it,functions of boards,etc
*/

#ifndef BOARD_H
#define BOARD_H
#include "AbsPiece.h"

class Board{
    private:   
        AbsPiece*** board;//2d array of ptr of AbsPiece class which is the board
        int row;
        int col;
    public:
    Board(int,int);
    Board();
    ~Board();
    void mvePce(AbsPiece***,int,int,int,int); // moves the piece of where its from to where user wants it
    bool isAtck(AbsPiece***,int,int);// checks if piece is being attacked
    bool simMove(AbsPiece***,int,int,int,int,int,int);//simulate move to see if move makes king in check
    AbsPiece*** getBrd(){return board;}
    void setBrd(int,int);
};
#endif