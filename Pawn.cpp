/*
 * File: Pawn.cpp
 * Author: Shawn Garello
 * Created on May 5/28/2025, 11:04 AM
 * Purpose: Pawn class Implementation
*/
#include "Pawn.h"
#include "Board.h"

Pawn::Pawn(string nme, string ownr, const char symbl[4], bool hsMved)
    :AbsPiece(nme, ownr, symbl, hsMved){}

Pawn::~Pawn(){}

bool Pawn::cnMvPce(Board* board,int fromRow,int fromCol,int toRow,int toCol,bool isChck,int kngRw,int kngCl){
    AbsPiece*** brd = board->getBrd();
    int rowSpce=fromRow>toRow?fromRow-toRow:toRow-fromRow;//calc total row spaces moved
    int colSpce=fromCol>toCol?fromCol-toCol:toCol-fromCol;//calc total col spaces moved
    int rowDir=fromRow>toRow?-1:1; // checks row direction (down = negative, up = pos)
    int colDir=fromCol>toCol?-1:1;// checks col dir(left=negative,right=pos)
    
    if(rowSpce==2&&colSpce==0&&brd[fromRow][fromCol]->getHsMv()==false&& // move pawn up 2
       brd[toRow][toCol]->getOwnr()=="EMPTY"&&brd[fromRow+1*rowDir][toCol]->getOwnr()=="EMPTY"){
        if(board->simMove(brd,fromRow,fromCol,toRow,toCol,kngRw,kngCl))return true;
    }

    //move pawn 1 space foward(decrease row if player 1, up otherwise)
    else if(rowSpce==1&&colSpce==0&&brd[toRow][toCol]->getOwnr()=="EMPTY"&&((brd[fromRow][fromCol]->getOwnr()=="Player 1"&&
            rowDir==-1)||(brd[fromRow][fromCol]->getOwnr()=="Player 2"&&rowDir==1))){
        if(board->simMove(brd,fromRow,fromCol,toRow,toCol,kngRw,kngCl))return true;
    } 

    else if(rowSpce==1&&colSpce==1&&brd[toRow][toCol]->getOwnr()!=brd[fromRow][fromCol]->getOwnr() // move pawn diagnally to capture piece
            &&brd[toRow][toCol]->getOwnr()!="EMPTY"){
                if(brd[fromRow][fromCol]->getOwnr()=="Player 1"&&fromRow>toRow){
                    if(board->simMove(brd,fromRow,fromCol,toRow,toCol,kngRw,kngCl))return true;
                }
                else if(brd[fromRow][fromCol]->getOwnr()=="Player 2"&&fromRow<toRow){
                    if(board->simMove(brd,fromRow,fromCol,toRow,toCol,kngRw,kngCl))return true;
                }
            }
    return false;
}

AbsPiece* Pawn::copy(){
    return new Pawn(*this);
}