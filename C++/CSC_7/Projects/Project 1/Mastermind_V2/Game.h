/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: rcc
 *
 * Created on September 26, 2019, 10:11 AM
 */

#ifndef GAME_H
#define GAME_H

#include <iostream>
using namespace std;

class Game{
    private:
        int nLetter;        //number of letters 
        int CodeSz;         //code size
        int atempts;        //number of attempts
        bool duplict;       //allow duplicates
        bool status;        //if the game is still playing
        char *answer;       //Code to find
        char *Plyinpt;      //player input
        char *letters;      //Letters to choose from
        
    public:
        Game(int,int,int,bool,char[]);      //constructor
        void crtans();                      //creates the answer
        bool chkdupl(int);                  //checks for duplicates
        bool chkletr();                     //checks if the Letter is the list
        void chcinpt();                     //check number of correct input
        void play();                        //play the game
        ~Game();                            //destructor
};


#endif /* GAME_H */

