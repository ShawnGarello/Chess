/*
 * File: Rook.h
 * Author: Shawn Garello
 * Created on May 5/28/2025, 11:04 AM
 * Purpose: Rook Class Specification
*/

#ifndef ROOK_H
#define ROOK_H
#include "AbsPiece.h"

class Rook:public AbsPiece{
    public:
        Rook(string,string,const char *,bool);
        ~Rook();
        bool cnMvPce(Board *,int,int,int,int,bool,int,int); // checks if movement of pawn is valid
        AbsPiece* copy();
};
#endif