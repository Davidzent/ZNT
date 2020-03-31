/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on Sep 7, 2018, 12:42 AM
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
    int popu,days;   //starting population and days that will be tested
    float incrs,avrg;     //average daily population increase
    
    //Input or initialize values Here
    do{
        cout<<"please input the starting population greater than 1 "<<endl;
        cin>>popu;
    }while(popu<2);
    do{
        cout<<"enter the amount of days greater than 0 "<<endl;
        cin>>days;
    }while(days<1);
    do{
        cout<<"enter the average daily population increase"<<endl;
        cin>>avrg;
    }while(avrg<0);
    
    //Process/Calculations Here
    for(int i=1;i<=days;i++){
        incrs=avrg/popu;
        popu=popu+popu*incrs;
        cout<<"Day "<<i<<endl;
        cout<<"population = "<<popu<<endl;
                
    }
    //Output Located Here
    

    //Exit
    return 0;
}

