/* 
 * File:   main.cpp
 * Author: Guijosa. David
 * Created on Sep 6, 2018, 9:27 AM
 * Purpose:  
 */
//System Libraries Here
#include <iostream>

using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    unsigned int a;
    
    //Output Located Here
    cout<<"Enter the number of books you have purchased --> ";
    cin>>a;
    if (a>=0&a<=3){
        switch (a){
            case(0):{
                cout<<"you have awarded 0 points this month"<<endl;
            break;}
            case(1):{
                cout<<"you have awarded 5 points this month"<<endl;
            break;}
            case(2):{
                cout<<"you have awarded 15 points this month"<<endl;
            break;}
            case(3):{
                cout<<"you have awarded 30 points this month"<<endl;
            break;}}}
    else {if (a>=4)
                cout<<"you have awarded 50 points this month"<<endl;
           }


    //calculations 
    
    //Output Located Here
    
    //Exit
    return 0;
}
