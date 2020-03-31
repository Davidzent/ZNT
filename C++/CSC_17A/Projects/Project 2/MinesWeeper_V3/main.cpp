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

//Program Execution Begins Here
int main(int argc, char** argv) {
    //create game
    GAME game;
    //output menu
    cout<<game;
    //run game
    game.play();
    //Exit
    return 0;
}