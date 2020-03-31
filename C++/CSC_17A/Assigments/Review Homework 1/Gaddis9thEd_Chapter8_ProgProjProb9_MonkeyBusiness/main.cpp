/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on Sep 6 , 2018, 10:00 AM
 * Purpose: 
 */

//System Libraries Here
#include <iostream>
using namespace std;
//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions
const int DAYSWK=7;
//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int MONKEY=3;
    int arr[MONKEY][DAYSWK];
    //Input or initialize values Here
    for (int i=0;i<MONKEY;i++){
        for(int j=0;j<DAYSWK;j++){
            cout<<"enter the number of pounds for monkey # "<<i+1<<" in day "<<
                    j+1<<endl;
            cin>>arr[i][j];
        }
    }
    
    //Process/Calculations Here
    cout<<"    Days of week"<<endl<<"   1 2 3 4 5 6 7 "<<endl;
    for (int i=0;i<MONKEY;i++){
        cout<<i+1<<"| ";
        for(int j=0;j<DAYSWK;j++){
            cout<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    
    //Output Located Here
    

    //Exit
    return 0;
}

