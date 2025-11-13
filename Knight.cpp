/*
 * File: Knight.h
 * Author: Shawn Garello
 * Created on May 5/29/2025, 6:59PM
 * Purpose: Knight Class Implementation
*/

#include "Knight.h"
#include "Board.h"


Knight::Knight(string nme, string ownr, const char symbl[4], bool hsMved)
    :AbsPiece(nme, ownr, symbl, hsMved){}

Knight::~Knight(){}

bool Knight::cnMvPce(Board* board,int fromRow,int fromCol,int toRow,int toCol,bool isChck,int kngRw,int kngCl){
    AbsPiece*** brd = board->getBrd();
    int rowSpce=fromRow>toRow?fromRow-toRow:toRow-fromRow;//calc total row spaces moved
    int colSpce=fromCol>toCol?fromCol-toCol:toCol-fromCol;//calc total col spaces moved
    if(((rowSpce==2&&colSpce==1)||(rowSpce==1&&colSpce==2))&& // L movement for knight must be 3 spaces
       brd[toRow][toCol]->getOwnr()!=brd[fromRow][fromCol]->getOwnr()){
        if(board->simMove(brd,fromRow,fromCol,toRow,toCol,kngRw,kngCl))return true;
    } 
    return false;                                                           
}  

AbsPiece* Knight::copy(){
    return new Knight(*this);
}