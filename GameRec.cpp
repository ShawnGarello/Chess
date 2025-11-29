/*
 * File: Game.cpp
 * Author: Shawn Garello
 * Created on May 5/30/2025, 4:27 PM
 * Purpose: Game Class Implementation
*/

#include "GameRec.h"
#include "Board.h"
#include <cstring> // for strcpy
#include <iomanip> 
#include <iostream>
#include <fstream> // files
#include <list>
#include <map>
#include <algorithm>
#include <utility>
#include <set>
#include <queue>
int* GameRec::turn = new int(1);

GameRec::GameRec(Board *board,char *fromPos,char *toPos){
    brd = board;
    strcpy(from,fromPos);
    strcpy(to,toPos);
}
GameRec::GameRec(Board *board){
    brd = board;
}
GameRec::GameRec(const GameRec &gmeRc){
    brd = gmeRc.brd;
    strcpy(from,gmeRc.from);
    strcpy(to,gmeRc.to);
}
GameRec::~GameRec(){}
void GameRec::gamePly(Board *board,fstream &binOut,fstream &txtOut){
    list<GameRec *> record1; // record of player 1 moves;
    queue<GameRec *> record2; // record of player 2 moves;
    AbsPiece*** brd = board->getBrd();
    map<string,int> p1;
    map<string,int>p2;
    string player;
    bool isChck = false;
    bool canMove = false;
    const int SIZE = 3;
    int p1KngRw=7;//row of player 1 king
    int p1KngCl=4;//col of player 1 king
    int p2KngRw=0;//row of player 2 king
    int p2KngCl=4;//col of player 2 king
    bool kpPly = true;
    do{
        int frmRow = 0;int frmCol = 0;
        int toRow=0;int toCol = 0;
        
        char from[SIZE];
        char to[SIZE];
        cout<<endl;
        player = *turn%2==0?"Player 2":"Player 1";
        do{
            isChck = false;
            isChck=*turn%2==0?board->isAtck(brd,p2KngRw,p2KngCl):board->isAtck(brd,p1KngRw,p1KngCl);
            if(isChck)cout<<setw(18)<<"CHECK! "<<player<<" IS IN CHECK."<<endl;
            try{
                kpPly=getInpt(from,to);
                if(!kpPly)break;
            }
            catch (const char *msg){
                cout<<"Error: "<<msg;
            }
            cnvrtIn(from,frmRow,frmCol);
            cnvrtIn(to,toRow,toCol);
            if(brd[frmRow][frmCol]->getOwnr()==player){
                if(player=="Player 2")canMove=brd[frmRow][frmCol]->cnMvPce(board,frmRow,frmCol,toRow,toCol,isChck,p2KngRw,p2KngCl);
                else canMove=brd[frmRow][frmCol]->cnMvPce(board,frmRow,frmCol,toRow,toCol,isChck,p1KngRw,p1KngCl);
            }
        }while(!canMove);
        if(!kpPly)break;
        if(brd[frmRow][frmCol]->getHsMv()==false)brd[frmRow][frmCol]->setHsMv(true);
        AbsPiece* piece = brd[frmRow][frmCol];
        board->mvePce(brd,frmRow,frmCol,toRow,toCol);
        if(brd[toRow][toCol]->getName() == "King"){
            if(player == "Player 1"){
                p1KngRw = toRow;
                p1KngCl = toCol;
            }
            else if(player == "Player 2"){
                p2KngRw = toRow;
                p2KngCl = toCol;
            }
        }
        /*
        debug
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++) {
                AbsPiece* piece = brd[i][j];
                cout << "Piece at [" << i << "][" << j << "]: "
                     << "pce = " << piece->getPce() << ", "
                     << "name = " << piece->getName() << ", "
                     << "owner = " << piece->getOwnr() << ", "
                     << "hasMove = " << (piece->getHsMv() ? "true" : "false")
                     << endl;
            }
        }
        cout<<"King player 1 pos row:"<<p1KngRw<<"  col:"<<p1KngCl<<endl;
        cout<<"King player 2 pos row:"<<p2KngRw<<"  col:"<<p2KngCl<<endl;
        */
        GameRec *rec = filObj(board,from,to,turn);
        GameRec *copy2 = rec;//copies and points to same thing using overlaoded =
        GameRec *copy1 = new GameRec(*rec);// copies using copy constructor
        if(*turn%2==0){
            record2.push(copy1);
        }
        else{
            record1.push_back(copy1);
        }
        if(*copy1==*rec){
            wrtBin(binOut,rec,piece);
            wrtTxt(txtOut,rec,piece);
        }
        dsplyBd(board,8,8,rec,toRow,toCol);
        pair<int,int> points = clcScor(p1,p2,brd);
        cout << endl;
        shwScor(p1,p2,points);
        delete rec;
        (*turn)++;
        canMove = false;
        //testing template function
        //shwPlyr<int>(1);
        cout<<endl<<"                ";
        shwPlyr<string>(player);
    }while(kpPly);
    //delete turn;
    cout<<endl<<setw(30)<<"END OF GAME"<<endl;
    cout<<setw(28)<<"HISTORY"<<endl;
    int moveNo = 1;
    list<GameRec*>::iterator it = record1.begin(); // iterator for Player 1 (list)
    cout << setw(6) << "Move#" << setw(18) << "Player 1" << "  " << "Player 2" << "\n";
    while(it != record1.end() || !record2.empty()){
        cout << setw(6) << moveNo++;
        // Player 1 column list
        if(it != record1.end()){
            GameRec* g1 = *it;
            cout << setw(18) << string(g1->getFrom()) + "->" + string(g1->getTo());
            it++;
        }
        else{
            cout << setw(18) << " ";
        }
        cout << "  ";
        // Player 2 column queue
        if(!record2.empty()){
            GameRec* g2 = record2.front();
            record2.pop();  // pop while printing
            cout << string(g2->getFrom()) + "->" + string(g2->getTo());
            delete g2; // delete
        }
        cout << "\n";
    }
    //cleanup remaining GameRec* in the list
    for(GameRec* p : record1){
        delete p;
    }
    record1.clear();
    delete turn;
}
pair<int,int> GameRec::clcScor(map<string,int> &plyr1,map<string,int> &plyr2,AbsPiece*** brd){
    int p1Pt = 0;
    int p2Pt = 0;
    pair<int,int> scores;
    map<string, int> pceVal ={{"Pawn",1},{"Rook",5},{"Queen",9}, // map of score value of each piece
                             {"Bishop",3},{"Knight",3}}; 
    plyr1 ={{"Pawn",0},{"Rook",0},{"Queen",0}, // maps amount of specific pieces
                             {"Bishop",0},{"Knight",0}}; // taken to help calc players score
    plyr2.clear();
    copy(plyr1.begin(),plyr1.end(),inserter(plyr2,plyr2.begin())); // copy p1map to p2map
    for(int i = 0 ; i < 8; i++){
        for(int j = 0; j < 8; j++){
            string owner = brd[i][j]->getOwnr();
            string pceNme = brd[i][j]->getName();
            if(owner == "Player 1") plyr1[pceNme]++;
            if(owner == "Player 2") plyr2[pceNme]++;
        }
    }
    for_each(pceVal.begin(),pceVal.end(),[&](const pair<string,int>& pv){
        p1Pt += pv.second * plyr1[pv.first];
        p2Pt += pv.second * plyr2[pv.first];
    });
    return scores = {p1Pt,p2Pt};
}
void GameRec::tknPce1(map<string,int> p2Map){ // pieces player 1 took
    set<string> allPces = {"Pawn","Knight","Queen","Bishop","Rook"};
    map<string,int> pceAmnt = {{"Pawn",8},{"Queen",1},{"Rook",2},
                               {"Knight",2},{"Bishop",2}};
    map<string,string> p2Symbl = {{"Pawn","P"},{"Rook","R"},{"Knight","k"},
                                {"Bishop","B"},{"Queen","Q"}};
    for(string p : allPces){ // print out the pieces player 1 took
        int captred = pceAmnt[p] - p2Map[p];
        for(int i = 0; i < captred; i++){
            cout <<p2Symbl[p];
        }
        cout << ' ';
    }
}
void GameRec::tknPce2(map<string,int> p1Map){ // pieces player 2 took
    set<string> allPces = {"Pawn","Knight","Queen","Bishop","Rook"};
    map<string,string> p1Symbl = {{"Pawn","!"},{"Rook","/V\\"},{"Knight","?"},
                                {"Bishop","(-)"},{"Queen","\\|/"}};
    map<string,int> pceAmnt = {{"Pawn",8},{"Queen",1},{"Rook",2},
                               {"Knight",2},{"Bishop",2}};
    for(string p : allPces){ // print out the pieces player 2 took
        int captred = pceAmnt[p] - p1Map[p];
        for(int i = 0; i < captred; i++){
            cout <<p1Symbl[p];
        }
        cout << ' ';
    }
}
void GameRec::shwScor(map<string,int> p1Map, map<string,int> p2Map,pair<int,int> plyrPts){
    int score = 0;
    if(plyrPts.first>plyrPts.second){
        score = plyrPts.first - plyrPts.second;
        cout << "Player 1: ";tknPce1(p2Map);cout<<"+" << score << endl;
        cout << "Player 2: ";tknPce2(p1Map);cout << endl;
    }
    else if(plyrPts.first<plyrPts.second){
        score = plyrPts.second - plyrPts.first;
        cout << "Player 1: ";
        tknPce1(p2Map);cout<<endl;
        cout << "Player 2: ";
        tknPce2(p1Map);cout<<" +" << score << endl;
    }
    else{
        cout << "Player 1: ";tknPce1(p2Map);cout << endl;
        cout << "Player 2: ";tknPce2(p1Map);cout << endl;
    }
}

