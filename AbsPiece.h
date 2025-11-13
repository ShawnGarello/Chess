/*
 * File: AbsPiece.h
 * Author: Shawn Garello
 * Created on May 5/28/2025, 11:04 AM
 * Purpose: Piece Class Specification
*/

#ifndef ABSPIECE_H
#define ABSPIECE_H
#include <iostream>
using namespace std;

class Board;//declaration of Board class so AbsPiece knows that it exists since
            // cnMvPce uses functions from Board class and Board class already


class AbsPiece{
    private:
        string name;
        string owner;
        char pce[4];
        bool hasMved;
    public:
        AbsPiece(string,string,const char [4],bool);
        virtual ~AbsPiece();
        virtual bool cnMvPce(Board *,int,int,int,int,bool,int,int) = 0;
        virtual AbsPiece* copy() = 0; // returns a ptr of the copied object for the simMove function
        virtual void setKgPs(int,int);
        void setName(string);
        void setOwnr(string);
        void setPce(const char [4]);
        void setHsMv(bool);
        string getName() const { return name; }
        string getOwnr() const { return owner; }
        char* getPce() { return pce; }
        bool getHsMv() const { return hasMved; }
};
#endif