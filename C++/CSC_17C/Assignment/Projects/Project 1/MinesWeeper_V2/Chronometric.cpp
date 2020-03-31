/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   player.h
 * Author: David guijosa
 *
 * Created on November 29, 2018, 2:24 PM
 */
#include <ctime>
#include "Chronometric.h"

chrono::chrono(){           //sets all values to 0
    mode=0;             
    winlose="None";         
    timest=0;
}

void chrono::play(){
    int y=0;            //y coordinates
    char x=0;           //x coordinates
    do{
        cin>>mode;      //input game mode
        switch (mode){      //set the number of mines and time
            //types of difficulty
            case 0:exit(0);break;
            case 1:maps.setnmin(20),toend=1*60*60;break;
            case 2:maps.setnmin(40),toend=.5*60*60;break;
            case 3:maps.setnmin(60);toend=.3*60*60;break;
            case 4:rules();break;
        }
    }while(mode==4); 
    maps.setrow(10);
    maps.setcol(10);    
    maps.crtmaps(); //create both the index and the real map
    maps.prtindx();
    timest=time(0); // game start
    do{
        do{
                cout<<"input the coordinate you want to reveal"
                        <<endl;
                cin>>x>>y;//input the coordinates of the game
                if(x>=65&&x<=74)x-=65;
                else if(x>=97&&x<=106)x-=97;
                if(maps.aredy(y,x))cout<<"Input a new coordinate"<<endl;
            }while(maps.aredy(y,x)||x<0||x>9||y<0||y>9);
        if(maps.getcord(y,x)=='0'){maps.reveal0(y,x);}
        else maps.reveal(y,x);//give to "hide" the value of inputed coordinates 
        maps.prtindx();//reveal map;
        if(maps.gtmoves()==0){winlose="Win";ply+=mode;}//if you find 
                                                         //all the mines
        else if(maps.getcord(y,x)=='X')winlose="Lost";//if the coordinate has a mine
        else ply+=5*mode;
    }while(ply.isalive(maps.getcord(y,x)&&time(0)<toend-timest)
            &&winlose=="None");  
    //output winer
    cout<<"You have "<<winlose<<" the game with "<<ply.gtpoint()<<" points"
            <<endl;
    if(winlose=="Win")ply+=mode*5;
}
ostream &operator<<(ostream &str,const chrono &obj){
    str<<"Welcome to Minesweeper"<<endl;
    str<<"To get into easy mode press 1"<<endl;
    str<<"To get into normal mode input 2"<<endl;
    str<<"To get into hard mode input 3"<<endl;
    str<<"To know information of the game press 4"<<endl;
    str<<"To Exit input 0"<<endl;
    return str;
}
void chrono::rules()const{
    cout<<"In order to win the game, you must reveal all the squares that "
          "DO NOT contain a mine"<<endl<<"If a mine is revealed,"
          " the player loses"<<endl;
    cout<<"to reveal a location you must enter the coordinates of it, as X " 
            <<endl<<"coordinates represented by a letter and Y coordinates "
            "as numbers EX: A9"<<endl;
    cout<<"The number that you reveal represent the number of mines around them"
            <<endl;
    cout<<"Mines are represented as X"<<endl;
    cout<<"easy mode has a maximum of 20 mines with 1 hour to complete"<<endl;
    cout<<"Normal mode has a maximum of 40 mines with 40 minutes to complete"<<endl;
    cout<<"Hard mode has a maximum of 60 mines with 30 minutes to complete"<<endl;
}