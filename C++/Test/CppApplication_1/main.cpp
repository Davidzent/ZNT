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
    int size=4;
    bool p[size];
    bool q[size];
    for(int i=0;i<size;i++){
        //Declare p
        if(i<2)p[i]=true;           
        else p[i]=false;
        //Declare q
        if(i%2==0)q[i]=true;        
        else q[i]=false;
    }
    cout<<"p q ~p ~q"<<endl;
    for(int i=0;i<size;i++){
        cout<<p[i]<<" "<<q[i]<<"  "<<(!p[i])<<"  "<<(!q[i])<<endl;
    }
    return 0;
}

