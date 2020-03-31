/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on November 21, 2018, 1:11 PM
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries
#include "Link.h"

//Functions associated with lists


int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Create 2 link pointers
    Link *link1, *link2;
    
    //Dynamically allocate memory
    link1=new Link;
    link2=new Link;
    
    //Fill with Data
    link1->data=rand()%90+10;
    link2->data=rand()%90+10;
    
    //Hook up the links
    link1->node=link2;
    link2->node=NULL;

    return 0;
}