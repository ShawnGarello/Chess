/*
 * File: King.cpp
 * Author: Shawn Garello
 * Created on May 5/28/2025, 11:04 AM
 * Purpose: King Class implementation
*/

#include "King.h"
#include "Board.h"
King::King(string nme, string ownr, const char symbl[4], bool hsMved)
    :AbsPiece(nme, ownr, symbl, hsMved){}

King::~King(){}

void King::setKgPs(int row,int col){
    kngRow = row;
    kngCol = col;
}
bool King::cnMvPce(Board* board,int fromRow,int fromCol,int toRow,int toCol,bool isChck,int kngR,int kngC){
    AbsPiece*** brd = board->getBrd();
    int rowSpce=fromRow>toRow?fromRow-toRow:toRow-fromRow;//calc total row spaces moved
    int colSpce=fromCol>toCol?fromCol-toCol:toCol-fromCol;//calc total col spaces moved
    if(((rowSpce==1&&colSpce==0)||(rowSpce==0&&colSpce==1)||(rowSpce==1&&colSpce==1)) // king can only move 1 space
        &&brd[toRow][toCol]->getOwnr()!=brd[fromRow][fromCol]->getOwnr()){
            if(board->simMove(brd,fromRow,fromCol,toRow,toCol,toRow,toCol)){
                kngR=toRow;
                kngC=toCol;
                return true;
            }
        }
    return false;
}

AbsPiece* King::copy(){
    return new King(*this);
}