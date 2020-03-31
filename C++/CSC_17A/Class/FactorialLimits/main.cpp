/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on May 4, 2015, 2:09 PM
 */

//System Libraries
#include <cmath>
#include <iostream>
#include <iomanip>
using namespace std;

//Function Prototypes
double logSum(int);
void display(double);
void display2(double);

int main(int argc, char** argv) {
    //Declare variables
    cout<<setprecision(7)<<fixed<<showpoint;
    for(int i=1;i<200;i++){
        double result=logSum(i);
        cout<<setw(3)<<i<<"! = 10^("<<setw(11)<<result<<")  = ";
        display(result);
        display2(result);
    }
    //Exit stage right
    return 0;
}

void display2(double log10Sum){
    double log2base=log10Sum/log10(2);
    int int2LgSm=log2base;
    double frac=pow(2,log2base-int2LgSm);
    cout<<setw(3)<<"  =    "<<frac<<" x 2^"<<setw(4)<<int2LgSm<<endl;
}

void display(double log10Sum){
    int intLgSm=log10Sum;
    double frac=pow(10,log10Sum-intLgSm);
    cout<<setw(11)<<frac<<" x 10^"<<setw(3)<<intLgSm;
}

double logSum(int range){
    //Declare sum variable
    double sum=0;
    //Take sum of all the logs
    for(int i=1;i<=range;i++){
        sum+=log10(i);
    }
    return sum;
}


