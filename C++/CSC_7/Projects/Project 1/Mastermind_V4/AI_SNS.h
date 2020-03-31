/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AI_SNS.h
 * Author: rcc
 *
 * Created on October 1, 2019, 10:50 AM
 */

#ifndef AI_SNS_H
#define AI_SNS_H

#include "Game.h"

class AISNS: public Game{
    private:
        int  *stats;        //statistics
	int   psbltr; 	    //number of posible letters
        char **pslet;        //all the possible answers in the game
        int row;
        void start();       //initialize the Arrays  
        
        
    public:
        AISNS (int nletter,int CodeSz,int atempts,bool duplict) 
        :Game(nletter,CodeSz,atempts,duplict){start();}     //Copy constructor + Initialize other arrays
        int nDifer(const int);              //checks number of different letter in an input
        char*ctNinpt(int);           	    //Create a input with a N number of different letters
        void check();
        void crtinpt();                     //creates an input to play
        void play();                        //Play the array in the game
        void chkprev();                     //Check previous input
        int posibl(char*);                       //
        void kpcorct(const char*);          //keep letters that are in the answer
        void psltter(const char);           //Takes out a letter that is not in Game
        bool ckntuniq(const char*);         //checks if the input is not unique
        ~AISNS();                           //destructor
};


#endif /* AI_SNS_H */

