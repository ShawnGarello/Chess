/*
 * File: Pawn.h
 * Author: Shawn Garello
 * Created on May 5/28/2025, 11:04 AM
 * Purpose: Pawn Class Specification
*/

#ifndef PAWN_H
#define PAWN_H
#include "AbsPiece.h"

class Pawn:public AbsPiece{
    public:
        Pawn(string,string,const char *,bool);
        ~Pawn();
        bool cnMvPce(Board *,int,int,int,int,bool,int,int); // checks if movement of pawn is valid
        AbsPiece* copy();
};
#endif