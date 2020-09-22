/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on September 8, 2020, 1:19 PM
 */
#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    int size=8;
    bool p[size];
    bool q[size];
    bool r[size];
    for(int i=0;i<size;i++){
        //Declare p
        if(i<size/2)p[i]=true;           
        else p[i]=false;                 
        //Declare q
        if(i%(size/2)<2)q[i]=true;        
        else q[i]=false;
        if(i%2==0)r[i]=true;
        else r[i] = false;
    }
    cout<<"p q r ((p||q)||(p&&r))   ((p||q)&&r)"<<endl;
    for(int i=0;i<size;i++){
        cout<<p[i]<<" "<<q[i]<<"  "<<(r[i])
                <<"      "<<((p[i]||q[i])||(p[i]&&r[i]))
                <<"                "<< ((p[i]||q[i])&&r[i])<<endl;
    }
    return 0;
}

