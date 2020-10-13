/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on October 6, 2020, 1:25 PM
 */
#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "Piece.h"
using namespace std;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds


/*
 * 
 */
void update(char[][10],Piece);
int main(int argc, char** argv) {
    char board[10][10];
    Piece tshape;
    tshape.piece = new char*[3];
    for(int i=0;i<4;i++){
        tshape.piece[i]=new char[3];
    }
    
    tshape.piece[0][0]='0';
    tshape.piece[0][1]='0';
    tshape.piece[0][2]='0';
    tshape.piece[1][0]='1';
    tshape.piece[1][1]='1';
    tshape.piece[1][2]='1';
    tshape.piece[2][0]='0';
    tshape.piece[2][1]='1';
    tshape.piece[2][2]='0';
    tshape.xpos=5;
    tshape.ypos=0;
    for(int i=0;i<10;i++){
        for(int j=0;j<10;j++){
            board[i][j]='0';
        }
    }
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            //cout<<tshape.piece[i][j];
        }
       // cout<<endl;
    }
    for(int r=0;r<10;r++){
        update(board,tshape);
        for(int i=0;i<10;i++){
            for(int j=0;j<10;j++){
                cout<<board[i][j];
            }
            cout<<endl;
        }
        tshape.ypos++;
        cout<<"\n\n";

        sleep_until(system_clock::now() + seconds(1));
    }
    return 0;
}
void update(char a[][10],Piece p){
    for(int i=p.ypos;i<p.ypos+3;i++){
        for(int j=p.xpos-1;j<p.xpos+2;j++){
            if(p.piece[i-p.ypos][j-p.xpos+1] != '0')
            a[i][j]=p.piece[i-p.ypos][j-p.xpos+1];
        }
    }
}
