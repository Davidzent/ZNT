/* 
 * File:   main.cpp
 * Author: David Guijosa
 * Created on SEP 5th, 2019, 8:35 AM
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//Global Constants

//Function Prototypes
char rndDgit();
void prpLuhn(char[],int);
void Luhn(char[],int);

int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    const int SIZE=12;
    char crdCard[SIZE]="cout<<crdCard<<endl;";
    //Prepare for Luhn encoding
    cout<<"A random number created in Prep for Luhn Digit"<<endl;
    prpLuhn(crdCard,SIZE-2);
    //Output the preLuhn credit card
    cout<<crdCard<<endl;
    //Now create a function that fills the last digit
    Luhn(crdCard,SIZE-2);
    //using the Luhn Algorithm
    cout<<"The random number with Luhn Encoding, Output Here!"<<endl;
    cout<<crdCard<<endl;
    //Exit Stage Right
    return 0;
}
void Luhn(char Cardn[],int n){
    int sum[n+1];
    char temp[n];
    sum[n]=0;
    for(int i=0;i<n;i++){
        temp[i]=Cardn[i];
    }
    for(int i=0;i<n;i++){
        temp[i]-=48;
        if(i%2==1)temp[i]*=2;
        sum[i]=temp[i]%10+temp[i]/10;
        sum[n]+=sum[i];
    }
    sum[n]*=9;
    sum[n]%=100;
    sum[n]%=10;
    Cardn[n]=sum[n]+48;
    
}
void prpLuhn(char cc[],int n){
    //Create a random cc in prep for Luhn checksum
    for(int i=0;i<n;i++){
        cc[i]=rndDgit();
    }
    //Put null terminator at the end
    for(int i=n;i<=n+1;i++){
        cc[i]='\0';
    }
}

char rndDgit(){
    return rand()%10+48;
}



