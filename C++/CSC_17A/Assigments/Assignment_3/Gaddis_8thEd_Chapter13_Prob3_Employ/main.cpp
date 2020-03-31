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
#include "Workers.h"
//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    string name,adress,position;
    int ID;
    const int SIZE=3;
    worker nwork(SIZE);
    //Input or initialize values Here
    for(int i=0;i<SIZE;i++){
        cout<<"Enter employee name"<<endl;
        cin>>name;
        cout<<"Enter the department"<<endl;
        cin>>adress;
        cout<<"Enter his/her position"<<endl;
        cin>>position;
        cout<<"Enter the ID"<<endl;
        cin>>ID;
        Employ info(name,position,adress,ID);
        nwork.setInfo(info,i);
    }
    //Output Located Here
    nwork.prntinfo();
    //Exit
    return 0;
}