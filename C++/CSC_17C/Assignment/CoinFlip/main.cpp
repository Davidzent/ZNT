/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on April s18, 2019, 11:00 AM
 * Purpose: 
 */

//System Libraries Here
#include <cmath>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
float lognPm(int,int);//Permutation without replacement
float lognCm(int,int);//Combination without replacement

//Program Execution Begins Here
int main(int argc, char** argv) {
    //setRandom Seed
    srand(static_cast<unsigned int>(time(0)));   
    //Declare all Variables Here    
    float BNcoinX=exp(lognCm(4,3));
    float BNcoinY=exp(lognCm(4,3));
    float STcoinX=0,STcoinY=0,STcoinH=0,STcoinT=0;
    int flips=10000;
    int rnd=0,rnd2=0;
    //Input or initialize values Here
    for(int i=0;i<flips;i++){
        rnd=rand()%2+1;
        rnd2=rand()%5+1;
        if(rnd2<4)STcoinH++;
        else STcoinT++;
        if(rnd==1)STcoinX++;
        else STcoinY++;
    }
    //Process/Calculations Here
    
    //Output Located Here
    cout<<fixed;
    cout<<"Normal Coin"<<endl;
    cout<<"You get Tail = "<<setprecision(0)<<STcoinX<<" Out of 10000 an average of = "
            <<setprecision(2)<<STcoinX/flips<<endl;
    cout<<"You get head = "<<setprecision(0)<<STcoinY<<" Out of 10000 an average of = "
            <<setprecision(2)<<STcoinY/flips<<endl;
    cout<<"The possibility of getting 3 times tail and one time head is = "
            <<setprecision(2)<<1/BNcoinX<<" out of 4 flips"<<endl;
    cout<<"The possibility of getting 3 times head and one time head is = "
            <<setprecision(2)<<1/BNcoinY<<" out of 4 flips"<<endl;
    cout<<endl<<endl;
    
    cout<<"60% Head Coin"<<endl;
    cout<<"You get Tail = "<<setprecision(0)<<STcoinT<<" Out of 10000 an average of = "
            <<setprecision(2)<<STcoinT/flips<<endl;
    cout<<"You get head = "<<setprecision(0)<<STcoinH<<" Out of 10000 an average of = "
            <<setprecision(2)<<STcoinH/flips<<endl;
    //Exit
    return 0;
}
//9519418408

float lognPm(int n,int m){
    double sumnmm=0.0;
    for(int i=n-m+1;i<=n;i++){
        sumnmm+=static_cast<float>(log(i));
    }
    return sumnmm;
}

float lognCm(int n,int m){
    float summ=0.0;
    for(int i=1;i<=m;i++){
        summ+=static_cast<float>(log(i));
    }
    return lognPm(n,m)-summ;
}