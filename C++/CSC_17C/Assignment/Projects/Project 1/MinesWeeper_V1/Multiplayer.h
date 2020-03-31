/* 
 * File:   Multiplayer.h
 * Author: Guijosa David
 *
 * Created on December 10, 2018, 10:11 AM
 */

#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H
#include "Normal mode.h"
class multy:Normal{
    private: 
        Player *players;    //array of players
        int nplayrs;        //number of players
        int winer;          //helps to find a winer
    public:
        //constructors
        multy();
        multy(int);
        //functions
        void stnplyr(int);
        void repeat();
        void fndwiner();
        //game information
        void run();
        void menu();
        //destructor
        ~multy();
};

#endif /* MULTIPLAYER_H */