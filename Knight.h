/*
 * File: Knight.h
 * Author: Shawn Garello
 * Created on May 5/28/2025, 11:04 AM
 * Purpose: Knight Class Specification
*/

#ifndef KNIGHT_H
#define KNIGHT_H
#include "AbsPiece.h"

class Knight:public AbsPiece{
    public:
        Knight(string,string,const char *,bool);
        ~Knight();
        bool cnMvPce(Board *,int,int,int,int,bool,int,int); // checks if movement of pawn is valid
        AbsPiece* copy();
};
#endif