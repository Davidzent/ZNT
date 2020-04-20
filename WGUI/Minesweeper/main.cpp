/* File:   main.cpp
 * Author: Guijosa, David
 * Created on Nov 20, 2018, 11:00 AM
 * Purpose:  Minesweeper
 */

//System Libraries Here
#include <GL/glut.h>
#include <iostream>
using namespace std;

//User Libraries Here
#include "game.hpp"
#include "painter.hpp"

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions
Game game;
int WinX = game.getW() * Painter::CELL_WIDTH;       //Width of Windows
int WinY = game.getH() * Painter::CELL_HEIGHT;      //Height of Windows
    
//Function Prototypes Here
void display();
void mouse(int button, int state, int x, int y);

int main(int argc, char **argv){
    //Random seed generator
    //srand(static_cast<unsigned int>(time(0)));
    //Initialize Glut library and negotiate a session with the window system
    glutInit(&argc, argv);
    
    //creating top-level windows, subwindows, and overlays to determine the OpenGL display mode for the to-be-created window or overlay. 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    
    //Windows created by glutCreateWindow will be requested to be created with the current initial window position and size. 
    glutInitWindowSize(WinX, WinY);
    glutInitWindowPosition(100, 120);
    glutCreateWindow("MineSweeper");
    
    //specifies the red, green, blue, and alpha values
    glClearColor(0, 0, 0, 1);
    
    //set the current matrix mode
    glMatrixMode(GL_PROJECTION);
    
    //replaces the current matrix with the identity matrix.
    glLoadIdentity();
    
    //describe a transformation that produces a parallel projection. 
    glOrtho(0, WinY, WinX, 0, -1.0, 1.0);
    
    //set the display callback for the current window.
    glutDisplayFunc(display);
    //set the mouse callback for the current window.
    glutMouseFunc(mouse);
    
    //enters the GLUT event processing loop.
    glutMainLoop();

}

void display(){
    //set the bitplane area of the window to values previously selected by glClearColor
    glClear(GL_COLOR_BUFFER_BIT);
    
    //draw game board
    game.draw();
    
    //Perform a buffer swap on the layer in use for the current window. 
    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y){
    float ScaleX = glutGet(GLUT_WINDOW_WIDTH)/static_cast<float>(WinX);
    float ScaleY = glutGet(GLUT_WINDOW_HEIGHT)/static_cast<float>(WinY);
    //If mouse click
    if (state == GLUT_UP){
        switch (button){
            //Left mouse click
            case GLUT_LEFT_BUTTON:
                //Open Cell
                game.open(x / (Painter::CELL_WIDTH * ScaleX), y / (Painter::CELL_HEIGHT * ScaleY));
                break;
            //Right mouse click
            case GLUT_RIGHT_BUTTON:
                //Flag cell
                game.mark(x / (Painter::CELL_WIDTH * ScaleX), y / (Painter::CELL_HEIGHT * ScaleY));
                break;
        }
        //Mark the normal plane of current window as needing to be redisplayed.
        glutPostRedisplay();
    }
}