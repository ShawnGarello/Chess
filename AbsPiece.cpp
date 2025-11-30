/*
 * File: Piece.cpp
 * Author: Shawn Garello
 * Created on 11/30/2025, 11:04 AM
 * Purpose: Piece class Implementation
*/

#include "AbsPiece.h"
#include <cstring>

AbsPiece::AbsPiece(string nme,string ownr,const char symbl[4],bool hsMved){
    name = nme;
    owner = ownr;
    strcpy(pce,symbl);
    hasMved = hsMved;
}

AbsPiece::~AbsPiece(){}

void AbsPiece::setName(string nme){
    name = nme;
}
void AbsPiece::setOwnr(string ownr){
    owner = ownr;
}
void AbsPiece::setPce(const char symbl[4]){
    strcpy(pce,symbl);
}
void AbsPiece::setHsMv(bool hsMv){
    hasMved = hsMv;
}
void AbsPiece::setKgPs(int row,int col){// virtaul function decided to make a virtual function for 
                                        // setting king position since it is needed when moving a king
                                        // to decide if its in check. Virtual function setKgPs(set king position)
                                        // doesnt rlly do anything for AbsPiece more so for the King class
                                        // when calling this.                                
}