void GameRec::dsplyBd(Board *board,int r,int c,GameRec *p,int toRow,int toCol){
    AbsPiece*** brd = board->getBrd();
    for(int i = 0;i < r;i++){
        cout<<" |-----|-----|-----|-----|-----|-----|-----|-----|\n"<<r-i;
        for(int y = 0; y<c;y++){
            cout<<"| " << brd[i][y]->getPce() << " ";
            if(y==7&&i==4){
                cout<<*p; // uses overloaded operator <<
            }
            else if(y==7)cout<<"|\n";
        }
    }    
    cout<<" |-----|-----|-----|-----|-----|-----|-----|-----|"<<endl;
    cout<<"    a     b     c     d     e     f     g     h   ";
}
    
void GameRec::dsplyBd(Board *board,int r,int c){
    AbsPiece*** brd = board->getBrd();
    for(int i = 0;i < r;i++){
        cout<<" |-----|-----|-----|-----|-----|-----|-----|-----|\n"<<r-i;
        for(int y = 0; y<c;y++){
            cout<<"| " << brd[i][y]->getPce() << " ";
            if(y==7)cout<<"|\n";
        }
    }    
    cout<<" |-----|-----|-----|-----|-----|-----|-----|-----|"<<endl;
    cout<<"    a     b     c     d     e     f     g     h   ";
}
bool GameRec::getInpt(char *from, char *to){
    cout <<"Enter position of piece and destination to be moved(ex:e4 e5) or (QIT GME) to stop:";
    cin >> from >> to;
    if(strcmp(from,"QIT")==0||strcmp(to,"GME")==0)return false;
    if(from[0]<'a'||from[0]>'h' ||to[0]<'a'||to[0]>'h'
       ||from[1]<'1'||from[1]>'8'||to[1]<'1'||to[1]>'8') throw "invalid input";
    return true;
}
void GameRec::cnvrtIn(char *plceArr, int &row, int &col){
    switch(plceArr[0]){ // letters represent the index values of the enum
        case('a'):col=A;break; // 0
        case('b'):col=B;break; // 1
        case('c'):col=C;break; // 2
        case('d'):col=D;break; // 3
        case('e'):col=E;break; // 4
        case('f'):col=F;break; // 5
        case('g'):col=G;break; // 6
        case('h'):col=H;break; // 7
    }
    row = 8 - static_cast<int>(plceArr[1]-'0');//get correct number subtracting based on ascii number
}
void GameRec::wrtTxt(fstream &txtOut, GameRec *rec, AbsPiece *pce){
    txtOut<<right;
    if(rec->getTurn()%2!=0)txtOut<<endl;
    txtOut<<"TURN "<<rec->getTurn()<<setw(20)<<"PIECE"<<setw(22)<<"MOVE\n";
    txtOut<<pce->getOwnr()<<':'<<setw(14)<<pce->getName()<<'['<<pce->getPce()<<']'<<
          setw(15)<<rec->getFrom()<<" to "<<rec->getTo()<<endl;
    txtOut.flush();
}

