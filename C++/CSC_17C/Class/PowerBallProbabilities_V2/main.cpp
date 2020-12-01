/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on September 21, 2018, 4:55 PM
 * Purpose: CSC 17c Powerball Computations
 * http://www.powerball.com/powerball/pb_prizes.asp
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes
float lognPm(int,int);//Permutation without replacement
float lognCm(int,int);//Combination without replacement

//Execution Begins Here!
int main(int argc, char** argv) {
    //Declare and calculate Total Possibilities for each combination
    float nOmega=exp(lognCm(69,5)+lognCm(26,1));
    float n5notM=exp(lognCm(5,5)+lognCm(25,1));
    float n4M=exp(lognCm(5,4)+lognCm(64,1)+lognCm(1,1));
    float n4notM=exp(lognCm(5,4)+lognCm(64,1)+lognCm(25,1));
    float n3M=exp(lognCm(5,3)+lognCm(64,2)+lognCm(1,1));
    float n3notM=exp(lognCm(5,3)+lognCm(64,2)+lognCm(25,1));
    float n2M=exp(lognCm(5,2)+lognCm(64,3)+lognCm(1,1));
    float n2notM=exp(lognCm(5,2)+lognCm(64,3)+lognCm(25,1));
    float n1M=exp(lognCm(5,1)+lognCm(64,4)+lognCm(1,1));
    float n1notM=exp(lognCm(5,1)+lognCm(64,4)+lognCm(25,1));
    float n0M=exp(lognCm(5,0)+lognCm(64,5)+lognCm(1,1));
    float n0notM=exp(lognCm(5,0)+lognCm(64,5)+lognCm(25,1));
    
    //Output the headers
    cout<<"Power-ball Calculations"<<endl;
    cout<<"6 numbers to draw"<<endl;
    cout<<"5 from 69 without replacement"<<endl;
    cout<<"1 from 26"<<endl;
    cout<<fixed;
    //Calculate the Jackpot probability
    cout<<"Possible Combinations  = "<<setprecision(2)<<1.0f*nOmega<<endl;
    //Probability of winning jackpot
    cout<<"Probability Jackpot    = "<<setprecision(16)<<1/nOmega;
    cout<<" or 1:"<<setprecision(2)<<1.0f*nOmega<<endl;
    //Probability of 5 numbers but no Mega
    cout<<"Probability 5 no Mega  = "<<setprecision(16)<<n5notM/nOmega;
    cout<<" or 1:"<<setprecision(2)<<setw(12)<<1.0f*nOmega/n5notM<<endl;
    //Probability of 4 numbers with Mega
    cout<<"Probability 4 and Mega = "<<setprecision(16)<<n4M/nOmega;
    cout<<" or 1:"<<setprecision(2)<<setw(12)<<1.0f*nOmega/n4M<<endl;
    //Probability of 4 numbers no Mega
    cout<<"Probability 4 no Mega  = "<<setprecision(16)<<n4notM/nOmega;
    cout<<" or 1:"<<setprecision(2)<<setw(12)<<1.0f*nOmega/n4notM<<endl;
    //Probability of 3 numbers with Mega
    cout<<"Probability 3 and Mega = "<<setprecision(16)<<n3M/nOmega;
    cout<<" or 1:"<<setprecision(2)<<setw(12)<<1.0f*nOmega/n3M<<endl;
    //Probability of 3 numbers no Mega
    cout<<"Probability 3 no Mega  = "<<setprecision(16)<<n3notM/nOmega;
    cout<<" or 1:"<<setprecision(2)<<setw(12)<<1.0f*nOmega/n3notM<<endl;
    //Probability of 2 numbers with Mega
    cout<<"Probability 2 and Mega = "<<setprecision(16)<<n2M/nOmega;
    cout<<" or 1:"<<setprecision(2)<<setw(12)<<1.0f*nOmega/n2M<<endl;
    //Probability of 2 numbers no Mega
    cout<<"Probability 2 no Mega  = "<<setprecision(16)<<n2notM/nOmega;
    cout<<" or 1:"<<setprecision(2)<<setw(12)<<1.0f*nOmega/n2notM<<endl;
    //Probability of 1 number with Mega
    cout<<"Probability 1 and Mega = "<<setprecision(16)<<n1M/nOmega;
    cout<<" or 1:"<<setprecision(2)<<setw(12)<<1.0f*nOmega/n1M<<endl;
    //Probability of 1 number no Mega
    cout<<"Probability 1 no Mega  = "<<setprecision(16)<<n1notM/nOmega;
    cout<<" or 1:"<<setprecision(2)<<setw(12)<<1.0f*nOmega/n1notM<<endl;
    //Probability of 0 number with Mega
    cout<<"Probability 0 and Mega = "<<setprecision(16)<<n0M/nOmega;
    cout<<" or 1:"<<setprecision(2)<<setw(12)<<1.0f*nOmega/n0M<<endl;
    //Probability of 1 number no Mega
    cout<<"Probability 0 no Mega  = "<<setprecision(16)<<n0notM/nOmega;
    cout<<" or 1:"<<setprecision(2)<<setw(12)<<1.0f*nOmega/n0notM<<endl;
    

    //Exit stage right!
    return 0;
}

float lognPm(int n,int m){
    float sumnmm=0.0f;
    for(int i=n-m+1;i<=n;i++){
        sumnmm+=static_cast<float>(log(i));
    }
    return sumnmm;
}

float lognCm(int n,int m){
    float summ=0.0f;
    for(int i=1;i<=m;i++){
        summ+=static_cast<float>(log(i));
    }
    return lognPm(n,m)-summ;
}