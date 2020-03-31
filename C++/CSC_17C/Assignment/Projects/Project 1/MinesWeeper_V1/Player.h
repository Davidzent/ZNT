/* 
 * File:   player.h
 * Author: David guijosa
 *
 * Created on November 23, 2018, 2:24 PM
 */
#ifndef PLAYER_H
#define PLAYER_H
#include "AbsPlayer.h"
#include <iostream>
class Player:AbsPlyr{
    private:
        float points; //points of the player
    public:
        Player();   //default constructor
        bool isalive(char)const;   //is the player alive/from abstract class
        float gtpoint()const;      //returns the amount of points that a player 
                                   //has
        void operator ++();        //increase the player points
        void operator +=(int);     //increase the players points after 
                                   //wining a game
};
#endif /* PLAYER_H */