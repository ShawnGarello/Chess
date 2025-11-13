/*
 * File: Empty.cpp
 * Author: Shawn Garello
 * Created on May 5/30/2025, 12:10AM
 * Purpose: Empty Class implementation
*/

#include "Empty.h"
#include "Board.h"
Empty::Empty(string nme, string ownr, const char symbl[4], bool hsMved)
    :AbsPiece(nme, ownr, symbl, hsMved){}

Empty::~Empty(){}
//Just empty pieces in the board no need for it to move so just return false everytime
bool Empty::cnMvPce(Board* board,int fromRow,int fromCol,int toRow,int toCol,bool isChck,int kngR,int kngC){
    return false;
}

AbsPiece* Empty::copy(){
    return new Empty(*this);
}