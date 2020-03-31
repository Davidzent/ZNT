/* 
 * File:   main.cpp
 * Author: David Guijosa
 * Created on SEP 26th, 2019, 8:35 AM
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>
using namespace std;

//Global Constants

//Function Prototypes
char rndDgit();                 //creates random char digit
void prpLuhn(char*,int,int);    //fills the card with random numbers
char Luhn(char*,int);           //returns the last value of the card
char* VISA(int&);               //Creates a VISA card
char* AEXPRES(int&);            //creates a American Express card
char* MASTERC(int&);            //creates a MasterCard
char* DISCVER(int&);            //creates a Discover card
char *genCC(int,int&);          //randomly creates a card
void prntcrd(char*,int);        //prints the card
void flipDig(char *,int);       //flips a digit
bool validCC(char *,int);       //Checks if the card is valid
void transpos(char*,int);       //transpose a random digit

int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    //declare variables
    int nloops=10000;           //number of loops
    int size;                   //cards number digits
    int valid=0;                //number of valid cards
    int invalid=0;              //number of invalid cards
    //Calculations
    for(int i=0;i<nloops;i++){
        //create a random type of card
        char* card=genCC(rand()%4,size);
        //flip one digit
        transpos(card,size);
        transpos(card,size);
        //counts the number of valid cards
        validCC(card,size)?valid++:invalid++;
        
        delete card;
    }
    //output
    cout<<"Valid number of cards = "<<valid<<endl;
    cout<<"Invalid number of cards = "<<invalid<<endl;
    //Exit Stage Right

    return 0;
}
void prpLuhn(char *cc,int n,int start){
    //Create a random cc in prep for Luhn checksum
    for(int i=start;i<n;i++){
        cc[i]=rndDgit();
    }
    //Put null terminator at the end
    for(int i=n;i<=n+1;i++){
        cc[i]='\0';
    }
}
char Luhn(char *Cardn,int n){
    char sum=0;
    char temp[n];
    for(int i=0;i<n;i++){
        temp[i]=Cardn[i];
    }
    for(int i=0;i<n-1;i++){
        temp[i]-=48;
        if(i%2==1){
            temp[i]*=2;
            if(temp[i]>9)temp[i]=temp[i]%10+temp[i]/10;
        }
        sum+=temp[i];
    }
    sum*=9;
    sum%=10;
    return (sum+48);
}

bool validCC(char *crd,int size){
    char luhn=Luhn(crd,size);
    if(luhn==crd[size-1])return true;
    return false;
}

char rndDgit(){
    return rand()%10+48;
}
char *genCC(int rnd,int &size){
    char*crdCard;
        switch(rnd){
            case 0:crdCard=VISA(size);break;
            case 1:crdCard=AEXPRES(size);break;
            case 2:crdCard=MASTERC(size);break;
            case 3:crdCard=DISCVER(size);break;
        }
    crdCard[size-1]=Luhn(crdCard,size);
    return crdCard;
}
void flipDig(char *crd,int size){
    int rnd=rand()%(size-1);
    crd[rnd]=rndDgit();
}

void prntcrd(char *crdCard,int size){
    cout<<endl;
    for(int i=0;i<size;i++){
        cout<<crdCard[i];
    }
    cout<<endl;
}

void transpos(char *crd,int size,int start){
    int i=rand()%(size-start)+start;
    int j=0;
    char temp;
    if(i==size-1)j=i-1;
    else j=i+1;
    temp=crd[i];
    crd[i]=crd[j];
    crd[j]=temp;
}

char* VISA(int &size){
    size=16;
    char* crd=new char[size];
    string str;
    int rnd=rand()%7;
    switch(rnd){
        case 0:str="4539";break;
        case 1:str="4556";break;
        case 2:str="4916";break;
        case 3:str="4532";break;
        case 4:str="4929";break;
        case 5:str="4485";break;
        case 6:str="4716";break;
    }
    stringstream s(str);
    int start=0;
    while(s>>crd[start])start++;
    prpLuhn(crd,size,start);
    return crd;
}
char* AEXPRES(int &size){
    size=15;
    char* crd=new char[size];
    string str;
    int rnd=rand()%2;
    switch(rnd){
        case 0:str="34";break;
        case 1:str="37";break;
    }
    stringstream s(str);
    int start=0;
    while(s>>crd[start])start++;
    prpLuhn(crd,size,start);
    return crd;
    
}
char* MASTERC(int &size){
    size=16;
    char* crd=new char[size];
    string str;
    int rnd=rand()%5;
    switch(rnd){
        case 0:str="51";break;
        case 1:str="52";break;
        case 2:str="53";break;
        case 3:str="54";break;
        case 4:str="55";break;
    }
    stringstream s(str);
    int start=0;
    while(s>>crd[start])start++;
    prpLuhn(crd,size,start);
    return crd;
}
char* DISCVER(int &size){
    size=16;
    char* crd=new char[size];
    string str="6011";
    stringstream s(str);
    int start=0;
    while(s>>crd[start])start++;
    prpLuhn(crd,size,start);
    return crd;
}
