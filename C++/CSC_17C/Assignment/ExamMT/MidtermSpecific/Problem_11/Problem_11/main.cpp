/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on April 30, 2019, 8:31 PM
 */

//System libraries
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

//Functions
float G2X(int);
float GX(int);
//main
int main(int argc, char** argv) {
    int val=12;
    /*int loops=50;
    for(int i=1;i<=loops;i++){
        for(int j=1;j<=4;j++){
            
        }
    }*/
    cout<<fixed;
    cout<<"G2X : "<<G2X(val)<<endl;
    cout<<"GX : "<<GX(val)<<endl;
    cout<<"G2X formula : "<<((2*GX(val))/1+GX(val)*GX(val))<<endl;
    return 0;
}
float G2X(int X){
    return((2*GX(X))/1+GX(X)*GX(X));
} 
float GX(int x){
    return (x-((x*x*x)/6.f));
}
