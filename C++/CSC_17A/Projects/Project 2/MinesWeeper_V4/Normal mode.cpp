/* 
 * File:   player.h
 * Author: David guijosa
 *
 * Created on November 23, 2018, 2:24 PM
 */

#include "Normal mode.h"
Normal::Normal(){
    mode=0;
    winlose="None";
}
void Normal::rules()const{
    cout<<"In order to win the game, you must reveal all the squares that "
          "DO NOT contain a mine"<<endl<<"If a mine is revealed,"
          " the player loses"<<endl;
    cout<<"to reveal a location you must enter the coordinates of it, as X " 
            <<endl<<"coordinates represented by a letter and Y coordinates "
            "as numbers EX: A9"<<endl;
    cout<<"The number that you reveal represent the number of mines around them"
            <<endl;
    cout<<"Mines are represented as X"<<endl;
    cout<<"easy mode has a maximum of 20 mines at the beginning"<<endl;
    cout<<"Normal mode has a maximum of 40 mines at the beginning"<<endl;
    cout<<"Hard mode has a maximum of 60 mines at the beginning"<<endl;
}
        
void Normal::play(){
    int y=0;    //y coordinates
    char x=0;   //x coordinates
    do{
        cin>>mode; //input game mode
        switch (mode){
            case 0:exit(0);break;
            case 1:maps.setnmin(20);break;
            case 2:maps.setnmin(40);break;
            case 3:maps.setnmin(60);break;
            case 4:rules();break;
        }
    }while(mode==4);
    maps.setrow(10);
    maps.setcol(10);
    maps.crtmaps(); //creates maps
    maps.prtindx(); //print the index
    do{
        do{
                cout<<"input the coordinate you want to reveal"
                        <<endl;
                cin>>x>>y;      //input coordinates
                if(x>=65&&x<=74)x-=65;
                else if(x>=97&&x<=106)x-=97;
                if(maps.aredy(y,x))cout<<"Input a new coordinate"<<endl;
            }while(maps.aredy(y,x)||x<0||x>9||y<0||y>9);
        if(maps.getcord(y,x)=='0'){maps.reveal0(y,x);}
        else maps.reveal(y,x);//give to index the value of inputed coordinates 
        maps.prtindx();//reveal map;
        if(maps.gtmoves()==0){winlose="Win";ply+=mode;}//if you find 
                                                         //all the mines
        else if(maps.getcord(y,x)=='X')winlose="Lost";//if the coordinate has a mine
        else ply+=5*mode;
    }while(ply.isalive(maps.getcord(y,x))&&winlose=="None");  
    cout<<"You have "<<winlose<<" the game"<<endl;
    if(winlose=="Win")ply+=mode*5;
}
ostream &operator<<(ostream &str,const Normal &obj){
    str<<"Welcome to Minesweeper"<<endl;
    str<<"To get into easy mode press 1"<<endl;
    str<<"To get into normal mode input 2"<<endl;
    str<<"To get into hard mode input 3"<<endl;
    str<<"To know information of the game press 4"<<endl;
    str<<"To Exit input 0"<<endl;
    return str;
}
int Normal::getmode()const{
    return mode;
}
string Normal::gtstatu()const{
    return winlose;
}