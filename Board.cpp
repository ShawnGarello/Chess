/*
 * File: Board.cpp
 * Author: Shawn Garello
 * Created on May 5/29/2025, 1:45 AM
 * Purpose: Board class implementation
*/

#include "Board.h"
#include "Empty.h"
#include "Pawn.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include <cstring>

Board::Board(int rw,int cl){
    row = rw;
    col = cl;
    board = new AbsPiece**[row];
    for(int i = 0; i < row; i++){
        board[i] = new AbsPiece*[col];
        for(int j =0; j < col;j++){
            board[i][j] = nullptr;
        }
    }
}
Board::Board(){
    row = 8;
    col = 8;
    board = new AbsPiece**[row];
    for(int i = 0; i < row; i ++){
        board[i] = new AbsPiece*[col];
        for(int j =0; j < col;j++){
            board[i][j] = nullptr;
        }
    }
}

Board::~Board(){
    for(int i = 0 ; i < row; i++){     
        for(int y = 0; y < col; y++){
            delete board[i][y];
        }         
        delete []board[i];
    }
    delete []board;

}

void Board::setBrd(int r, int c){
    int rw,cl;
    
    for(int i = 0;i<r/2;i++){ //since board is mostly symmetrical throughout,
                              //fill in 1/4 of the board
        for(int j =0;j<c/2;j++){//then mirror it
            for(int y=0;y<4;y++){
                rw=y==0||y==1?i:r-1-i;
                cl=y==0||y==3?j:c-1-j;
                if(i==0&&j==0){
                    if(rw==i){
                        board[rw][cl]=new Rook("Rook","Player 2"," R ",false);
                    }
                    else{
                        board[rw][cl]=new Rook("Rook","Player 1", "/V\\",false);
                    } 
                }
                else if(i==0&&j==1){
                    if(rw==i){
                        board[rw][cl]=new Knight("Knight","Player 2"," k ",false);
                    }
                    else{
                        board[rw][cl]=new Knight("Knight","Player 1", " ? ",false);
                    } 
                }
                else if(i==0&&j==2){
                    if(rw==i){
                        board[rw][cl]=new Bishop("Bishop","Player 2"," B ",false);
                    }
                    else{
                        board[rw][cl]=new Bishop("Bishop","Player 1","(-)",false);
                    } 
                }
                else if(i==0&&j==3){
                    if(rw==i){
                        if(y==0){
                            board[rw][cl]=new Queen("Queen","Player 2"," Q ",false);
                            
                        }
                        else{
                            board[rw][cl]=new King("King","Player 2"," K ", false);
                        }
                    }
                    else{
                        if(y==2){
                            board[rw][cl]=new King("King","Player 1","-|-",false);
                        }
                        else{
                            board[rw][cl]=new Queen("Queen","Player 1","\\|/",false);
                        } 
                    }
                }
            }
       } 
    }  
    for(int x = 0; x < c; x++){
        board[1][x]=new Pawn("Pawn","Player 2"," P ",false);
        board[6][x]=new Pawn("Pawn","Player 1"," ! ",false);
    }
    for(int i = 2; i < 6; i++){
        for(int j = 0; j < c; j++){
            board[i][j]=new Empty("EMPTY","EMPTY","   ",false);
        }
    } 
}


bool Board::simMove(AbsPiece*** board,int fromRow,int fromCol,int toRow,int toCol,int kngRw,int kngCl){
    int row = 8;
    int col = 8;
    
    AbsPiece*** tempBrd = new AbsPiece**[row];//dynamically allocate 2d array of Piece
    for(int i = 0; i < row; i++){     // to be a copy of the board
        tempBrd[i] = new AbsPiece*[col];
        for(int j =0; j < col;j++){
            tempBrd[i][j] = nullptr;
        }
    }
    
    for(int i = 0; i < row;i++){
        for(int y = 0; y <col;y++){
            tempBrd[i][y]=board[i][y]->copy();
        }
    }
    mvePce(tempBrd,fromRow,fromCol,toRow,toCol);
    bool isSafe = !isAtck(tempBrd, kngRw, kngCl);//if true(piece/king is safe) then move is valid
    //deallcocate clean up
    for(int i = 0 ; i < row; i++){     
        for(int y = 0; y < col; y++){
            delete tempBrd[i][y];
        }         
        delete []tempBrd[i];
    }
    delete []tempBrd;
    return isSafe;
}
void Board::mvePce(AbsPiece*** board,int fromRow,int fromCol,int toRow,int toCol){
    if(board[toRow][toCol]->getOwnr()=="EMPTY"){
        AbsPiece *temp;
        temp = board[toRow][toCol]->copy();
        delete board[toRow][toCol];
        board[toRow][toCol]=board[fromRow][fromCol]->copy();
        delete board[fromRow][fromCol];
        board[fromRow][fromCol]=temp;
    }
    else{
        delete board[toRow][toCol];
        board[toRow][toCol]=board[fromRow][fromCol]->copy();
        delete board[fromRow][fromCol];
        board[fromRow][fromCol] = new Empty("EMPTY","EMPTY","   ",false);
    }
}
bool Board::isAtck(AbsPiece*** board,int row,int col){// checks if piece is being attacked
    // Check all 8 directions for attacking pieces
    int dir[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1},  
                    {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
    string owner = board[row][col]->getOwnr();
    // Check for queen rook and bishop atck
    for (int i = 0; i < 8; i++) {
        int r = row + dir[i][0];
        int c = col + dir[i][1];
        while (r >= 0 && r < 8 && c >= 0 && c < 8) {
            if (board[r][c]->getOwnr() != "EMPTY") {
                if (board[r][c]->getOwnr() != owner) {
                    // Check if piece can attack in this dir
                    if ((i < 4 && (board[r][c]->getName() == "Rook" || board[r][c]->getName() == "Queen")) ||
                        (i >= 4 && (board[r][c]->getName() == "Bishop" || board[r][c]->getName() == "Queen"))) {
                        return true;
                    }
                }
                break;//break when piece is found
            }
            r += dir[i][0];
            c += dir[i][1];
        }
    }
    // Check pawn attacks
    int pawnDir = (owner == "Player 1") ? 1 : -1;
    int pwnAtck[2][2] = {{pawnDir, -1}, {pawnDir, 1}};
    for (int i = 0; i < 2; i++) {
        int r = row + pwnAtck[i][0];
        int c = col + pwnAtck[i][1];
        if (r >= 0 && r < 8 && c >= 0 && c < 8) {
            if (board[r][c]->getOwnr() != owner && board[r][c]->getName() == "Pawn") {
                return true;
            }
        }
    }
    // Check knight attacks
    int kntMve[8][2] = {{-2,-1}, {-2,1}, {-1,-2}, {-1,2},
                        {1,-2}, {1,2}, {2,-1}, {2,1}};
    for (int i = 0; i < 8; i++) {
        int r = row + kntMve[i][0];
        int c = col + kntMve[i][1];
        if (r >= 0 && r < 8 && c >= 0 && c < 8) {
            if (board[r][c]->getOwnr() != owner && board[r][c]->getName() == "Knight") {
                return true;
            }
        }
    }
    return false;
}   