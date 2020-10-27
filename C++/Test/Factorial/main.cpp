/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on October 15, 2020, 12:46 PM
 */
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;

/*
 * 
 */
double fact(int );
int main(int argc, char** argv) {
    int n;
    cout<<"Enter a number to factorize: ";
    cin>>n;
    
    cout<<setprecision(0);
    for(int j=2;j<=n;j++){
        double facN=1;
        //double factfnc=static_cast<double>(pow(10,fact(n)));
        for(int i=2;i<=j;i++){
            facN*=i;
        }
        //cout<<"Factorial with function of 5 = "<<factfnc<<endl;
        cout<<"Factorial with loop of "<<setw(3)<<j<<"     = "<<right<<setw(10)<<facN<<endl;
    }
    return 0;
}
double fact(int n){
    double sumn=0.0f;
    for(int i=1;i<=n;i++){
        sumn+=static_cast<double>(log10(i));
    }
    return sumn;
}
