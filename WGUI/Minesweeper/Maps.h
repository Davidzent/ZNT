/* 
 * File:   player.h
 * Author: David guijosa
 *
 * Created on November 23, 2018, 2:24 PM
 */

#ifndef MAPS_H
#define MAPS_H
#include "painter.hpp"
#include "Window.h"

class MAP:Window{
    private:
        enum State { CLOSED, OPENED, FLAG };
        struct Cell{
            State state;    
            char value;    
            bool hasMine;   
        };
        Cell **field_;
        int row;                //rows of map
        int col;                //columns of map
        int nmines;             //number of mines in the map
        int moves;              //number of moves for the game to end
    public:
        void prntmap();
        MAP();                  //default constructor
        MAP(int,int);           //constructor with rows and columns
        //Cell getcord(int,int);   //get a coordinate in the map
        void setrow(int);       //set the value of rows
        void setcol(int);       //set the value of columns
        void setnmin(int);      //set the number of mines
        void shufle();          //shuffle the map mines 
        void cntmine();         //counts the number of mines around a non mine
        void crtmap();          //creates the maps
        void open(int,int);     //open a cell
        void mark(int,int);     //Flag or unflag a cell
        void draw();            //Draws the map into a window
        int getcol()const;      //get the value of columns
        int getrow()const;      //get the value of rows
        int getnmin()const;     //get the number of mines
        int gtmoves()const;     //returns the number of moves
        ~MAP();                 //destructor (deletes dynamic arrays)
};
#endif /* MAPS_H */