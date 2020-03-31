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
int *fillAry(int);
void prntAry(int*,int);
void swap(int &, int&);
void smlLst(int*,int,int);
void Sort(int *,int);
float avrg(int *,int);

//Program Execution Begins Here
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    //Declare and initialize all Variables Here
    cout<<"enter the number of scores "<<endl;
    int size;
    cin>>size;
    int *array=fillAry(size);
   
    //Short the array
    Sort(array,size);
    
    //Output Located Here
    prntAry(array,size);
    cout<<"the average is = "<<avrg(array,size);
    //clean memory
    delete []array;
    //Exit
    return 0;
}
float avrg(int *a,int size){
    float average=0;
    for (int i=0;i<size;i++){
        average+=a[i];
    }
    average/=size;
    return average;
}
int *fillAry(int n){
    int* array=new int [n];
    for(int i=0;i<n;i++){
        cout<<"enter the value for test #"<<i+1<<endl;
        cin>>array[i];
    }
    return array;
}
void prntAry(int *array,int n){
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<array[i]<<" ";
        if(i%10==(9))cout<<endl;
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
void Sort(int *a,int n){
    for(int i=0;i<n-1;i++){
        smlLst(a,n,i);
    }
}
