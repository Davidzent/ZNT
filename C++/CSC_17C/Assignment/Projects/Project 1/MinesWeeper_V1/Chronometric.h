/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   player.h
 * Author: David guijosa
 *
 * Created on November 23, 2018, 2:24 PM
 */

#ifndef CHRONOMETRIC_H
#define CHRONOMETRIC_H
#include <iostream>

using namespace std;
#include "Normal mode.h"

class chrono{       //chronometric game mode
     protected:
        Player ply; //player points & live
        MAP maps;   //map
        int mode;   //difficulty mode
        string winlose;  //if the player win or lose
        int timest;     //time that game start
        int toend;      //time for the game to end
    public:
        chrono();           //constructor
        void rules()const;  //rules of the game
        void play();        //play the game
        friend ostream &operator<<(ostream &,const chrono &); //used to output 
                                                              //menu
};
#endif /* CHRONOMETRIC_H */