/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on May 4, 2015, 9:39 AM
 */

//System Libraries
#include <iostream>//Got to see what you get
#include <iomanip> //To make it look pretty
#include <cmath>   //For the sqrt function
#include <fstream>
using namespace std;

//User Libraries

//Global Constants

//Function Prototypes
void prmFact(int,ofstream &);

//Execution Begins Here!
int main(int argc, char** argv) {
    //Declare variables
    ofstream out("Prime.dat");
    int strt=9000,stop=9049;
    //Output the prime factors
    for(int i=strt;i<=stop;i++){prmFact(i,out);}
    //Exit Stage Right!!
    out.close();
    return 0;
}

void prmFact(int valInpt,ofstream &out){
    //Declare stream output
    //Declare variables
    const int SIZE=valInpt+1;
    bool prime[SIZE];
    //Initialize the prime factor array
    for(int i=2;i<SIZE;i++){
        prime[i]=true;
    }
    prime[0]=prime[1]=false;
    //Fill the Prime Array using the Erastothenes Sieve
    int n=sqrt(SIZE);
    for(int i=2;i<n;i++){
        if(prime[i]){
            //Inner Loop of sieve
            for(int j=2*i;j<SIZE;j+=i){prime[j]=false;}
        }
    }
    //Now output the prime factors
    int val=valInpt;
    cout<<endl<<val<<" = ";
    out<<endl<<val<<" = ";
    if(prime[val])cout<<"    Prime Number! ";
    for(int i=2;i<valInpt&&val>1;i++){
        if(prime[i]){
            //Is this a factor and count how many
            int count=0;
            while(val%i==0){val/=i;count++;}
            if(count!=0){
                cout<<setw(5)<<i<<"^"<<count<<" ";
                out<<setw(5)<<i<<"^"<<count<<" ";
            }
        }
    }
}