/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on August 31, 2020, 1:06 PM
 */

#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    int coins=16;
    int loops=9;
    int h=0;
    int t=0;
    
    
    for(int i=0;i<loops;i++){
        h=0;
        t=0;
        for(int i=0;i<coins;i++){
           if(rand()%6<3)h++;
           else t++;
        }
        cout<<"Round #"<<i+1<<": "<<endl;
        cout<<"tails: "<<t<<"\theads: "<<h<<endl;
    }
    return 0;
}

