/* 
 * File:   Game.h
 * Author: Guijosa, David
 *
 * Created on September 26, 2019, 10:11 AM
 */

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
using namespace std;

class Game{
    private:
        
        char *answer;                       //Code to find
                
    public:
        Game(int,int,int,bool);             //constructor
        bool chkletr();                     //checks if the Letter is in the range list
        bool chkletr(char);                 //checks if a letter is in the answer
        bool chkdupl(const char*,const int);//checks for duplicates in an array
        bool Status(){return status;}
        void crtans();                      //creates a new random answer    
        void chkinpt();                     //check number of correct input
        void play();                        //play the game
        void instans(char*);                //insert an answer
        ~Game();                            //destructor
             
    protected:
        char *letters;                      //letters to choose from
        char **Plyinpt;                     //player inputs
        bool duplict;                       //allow duplicates
        bool status;                        //if the game is still going
        int nInput;                         //This turns input
        int *nCorrct;                       //number of correct inputs
        int *nPerfc;                        //number of perfect inputs
        int CodeSz;                         //code size
        int atempts;                        //number of attempts
        int nLetter;                        //number of letters to choose from
        ofstream file;
        
};


#endif /* GAME_H */

