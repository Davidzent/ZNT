/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on November 4, 2020, 6:14 PM
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

/*
 * 
 */
double SX(double);
double S2X(double);
double CX(double);
double C2X(double);
double C2XT(double);  //faster version of C2X + error
double S2XT(double);  //faster version of S2X + error

int main(int argc, char** argv) {
    cout<<fixed<<showpoint<<setprecision(12);
    double test=0.00001; 
    double test2=1/test;
    cout<<"Testing functions for value: "<<test<<endl;
    cout<<"The values for S(2X) = "<<endl<<S2X(test)<<endl; //4 N 4
    cout<<"The values for C(2X) = "<<endl<<C2X(test)<<endl; //12 N 12
    cout<<"Testing T functions for value: "<<test<<endl;
    cout<<"The values for S(2X) = "<<endl<<S2XT(test)<<endl;
    cout<<"The values for C(2X) = "<<endl<<C2XT(test)<<endl;
    //cout<<"Testing the inverse of the value to test - Inverse: "<<test2<<endl;
    //cout<<"The values for S(2X) = "<<S2X(test2)<<endl;
    //cout<<"The values for C(2X) = "<<C2X(test2)<<endl;
    return 0;
}
double SX(double n){
    static int x=1;
    return 1+(n*n)/2.0;
}
double S2X(double n){
    static const double tol=0.000001f;
    n/=2.0f;
    if(n>-tol&&n<tol){
        double cx=CX(n);
        double sx=SX(n);
        
        return (cx*cx*sx*sx/(cx*cx-sx*sx));
    }
    double c2x=C2X(n);
    double s2x=S2X(n);
    return (c2x*c2x*s2x*s2x/(c2x*c2x-s2x*s2x));
}
double CX(double n){
    static int x=1;
    return 1/n+n/6;
}
double C2X(double n){
    static const double tol=0.000001;
    n/=2.0f;
    if(n>-tol&&n<tol){
        return CX(n)*SX(n);
    }
    return C2X(n)*S2X(n)/2;       
}
double C2XT(double n){
    static const double tol=0.000001;
    int temp=1;
    n/=2;
    while(n>=tol||n<=-tol){
        n/=2;
        temp++;
    }
    double temp2=pow(2,temp-1);
    double cx=CX(n);
    double cxt=cx/temp2;
    return cxt;
}
double S2XT(double n){
    static const double tol=0.000001;
    int temp=1;
    double cxt=C2XT(n);
    n/=2;
    while(n>=tol||n<=-tol){
        n/=2;
        temp++;
    }
    double temp2=pow(2,temp);
    double sx=pow(SX(n),temp2);
    double cx=pow(CX(n),temp2);    
    double sxt=sx*cx/((cx-sx));
    return sxt;
}