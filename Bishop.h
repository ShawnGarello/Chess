/*
 * File: Bishop.h
 * Author: Shawn Garello
 * Created on May 5/28/2025, 11:04 AM
 * Purpose: Bishop Class Specification
*/

#ifndef BISHOP_H
#define BISHOP_H
#include "AbsPiece.h"

class Bishop:public AbsPiece{
    public:
        Bishop(string,string,const char *,bool);
        ~Bishop();
        bool cnMvPce(Board *,int,int,int,int,bool,int,int); // checks if movement of pawn is valid
        AbsPiece* copy();
};
#endif