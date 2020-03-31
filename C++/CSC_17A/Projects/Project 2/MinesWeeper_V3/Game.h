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

#ifndef GAME_H
#define GAME_H
#include "Maps.h"
#include "Player.h"
using namespace std;

class GAME{
    private:
        Player ply;
        MAP maps;
        int mode;
        string winlose;
    public:
        GAME();
        void rules()const;
        void play();
        friend ostream &operator<<(ostream &,const GAME &);
};


#endif /* GAME_H */