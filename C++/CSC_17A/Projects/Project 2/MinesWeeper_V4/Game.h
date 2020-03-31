/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Game.h
 * Author: rcc
 *
 * Created on December 6, 2018, 2:01 PM
 */

#ifndef GAME_H
#define GAME_H

#include <cstdlib>
#include "Normal mode.h"
#include "Chronometric.h"

using namespace std;

template <class T>
class GAME{
    private:
        T game;
    public:
        GAME();
        void PLAY();
        
};

template <class T>
GAME<T>::GAME(){}
template <class T>
void GAME<T>::PLAY(){
    cout<<game;
    game.play();
}
#endif /* GAME_H */
