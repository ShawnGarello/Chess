/*
 * File: Queen.cpp
 * Author: Shawn Garello
 * Created on May 5/29/2025, 8:10PM
 * Purpose: Queen Class Implementation
*/
#include "Queen.h"
#include "Board.h"

Queen::Queen(string nme, string ownr, const char symbl[4], bool hsMved)
    :AbsPiece(nme, ownr, symbl, hsMved){}

Queen::~Queen(){}

//Since Queen movement is the same as a rook (horizontal,vertical) and bishop(diagnol) I copied
//over the movement functions from those classes and combined the code together.
bool Queen::cnMvPce(Board* board,int fromRow,int fromCol,int toRow,int toCol,bool isChck,int kngRw,int kngCl){
    AbsPiece*** brd = board->getBrd();
    int rowSpce=fromRow>toRow?fromRow-toRow:toRow-fromRow;//calc total row spaces moved
    int colSpce=fromCol>toCol?fromCol-toCol:toCol-fromCol;//calc total col spaces moved
    int rowDir=fromRow>toRow?-1:1; // checks row direction (down = negative, up = pos)
    int colDir=fromCol>toCol?-1:1;// checks col dir(left=negative,right=pos)
    if((rowSpce==colSpce)&&rowSpce>0&&colSpce>0&&brd[toRow][toCol]->getOwnr()!=brd[fromRow][fromCol]->getOwnr()){
        for(int i = 1; i<rowSpce;i++){ // loop checks every space inbetween 
            if(brd[fromRow+i*rowDir][fromCol+i*colDir]->getOwnr()!="EMPTY")return false;
        }   
        if(board->simMove(brd,fromRow,fromCol,toRow,toCol,kngRw,kngCl))return true;
    } 
    
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
    return false;//return false if Queen piece being moved isnt how it should be moved
}            

AbsPiece* Queen::copy(){
    return new Queen(*this);
}