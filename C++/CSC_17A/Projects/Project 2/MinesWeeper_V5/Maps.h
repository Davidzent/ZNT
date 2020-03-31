/* 
 * File:   player.h
 * Author: David guijosa
 *
 * Created on November 23, 2018, 2:24 PM
 */

#ifndef MAPS_H
#define MAPS_H
class MAP{
    private:
        char **map;         //map of the game
        char **index;       //index to print
        int row;            //rows of map
        int col;            //columns of map
        int nmines;         //number of mines in the map
        int moves;          //number of moves for the game to end
    public:
        MAP();              //default constructor
        MAP(int,int);       //constructor with rows and columns
        void setrow(int);   //set the value of rows
        void setcol(int);   //set the value of columns
        void setnmin(int);  //set the number of mines
        bool aredy(int,char);   //knows if a coordinate have already been inputed
        char getcord(int,char)const; //get a coordinate in the map
        int getcol()const;      //get the value of columns
        int getrow()const;      //get the value of rows
        int getnmin()const;     //get the number of mines
        int gtmoves()const;     //returns the number of moves
        void shufle();          //shuffle the map mines 
        void cntmine();         //counts the number of mines around a non mine
        void crtmaps();         //creates the maps
        void reveal(int,char);  //reveal a part of the map
        void reveal0(int,char); //if the coordinate is 0 it will reveal all its 
                                //surroundings
        void prntmap();         //print the map
        void prtindx();         //prints the index
        ~MAP();                 //destructor (deletes dynamic arrays)
};
#endif /* MAPS_H */