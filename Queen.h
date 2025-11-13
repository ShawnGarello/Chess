/*
 * File: Queen.h
 * Author: Shawn Garello
 * Created on May 5/28/2025, 11:04 AM
 * Purpose: Queen Class Specification
*/

#ifndef QUEEN_H
#define QUEEN_H
#include "AbsPiece.h"

class Queen:public AbsPiece{
    public:
        Queen(string,string,const char *,bool);
        ~Queen();
        bool cnMvPce(Board *,int,int,int,int,bool,int,int); // checks if movement of pawn is valid
        AbsPiece* copy();
};
#endif