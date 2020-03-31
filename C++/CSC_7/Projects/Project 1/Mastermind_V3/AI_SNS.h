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
        int  *pnts;         //Points to give AI
        int  *psleter;      //different position for letters
        int   psbltr;       //number of possible letters
        void start();       //initialize the Arrays     
        
    public:
        AISNS (int nletter,int CodeSz,int atempts,bool duplict) 
        :Game(nletter,CodeSz,atempts,duplict){start();}     //Copy constructor + Initialize other arrays
        void play();                        //Play the array in the game
        void ctdbinpt();                    //Create a lineal input
        void crtRinpt();                    //Creates a random input based on previous inputs 
        void kpcorct(const char*);          //keep letters that are in the answer
        void psltter(const char);           //Takes out a letter that is not in Game
        bool ckntuniq(const char*);         //checks if the input is not unique
        bool checknt(const char);           //Check that a letter is in the letters to choose from
        bool ntlstinpt();                   //checks that the input created is not the same as the last ones
        ~AISNS();                           //destructor
};


#endif /* AI_SNS_H */

