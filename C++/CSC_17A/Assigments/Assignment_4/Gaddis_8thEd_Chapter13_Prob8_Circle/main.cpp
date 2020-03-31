/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on March 22, 2018, 11:00 AM
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
using namespace std;

//User Libraries Here
#include "Circle.h"
//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    float radius;
    Circle circle;
    //Input or initialize values Here
    cout<<"Set radius "<<endl;
    cin>>radius;
    circle.setRad(radius);
    //Output Located Here
    cout<<"Circle Radius = "<<circle.getrad()<<endl;
    cout<<"Circle Diameter = "<<circle.getdmtr()<<endl;
    cout<<"Circle area = "<<circle.getarea()<<endl;
    cout<<"Circle Circumference = "<<circle.getcirc()<<endl;
    //Exit
    return 0;
}

