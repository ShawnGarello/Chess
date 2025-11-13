/*
 * File: Bishop.h
 * Author: Shawn Garello
 * Created on May 5/29/2025, 7:46 PM
 * Purpose: Bishop Class Impelentatation
*/

#include "Bishop.h"
#include "Board.h"

Bishop::Bishop(string nme, string ownr, const char symbl[4], bool hsMved)
    :AbsPiece(nme, ownr, symbl, hsMved){}
    
Bishop::~Bishop(){}

bool Bishop::cnMvPce(Board* board,int fromRow,int fromCol,int toRow,int toCol,bool isChck,int kngRw,int kngCl){
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
    return false;//return false if bishop piece being moved isnt how it should be moved
}   

AbsPiece* Bishop::copy(){
    return new Bishop(*this); // creates and returns ptr of the object
}