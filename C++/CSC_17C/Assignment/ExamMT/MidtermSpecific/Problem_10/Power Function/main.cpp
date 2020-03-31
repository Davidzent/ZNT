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
float Power(int,int);
//main
int main(int argc, char** argv) {
    int loops=50;
    for(int i=1;i<=loops;i++){
        for(int j=1;j<=4;j++){
            cout<<i<<"^"<<j<<" = "<<Power(i,j)<<endl;
        }
    }
    
    return 0;
}
float Power(int base,int power) {
    if(power==0)return 1;
    return exp2(log2(base)+log2(Power(base,power-1)));
} 
