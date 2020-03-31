/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on March 22, 2018, 11:00 AM
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
int *fillAry(int,int);
void prntAry(int*,int,int);
void swap(int &, int&);
void smlLst(int*,int,int);
void mrkSort(int *,int);
int mode(int *,int);

//Program Execution Begins Here
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    //Declare all Variables Here
    int size=100;
    int mod=10;
    int *array=fillAry(size,mod);
    int mde=mode(array,size);
   
    //Short the array
    mrkSort(array,size);
    
    //Output Located Here
    prntAry(array,size,mod);
    cout<<"The first mode is "<<array[mde]<<endl;
    //clean memory
    delete []array;
    //Exit
    return 0;
}
int mode(int *a,int size){
    int count,mde=0,lcation;
    int quntity=1;
    for(int i=0;i<size;i++){
        if(i!=0&&a[i]==a[i-1])quntity++;
        else if(i!=0&&a[i]!=a[i-1]){
            quntity>mde?mde=quntity,lcation=i-1:quntity=1;            
            quntity=1;
        }
    }
    return lcation;
}
int *fillAry(int n,int m){
    int* array=new int [n];
    for(int i=0;i<n;i++){
        array[i]=i%m;
    }
    return array;
}
void prntAry(int *array,int n,int perLine){
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<array[i]<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}
void swap(int &a, int &b){
    a=a^b;
    b=a^b;
    a=a^b;
}
void smlLst(int *a,int n,int pos){
    for(int i=pos;i<n;i++){
        if(a[pos]>a[i])swap(a[pos],a[i]);
    }
}
void mrkSort(int *a,int n){
    for(int i=0;i<n-1;i++){
        smlLst(a,n,i);
    }
}
