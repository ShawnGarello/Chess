/*
 * File: King.h
 * Author: Shawn Garello
 * Created on May 5/28/2025, 11:04 AM
 * Purpose: King Class Specification
*/

#ifndef KING_H
#define KING_H
#include "AbsPiece.h"


class King:public AbsPiece{
    private:
        int kngRow;
        int kngCol;
    public:
        King(string,string,const char *,bool);
        ~King();
        bool cnMvPce(Board *,int,int,int,int,bool,int,int); // checks if movement of pawn is valid
        void setKgPs(int row,int col);
        int getKgRw(){return kngRow;}
        int getKgCl(){return kngCol;}
        AbsPiece* copy();
};
#endif