/*
 * File: Game.h
 * Author: Shawn Garello
 * Created on May 5/30/2025, 4:27 PM
 * Purpose: Game Class Specification
*/

#ifndef GAMEREC_H
#define GAMEREC_H
#include "Board.h"
#include <utility>
#include <map>
#include <stack>
#include <queue>
#include <iterator>
#include <list>

enum letter {A,B,C,D,E,F,G,H}; //enum for letters in board, represent index of a column


class GameRec{
    private:
        Board *brd;
        static int *turn;
        char from[3];
        char to[3];
    protected:
        void wrtTxt(fstream &, GameRec *,AbsPiece *);
        void wrtBin(fstream &, GameRec *,AbsPiece *);
        GameRec* filObj(Board *, char *, char*,int *);
    public:
        GameRec(Board *,char *,char *);
        GameRec(Board *);
        GameRec(const GameRec &);
        ~GameRec();
        void dsplyBd(Board *,int,int); // displays the board with some data of current turn
        void dsplyBd(Board *,int,int,GameRec *,int,int); // displays the board with some data of current turn
        bool getInpt(char *, char *); //gets user input from and to place of piece
        void cnvrtIn(char *, int &, int &); // converts user input like (e4) to the array index
        void gamePly(Board *, fstream &, fstream &);
        static int getTurn(){ return *turn; }
        static void setTurn(int *);
        void setFrom(const char[3]);
        void setTo(const char[3]);
        char* getFrom(){ return from; }
        char* getTo(){ return to; }
        Board* getBrd(){ return brd; }
        friend ostream& operator<<(ostream &, GameRec &);
        bool operator==(const GameRec &);
        GameRec& operator=(const GameRec &rec2);
        template <class T>
        void shwPlyr(T);
        pair<int,int> clcScor(map<string,int> &,map<string,int> &,AbsPiece***); // calculate score with maps
        void shwScor(map<string,int>,map<string,int>,pair<int,int>);
        void tknPce1(map<string,int>);
        void tknPce2(map<string,int>);
        void rewind(stack<GameRec *> &, Board *,map<int,AbsPiece *> &,map<int,AbsPiece *> &);
        void prntHst(list<GameRec*>::iterator,list<GameRec*>::iterator,queue<GameRec*> &,int); // rec function for print
        unsigned int DJBHash(const string& str);
};
#endif