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
float C2X(float);
float S2X(float);
float SX(float);
float CX(float);
//main
int main(int argc, char** argv) {
    int val=12;
    /*int loops=50;
    for(int i=1;i<=loops;i++){
        for(int j=1;j<=4;j++){
            
        }
    }*/
    cout<<fixed;
    cout<<"C2X : "<<C2X(1)<<endl;
    cout<<"C2X F: "<<CX(1)*SX(1)/2<<endl;
    return 0;
}
float C2X(float X){
    if(X==0)return 1;
    return((7*X/8)*S2X(X-1));
} 
/* 
float S2X(float x){
    if(x==0)return 1;
    return ((x/(x+1))*C2X(x-1));
}*/
float SX(float X){
    return (1+X*X/2);
}
float CX(float X){
    return (1/X+X/6);
}