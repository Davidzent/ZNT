/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: rcc
 *
 * Created on November 21, 2018, 2:45 PM
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