void GameRec::wrtBin(fstream &binOut, GameRec *rec, AbsPiece *pce){
    binOut.write(reinterpret_cast<char *>(pce->getPce()),4*sizeof(char));
    int lenNme = pce->getName().length();
    binOut.write(reinterpret_cast<char *>(&lenNme),sizeof(lenNme));//write size of string to know
    binOut.write(pce->getName().c_str(),lenNme);                     //where string ends
    int lenOwnr = pce->getOwnr().length();
    binOut.write(reinterpret_cast<char *>(&lenOwnr),sizeof(lenOwnr));
    binOut.write(pce->getOwnr().c_str(),lenOwnr);
    bool hsMv = pce->getHsMv();
    binOut.write(reinterpret_cast<char *>(&hsMv),sizeof(bool));
    int t = rec->getTurn();
    binOut.write(reinterpret_cast<char *>(&t),sizeof(int));
    char* toPos = rec->getTo();
    binOut.write(reinterpret_cast<char *>(toPos),3*sizeof(char));
    char* fromPos = rec->getFrom();
    binOut.write(reinterpret_cast<char *>(fromPos),3*sizeof(char));
} 
 void GameRec::setTo(const char toPos[3]){
    strcpy(to,toPos);
}
 void GameRec::setFrom(const char fromPos[3]){
    strcpy(from,fromPos);
}
void GameRec::setTurn(int *t){
    *turn = *t;
}
GameRec* GameRec::filObj(Board *board,char *from, char *to,int *turn){
    GameRec *rec = new GameRec(board);
    rec->setFrom(from);
    rec->setTo(to);
    rec->setTurn(turn); // return ptr of dynamically allocated structure
    return rec;
} 
ostream& operator<<(ostream &cout, GameRec &p) {
    cout<<"|   PREVIOUS - TURN "<<p.getTurn()<<':'<<setw(10)<<' '<<p.getFrom()<<" to "
                       <<p.getTo()<<"\n";
    return cout;
}
bool GameRec::operator==(const GameRec &rec2){
    if (brd != rec2.brd) return false;
    if (strcmp(from, rec2.from) != 0) return false;
    if (strcmp(to, rec2.to) != 0) return false;
    if (*turn != *(rec2.turn)) return false;

    return true;
}
GameRec& GameRec::operator=(const GameRec &rec2){
    brd = rec2.brd;
    strcpy(from, rec2.from);
    strcpy(to, rec2.to);
    
    return *this;
}
template <class T>
void GameRec::shwPlyr(T data){
    cout<< "Previous Turn: "<< data << endl;
}