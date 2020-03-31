/* 
 * File:   main.cpp
 * Author: David Guijosa
 * Created on April 30th, 2019, 7:45 PM
 */

//Libraries
#include <cstdlib>//Random number seed
#include <ctime>//Set the seed
#include <iostream>//I/O
#include <bits/stdc++.h>
using namespace std;

//No Global Constants

//Function Prototypes
int *fillAry(int,int);
void prntAry(int *,int,int);
void prntMod(int *);
void swap(int *,int *);
void minPos(int *,int,int);
void mrkSort(int *,int);
int *mode(const int *,int);
int *copy(const int *,int);
int *modeSet(const int *,set<int>&,int);
//Execution begins here
int main(int argc, char*argv[]) {
    //Declare variables and fill
    int arySize=35;
    int modNum=10;
    int *ary=fillAry(arySize,modNum);
    int beg,end; //time for functions
    set<int> s1;
    //Print the initial array
    prntAry(ary,arySize,10);
    int *modeset=modeSet(ary,s1,arySize);
    //Calculate the mode array
    int *modeAry=mode(ary,arySize);
    //Print the modal information
    cout<<s1.count(0)<<endl;
    cout<<endl;
    cout<<"Set :"<<endl;
    for(int i:s1){
        cout<<i<<" ";
    }
    cout<<endl<<endl;
    cout<<"array : "<<endl;
    prntMod(modeAry);
    
    //Delete allocated memory
    delete []ary;
    delete []modeAry;
    
    //Exit stage right
    return 0;
}

int *modeSet(const int *array,set<int>&s1,int arySize){
    int nModes=0;
    int *locat=new int[arySize];
    
    for(int i=0;i<arySize;i++){
        s1.insert(array[i]);
        //    locat[nModes]=i;
        //   nModes++;
        //}
    }
    cout<<s1.find(1)<<endl;
    
    int *mode=new int[nModes];
    for(int i=0;i<nModes;i++){
        mode[i]=array[locat[nModes]];
    }
    cout<<<<" Modes in ModeSet : ";
    for(int i=0;i<nModes;i++){
        if(i%10==0)cout<<endl;
        cout<<mode[i]<<" ";        
    }
    return mode;
}

int *copy(const int *a,int n){
    //Declare and allocate an array
    //that is a c
    int *b=new int[n];
    //Fill
    for(int i=0;i<n;i++){
        b[i]=a[i];
    }
    //Return the copy
    return b;
}

int *mode(const int *array,int arySize){
    //Copy the array
    int *ary=copy(array,arySize);
    //Sort the ary
    mrkSort(ary,arySize);
    //Sort the copy
    //Find the max Freq
    int count=0,maxFreq=0;
    for(int i=0;i<arySize-1;i++){
        if(ary[i]==ary[i+1]){
            count++;
            if(maxFreq<count)maxFreq=count;
        }else{
            count=0;
        }
    }
    cout<<"Mode Freq = "<<maxFreq+1<<endl;
    //Find the number of modes
    count=0;
    int nModes=0;
    for(int i=0;i<arySize-1;i++){
        if(ary[i]==ary[i+1]){
            count++;
            if(maxFreq==count)nModes++;
        }else{
            count=0;
        }
    }
    cout<<"Number of modes = "<<nModes<<endl;
    //Allocate the mode array
    int *modeAry=new int[nModes+2];
    //Fill the mode array
    modeAry[0]=nModes;
    modeAry[1]=maxFreq+1;
    count=0;
    int indx=2;
    for(int i=0;i<arySize-1;i++){
        if(ary[i]==ary[i+1]){
            count++;
            if(maxFreq==count)modeAry[indx++]=ary[i];
        }else{
            count=0;
        }
    }
    //Delete the allocated copy and return
    delete []ary;
    return modeAry;
}

void prntMod(int *ary){
    cout<<endl;
    cout<<"The number of modes = "<<
            ary[0]<<endl;
    cout<<"The max Frequency = "<<
            ary[1]<<endl;
    if(ary[0]==0){
        cout<<"The mode set = {null}"<<endl;
        return;
    }
    cout<<"The mode set = {";
    for(int i=2;i<ary[0]+1;i++){
        cout<<ary[i]<<",";
    }
    cout<<ary[ary[0]+1]<<"}"<<endl;
}

void mrkSort(int *array,int n){
    for(int i=0;i<n-1;i++){
        minPos(array,n,i);
    }
}

void minPos(int *array,int n,int pos){
    for(int i=pos+1;i<n;i++){
        if(*(array+pos)>*(array+i))
            swap(array+pos,array+i);
    }
}

void swap(int *a,int *b){
    //Swap in place
    *a=*a^*b;
    *b=*a^*b;
    *a=*a^*b;
}

void prntAry(int *array,int n,int perLine){
    //Output the array
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<*(array+i)<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

int *fillAry(int n, int modNum){
    //Allocate memory
    int *array=new int[n];
    
    //Fill the array with 2 digit numbers
    for(int i=0;i<n;i++){
        *(array+i)=i%modNum;
        //*(array+i)=rand()%modNum;
    }
    
    //Exit function
    return array;
}