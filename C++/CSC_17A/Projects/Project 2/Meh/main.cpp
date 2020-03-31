/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on Oct 16th, 2018, 2:00 PM
 * Purpose:  project
 */

//System Libraries Here
#include <iostream>   //
#include <cmath>      //
#include <cstdlib>    //
#include <iomanip>    //
#include <ctime>      //
#include <fstream>    //
#include <cstring>    //

using namespace std;

//User Libraries Here
#include "Show Map.h"
//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
void rules();                      //output information if needed
void menu();                       //output menu
//Program Execution Begins Here
int main(int argc, char** argv) {
    //declare random seed
    srand(static_cast<unsigned int>(time(0)));
    //initialize stream
    fstream bin;
    bin.open("data.bin",ios::in|ios::out|ios::binary);
    //Declare and all Variables Here
    const int row=10;
    const int col=10;
    char val;
    HIDE hide(row,col);
    MAP map(row,col);
    char x,                     //input coordinate
         ability;               //ability
    int mode,                   //difficulty mode
        y,                      //row coordinates 
        move,                   //number of moves
        cntn=1,                 //continue playing
        nMines=20;                 //number of mines
    string winlose="Normal",YN;   //win or lost
    float points;               //abilities points
    bool save=false;            // save argument
    //output menu
    do {
        menu();
        cin>>mode;
        if(mode==4)rules();
        else if(mode>4||mode<0)cout<<"Input a valid number"<<endl;
    }while(mode>3||mode<0);
    //create game map
    if(mode>0&&mode<4){
        switch (mode){
        //mines in map map
            case 1: {nMines=20;break;}
            case 2: {nMines=40;break;}
            case 3: {nMines=40;break;}  
        }
        //create maps
        map.flmap(nMines);
        hide.fillmap();
        //number of non-mines
        move=(row*col)-nMines;
        //moves/inputed coordinates
        while(winlose=="Normal"&&move>0){
            map.getcord(y,x);
            hide.reveal(y,x);//give to "hide" the value of inputed coordinates 
            val=map.getval(y,x);
            if(val=='0')hide.reveal0(y,x);
            cout<<hide;//reveal map;
            move--;                  //moves left to win   
            if(move==0){winlose="Win";points+=sqrt(0.2)/mode;}//if you find 
                                                             //all the mines
            else if(val=='X')winlose="Lost";//if the coordinate has a mine
            else points+=0.01/mode;
        }
        //output if winner or loser
        cout<<"you have "<<winlose<<" the game"<<endl;
        //print map after win or lose
        cout<<map;
        if(winlose=="Win"){
            cout<<"do you want to save?Y/N -->";
            cin>>YN;
            YN="y"?YN="Y":YN="Y";
            if(YN=="Y")save=true;}
        if(save==true)bin<<points;
    }
    //Exit
    else cout<<"Thanks for playing"<<endl; 
    bin.close();
    //clean memory
    map.~MAP();
    hide.~MAP();
    return 0;
}
void rules(){
    cout<<"In order to win the game, you must reveal all the squares that "
          "DO NOT contain a mine, whether you flag them or not is a matter"
          " of personal preference."<<endl<<"If a mine is revealed,"
          " the player loses"<<endl;
    cout<<"to reveal a location you must enter the coordinates of it, as X "
            "coordinates represented by a letter and Y coordinates as numbers"
            <<endl<<"EX: A9, to flag a coordinate you must enter an Z before"
            "the coordinate EX: ZA9"<<endl;
    cout<<"The number that you reveal represent the number of mines around them"
            <<endl;
    cout<<"Mines are represented as X"<<endl;
    cout<<"easy mode has a maximum of 20 mines at the beginning"<<endl;
    cout<<"Normal mode has a maximum of 40 mines at the beginning"<<endl;
    cout<<"Hard mode has a maximum of 60 mines at the beginning"<<endl;
}
void menu(){
        cout<<"Welcome to Minesweeper"<<endl;
        cout<<"To get into easy mode press 1"<<endl;
        cout<<"To get into normal mode input 2"<<endl;
        cout<<"To get into hard mode input 3"<<endl;
        cout<<"To know information of the game press 4"<<endl;
        cout<<"To Exit input 0"<<endl;
}