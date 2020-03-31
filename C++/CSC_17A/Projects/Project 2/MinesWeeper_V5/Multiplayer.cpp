/* 
 * File:   Multiplayer.h
 * Author: Guijosa David
 *
 * Created on December 10, 2018, 10:11 AM
 */

#include <iostream>
#include "Multiplayer.h"

multy::multy(){
    this->nplayrs=0;
    winer=0;
}
multy::multy(int plyrs){
    this->nplayrs=plyrs;
    this->players=new Player[nplayrs];
    winer=0;
}
void multy::repeat(){
    for(int i=0;i<nplayrs;i++){
        cout<<"Player "<<i<<" Game"<<endl;
        menu();
        play();
    }
}

void multy::fndwiner(){
    for(int j=1;j<nplayrs;j++){
        if(players[winer].gtpoint()<players[j].gtpoint()){
            winer=j;
        }
    }   
}
void multy::run(){
    cout<<"How many players will be playing? (MAX 10)"<<endl;
    cin>>nplayrs;
    repeat();
    fndwiner();
    cout<<"The winner is Player"<<winer+1<<" with "<<players[winer].gtpoint()
            <<" points"<<endl;
}
void multy::stnplyr(int playrs){
    if(playrs>10||playrs<0)exit(EXIT_FAILURE);
    else this->nplayrs=playrs;
}
void multy::menu(){
    cout<<"Welcome to Minesweeper"<<endl;
    cout<<"To get into easy mode press 1"<<endl;
    cout<<"To get into normal mode input 2"<<endl;
    cout<<"To get into hard mode input 3"<<endl;
    cout<<"To know information of the game press 4"<<endl;
    cout<<"To Exit input 0"<<endl;
}
multy::~multy(){
    delete []players;
}