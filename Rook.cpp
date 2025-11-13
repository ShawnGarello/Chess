/*
 * File: Rook.cpp
 * Author: Shawn Garello
 * Created on May 5/29/2025, 7:58 PM
 * Purpose: Rook Class Impelementation
*/
#include "Rook.h"
#include "Board.h"


Rook::Rook(string nme, string ownr, const char symbl[4], bool hsMved)
    :AbsPiece(nme, ownr, symbl, hsMved){}

Rook::~Rook(){}
bool Rook::cnMvPce(Board* board,int fromRow,int fromCol,int toRow,int toCol,bool isChck,int kngRw,int kngCl){
    AbsPiece*** brd = board->getBrd();
    int rowSpce=fromRow>toRow?fromRow-toRow:toRow-fromRow;//calc total row spaces moved
    int colSpce=fromCol>toCol?fromCol-toCol:toCol-fromCol;//calc total col spaces moved
    int rowDir=fromRow>toRow?-1:1; // checks row direction (down = negative, up = pos)
    int colDir=fromCol>toCol?-1:1;// checks col dir(left=negative,right=pos)
    if(fromRow==toRow&&fromCol!=toCol&&brd[toRow][toCol]->getOwnr()!=brd[fromRow][fromCol]->getOwnr()){
        for(int i = 1; i < colSpce;i++){
            if(brd[fromRow][fromCol+i*colDir]->getOwnr()!="EMPTY")return false;
        }
        if(board->simMove(brd,fromRow,fromCol,toRow,toCol,kngRw,kngCl))return true;
    }
    else if((fromRow!=toRow&&fromCol==toCol)&&brd[toRow][toCol]->getOwnr()!=brd[fromRow][fromCol]->getOwnr()){
        for(int i = 1; i < rowSpce;i++){
            if(brd[fromRow+i*rowDir][fromCol]->getOwnr()!="EMPTY")return false;
        }      
        if(board->simMove(brd,fromRow,fromCol,toRow,toCol,kngRw,kngCl))return true;
    }
    return false;
}

AbsPiece* Rook::copy(){
    return new Rook(*this);
}