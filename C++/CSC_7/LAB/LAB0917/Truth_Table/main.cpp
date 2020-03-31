/* 
 * File:   main.cpp
 * Author: David Guijosa
 * Purpose: Truth Table
 * Created on September 12, 2019, 11:55 AM
 */

#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

//Functions

int main(int argc, char** argv) {
    //declare variables
    cout<<"p q ~p ~q p&&q p||q p^q p^q^q p^q^p !(p&&q) !p||!q !(p||q) !p^!q"<<endl;
    //Calculations
    for(int p=1;p>=0;p--){
        for(int q=0;q<2;q++){
            //output/display
            cout<<(p?"T ":"F ")
                <<(q?"T  ":"F  ")
                <<(!p?"T  ":"F  ")
                <<(!q?"T  ":"F  ")
                <<(p?(q?"T    ":"F    "):"F    ")
                <<(p?"T    ":q?"T    ":"F    ")
                <<(p^q?"T    ":"F    ")
                <<(p^q^q?"T     ":"F     ")
                <<(p^q^p?"T      ":"F      ") 
                <<(!((p?(q?1:0):0))?"T       ":"F       ")
                <<(!p?"T     ":!q?"T     ":"F     ")
                <<(!((p?1:(q?1:0)))?"T       ":"F       ")
                <<((!p^!q)?"T":"F")
                    <<endl;
            
        }
    }


    //exit

    return 0;
}
