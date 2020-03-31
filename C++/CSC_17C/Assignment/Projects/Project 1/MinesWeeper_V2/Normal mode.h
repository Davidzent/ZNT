/* 
 * File:   player.h
 * Author: David guijosa
 *
 * Created on November 23, 2018, 2:24 PM
 */

#ifndef NORMAL_MODE_H
#define NORMAL_MODE_H
#include "Maps.h"
#include "Player.h"
using namespace std;

class Normal{
    private:
        Player ply; //player live and points
    protected:
        MAP maps;   //map
        int mode;   //difficulty
        string winlose; //game is a lose or a win
    public:
        Normal();   //default constructor
        void rules()const;  //rules of normal mode game
        void play();        //run the game
        int getmode()const; //gets the difficulty of the mode
        string gtstatu()const;  //returns the stage of the game
        friend ostream &operator<<(ostream &,const Normal &); 
                                                 //prints the menu of the game
};
#endif /* GAME_H */