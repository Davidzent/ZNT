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
        char *answer;                       //Code to find
        bool *inptchk;                      //is the letter already being count in checking
                
    public:
        Game(int,int,int,bool);             //constructor
        bool chkletr();                     //checks if the Letter is in the list
        bool chkdupl(const char*,const int);//checks for duplicates in an array
        void crtans();                      //creates a new answer    
        void chcinpt();                     //check number of correct input
        void play();                        //play the game
        ~Game();                            //destructor
             
    protected:
        char *letters;                      //letters to choose from
        char **Plyinpt;                     //player inputs
        bool duplict;                       //allow duplicates
        bool status;                        //if the game is still going
        int nInput;                         //This turns input
        int nCorrct;                        //number of correct inputs
        int nPerfc;                         //number of perfect inputs
        int CodeSz;                         //code size
        int atempts;                        //number of attempts
        int nLetter;                        //number of letters to choose from
        
};


#endif /* GAME_H */

