/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on August 30, 2020, 4:26 PM
 */

#include <cstdlib>
#include <iostream>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    int size=4;
    int a[size];
    int temp[size];
    long long int l=1000000000;
    for(int i=0;i<size;i++){
        a[i]=0;
    }
    for(long long int i=0;i<l;i++){
        temp[0]=rand()%30;
        temp[1]=rand()%30;
        temp[2]=rand()%30;
        temp[3]=rand()%30;
        
        if(temp[0]==temp[1]&&temp[1]==temp[2]&&temp[3]==temp[2]&&temp[4]==temp[1]) a[0]++;
    }
    cout<<a[0]<<" P = "<<a[0]/l*100.0f<<endl;
    return 0;
}

