/* 
 * File:   Show Map.h
 * Author: David Guijosa
 *
 * Created on November 15, 2018, 11:41 AM
 */

#ifndef SHOW_MAP_H
#define SHOW_MAP_H
#include "Class Map.h"
class HIDE : public MAP{
    private:
        char **map;
    public:
        HIDE();
        HIDE(int,int);
        void reveal(int,char);
        void reveal0(int,char);
        void fillmap();
};



#endif /* SHOW_MAP_H */

