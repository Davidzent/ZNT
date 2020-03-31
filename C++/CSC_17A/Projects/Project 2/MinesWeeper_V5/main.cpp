/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on Nov 20, 2018, 11:00 AM
 * Purpose:  Minesweeper
 */

//System Libraries Here
#include <iostream>
using namespace std;

//User Libraries Here
#include "Game.h"

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
void playmulty();

//Program Execution Begins Here
int main(int argc, char** argv) {
    char mode;
    //output menu
    cout<<"What time of mines weeper do you want to play"<<endl;
    cout<<"To play minesweeper with a chronometric mode input 1"<<endl;
    cout<<"To play normal minesweeper input 2"<<endl;
    cout<<"To play in multiplayer input 3"<<endl;
    cout<<"input any key to exit"<<endl;
    cin>>mode;
    //create the type of game
        //create and run the game
    if(mode=='1'){GAME<chrono> game;game.PLAY();} 
        //create and run the game     
    else if(mode=='2'){GAME<Normal> game;game.PLAY();} 
        //create and run multiplayer game
    else if(mode=='3'){playmulty();}       
    //Exit the game
    return 0;
}
void playmulty(){
    //create a multiplayer game
    multy game;
    //run the game/games
    game.run();
}