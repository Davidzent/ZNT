/* 
 * File:   main.cpp
 * Author: David Guijosa
 * Purpose: To prove Absorption law
 * Created on September 17, 2019, 11:55 AM
 */

#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

//Functions

int main(int argc, char** argv) {
    //declare variables
    cout<<"p q p||(p&&q) p&&(p||q)"<<endl;
    //Calculations
    for(int p=1;p>=0;p--){
        for(int q=0;q<2;q++){
            //output/display
            cout<<(p?"T ":"F ")
                <<(q?"T    ":"F    ")
                <<(((p?(p?1:(q?1:0)):0))?"T         ":"F         ")
                <<(p?"T":p?(q?"T":"F"):"F")
                    <<endl;
            
        }
    }
    //exit
    return 0;
}