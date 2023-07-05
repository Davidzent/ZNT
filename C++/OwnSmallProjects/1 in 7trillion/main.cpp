/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on December 21, 2020, 7:07 PM
 */

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    long long int sevTrillion=7300000000000;
    int n=log2(sevTrillion);
    unsigned long long int attempts=0;
    for(int i=0;i<n;i++){
        if(rand()%2!=0){
            i=0;
        }
        attempts++;
        if(attempts==1446744073709551615)i=n;
        if(attempts%1000000000==0)cout<<"There has been "<<attempts<<" attempts"<<endl;
    }
    cout<<attempts;
    return 0;
}