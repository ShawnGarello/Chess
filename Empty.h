/*
 * File: Empty.h
 * Author: Shawn Garello
 * Created on May 5/30/2025, 12:08 AM
 * Purpose: Empty Class Specification
*/

#ifndef EMPTY_H
#define EMPTY_H
#include "AbsPiece.h"

class Empty:public AbsPiece{
    public:
        Empty(string,string,const char *,bool);
        ~Empty();
        bool cnMvPce(Board *,int,int,int,int,bool,int,int); // checks if movement of pawn is valid
        AbsPiece* copy();
};
#endif
