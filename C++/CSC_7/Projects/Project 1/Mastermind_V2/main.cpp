/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on Oct 1, 2019, 10:50 AM
 * Purpose: Mastermind Fix Duplicate problems
 */

//System Libraries Here
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

//User Libraries Here
#include "Game.h"
//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Initialize random seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare all Variables Here
    char input;
    char nmfile[15]="letter.txt";
    int nLetter=8;
    int codesz=4;
    int atempts=10;
    bool dupli=true;
    //Menu
    //cout<<"Do you want to customize your game? (Y/N)\n";
    //cin>>input;
    if(input=='Y'||input=='y'){
        cout<<"Enter the number of letters : ";
        cin>>nLetter;
        cout<<"Enter the code size : ";
        cin>>codesz;
        cout<<"How many attempts do you want to have? ";
        cin>>atempts;
        cout<<"Allow duplicates? (Y/N): ";
        cin>>input;
        if(input=='Y'||input=='y')dupli=true;
    }
    //start the game
    Game player(nLetter,codesz,atempts,dupli,nmfile);
    
    //play the game
    player.play();
    
    //Exit
    return 0;
}
//9519418408
