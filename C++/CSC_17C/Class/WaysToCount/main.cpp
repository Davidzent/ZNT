/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on September 21, 2020, 4:55 PM
 * Purpose: CSC 17c preparation for analysis
 *          Counting -> permutations/combinations
 *          with or without replacement
 * Note:  Permutations are ordered, Combinations are unordered.
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes
float logPnm(int,int);//Permutation with replacement
float lognPm(int,int);//Permutation without replacement
float logCnm(int,int);//Combination with replacement
float lognCm(int,int);//Combination without replacement
void  compare(int,int, float &,float &,float &,float &);

//Execution Begins Here!
int main(int argc, char** argv) {
    //Declare variables
    int nMin=2,nMax=26;
    float prep,pnorep,crep,cnorep;
    
    //Output the headers
    cout<<"P      -> Permutation(Order Matters)"<<endl;
    cout<<"C      -> Combination(Order does not matter)"<<endl;
    cout<<"Rep    -> with replacement"<<endl;
    cout<<"no Rep -> no replacement"<<endl;
    cout<<"N      -> Number of total elements"<<endl;
    cout<<"M      -> Number of elements to take from the total"<<endl<<endl;
    cout<<"  N  M          P Rep       P no Rep          C Rep            C no Rep"<<endl;
    cout<<"                  N^M      N!/(N-M)!    (N+M-1)!/((N-1)!M!)  N!/((N-M)!M!)"<<endl<<endl;
    
    //Loop
    for(int n=nMin;n<=nMax;n++){
        for(int m=0;m<=n;m++){
            //Calculate
            compare(n,m,prep,pnorep,crep,cnorep);

            //Output the result
            cout<<setw(3)<<n<<setw(3)<<m;
            cout<<setw(15)<<prep<<setw(15)<<pnorep;
            cout<<setw(15)<<crep<<setw(16)<<cnorep<<endl;
        }
        cout<<endl;
    }

    //Exit stage right!
    return 0;
}

float logPnm(int n,int m){
    return static_cast<float>(m*log(n));
}

float lognPm(int n,int m){
    float sumn=0.0f;
    for(int i=n-m+1;i<=n;i++){
        sumn+=static_cast<float>(log(i));
    }
    return sumn;
}

float logCnm(int n,int m){
    return lognCm(n+m-1,m);
}

float lognCm(int n,int m){
    float summ=0.0f;
    for(int i=1;i<=m;i++){
        summ+=static_cast<float>(log(i));
    }
    return lognPm(n,m)-summ;
}

void  compare(int n,int m, float &Pnm,float &nPm,float &Cnm,float &nCm){
    Pnm=static_cast<float>(exp(logPnm(n,m)));
    nPm=static_cast<float>(exp(lognPm(n,m)));
    Cnm=static_cast<float>(exp(logCnm(n,m)));
    nCm=static_cast<float>(exp(lognCm(n,m)));
}