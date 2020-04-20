#pragma once

#include "Maps.h"

class Game:Window{
private:
    MAP temp;
public:
    Game();
    void open(int,int);             //open a cell
    void mark(int,int);             //Flag or unflag a cell
    void draw();                    //Draws the map into a window
    int getW(){return temp.getcol();}
    int getH(){return temp.getrow();}
};
