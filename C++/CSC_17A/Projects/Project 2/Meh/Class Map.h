/* 
 * File:   Class Map.h
 * Author: David Guijosa
 *
 * Created on November 15, 2018, 11:19 AM
 */

#ifndef CLASS_MAP_H
#define CLASS_MAP_H
#include <iostream>
#include "Show Map.h"
using namespace std;
class MAP{
    private:  
        char **map;
        bool ctmap=false;
    public:
        MAP();
        MAP(int,int);
        int getrow();
        int getcol();
        char getval(int,char);
        void setcol(int);
        void setrow(int);
        void crtmap();
        void flmap(int);
        void getcord(int,char);
        void shufle();
        void cntmine();
        friend istream &operator >>(istream &, MAP &);
        friend ostream &operator <<(ostream&,MAP&);
        ~MAP();
    protected:
        int row;
        int col;
};


#endif /* CLASS_MAP_H */

