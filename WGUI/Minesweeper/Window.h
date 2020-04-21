
/* 
 * File:   Window.h
 * Author: david
 *
 * Created on April 19, 2020, 2:48 PM
 */

#ifndef WINDOW_H
#define WINDOW_H
class Window{
public:
    void open(int,int);         //open a cell
    void mark(int,int);         //Flag or unflag a cell
    void draw();                //Draws to the window
};


#endif /* WINDOW_H */

