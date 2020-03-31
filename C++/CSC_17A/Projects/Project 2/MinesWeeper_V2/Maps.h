/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Maps.h
 * Author: rcc
 *
 * Created on November 21, 2018, 12:39 PM
 */

#ifndef MAPS_H
#define MAPS_H
class MAP{
    private:
        char **map;
        char **index;
        int row;
        int col;
        int nmines;
    public:
        MAP();
        MAP(int,int);
        void isalive();
        void points();
        void setrow(int);
        void setcol(int);
        void setnmin(int);
        int getcol()const;
        int getrow()const;
        int getnmin()const;
        void shufle();
        void cntmine();
        void crtmaps();
        void reveal(int,char);
        void reveal0();
        bool alive(int,int);
        void prntmap();
        void prtindx();
        ~MAP();
};


#endif /* MAPS_H */

