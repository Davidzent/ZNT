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
class Player : AbsPlyr{
    private:
        float points;
    public:
        Player();
        bool isalive(char)const;  
        float gtpoint()const;
        void operator ++();
        void operator +=(int);
};


#endif /* PLAYER_H */