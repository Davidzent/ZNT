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
        char **map;
        char **index;
        int row;
        int col;
        int nmines;
        int moves;
    public:
        MAP();
        MAP(int,int);
        void setrow(int);
        void setcol(int);
        void setnmin(int);
        bool aredy(int,char);
        char getcord(int,char)const;
        int getcol()const;
        int getrow()const;
        int getnmin()const;
        int gtmoves()const;
        void shufle();
        void cntmine();
        void crtmaps();
        void reveal(int,char);
        void reveal0(int,char);
        void prntmap();
        void prtindx();
        void rr(int,char);
        ~MAP();
};


#endif /* MAPS_H */