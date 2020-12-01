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
double lognPm(int,int);//Permutation without replacement
double lognCm(int,int);//Combination without replacement
double lognCr(int,int);//Combination without replacement

//Execution Begins Here!
int main(int argc, char** argv) {
    //Declare and calculate Total Possibilities for each combination
    double n=exp(lognCr(10,4));
    double n3=exp(lognPm(4,3)+lognPm(6,1));
    double n2=exp(lognPm(4,2)+lognPm(6,2));
    double n1=exp(lognPm(4,1)+lognPm(6,3));
    double n0=exp(lognPm(4,0)+lognPm(6,4));
    
    //Output the headers
    cout<<"Mastermind"<<endl;
    cout<<"4 numbers to pick"<<endl;
    cout<<"4 from 10 without replacement"<<endl;

    cout<<fixed;
    //Calculate the Jackpot probability
    cout<<"Possible Combinations  = "<<setprecision(2)<<1.0f*n<<endl;
    //Probability of winning jackpot
    cout<<"Probability of all    = "<<setprecision(16)<<1/n;
    cout<<" or 1:"<<setprecision(2)<<1.0f*n<<endl;
    //Probability of 5 numbers but no Mega
    cout<<"Probability 3  = "<<setprecision(16)<<n3/n;
    cout<<" or 1:"<<setprecision(2)<<setw(12)<<1.0f*n/n3<<endl;
    cout<<"Probability 2  = "<<setprecision(16)<<n2/n;
    cout<<" or 1:"<<setprecision(2)<<setw(12)<<1.0f*n/n2<<endl;
    cout<<"Probability 1  = "<<setprecision(16)<<n1/n;
    cout<<" or 1:"<<setprecision(2)<<setw(12)<<1.0f*n/n1<<endl;
    cout<<"Probability 0  = "<<setprecision(16)<<n0/n;
    cout<<" or 1:"<<setprecision(2)<<setw(12)<<1.0f*n/n0<<endl;


    

    //Exit stage right!
    return 0;
}

double lognPm(int n,int m){
    double sumnmm=0.0;
    for(int i=n-m+1;i<=n;i++){
        sumnmm+=static_cast<double>(log(i));
    }
    return sumnmm;
}

double lognCm(int n,int m){
    double summ=0.0;
    for(int i=1;i<=m;i++){
        summ+=static_cast<double>(log(i));
    }
    return lognPm(n,m)-summ;
}
double lognCr(int n,int m){
    double summ=0.0;
    for(int i=1;i<=m;i++){
        summ+=static_cast<double>(log(n));
    }
    return summ;
}