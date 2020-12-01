/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on August 26th, 2020, 6:14 PM
 * Purpose:  Example of Mark Sort
 */

//System Libraries
#include <iostream>  //I/O Library
#include <cstdlib>   //Random Number Library
#include <ctime>     //Time to set the random number seed
using namespace std;

//User Libraries

//Global Constants Only
//Well known Science, Mathematical and Laboratory Constants
int Ob,Oi,Oj,POs;

//Function Prototypes
int *filAray(int);
void prntAry(const int *,int,int);
void markSrt(int *,int);

//Execution of Code Begins Here
int main(int argc, char** argv) {
    //Set the random number seed here
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare all variables for this function
    int size=850;
    int perLine=10;
    int *array;
    Ob=Oi=Oj=POs=0;
    
    
    //Initialize all known variables
    array=filAray(size);
    //cout<<"Before Sorting"<<endl;
    //prntAry(array,size,perLine);
    
    //Process Inputs to Outputs -> Mapping Process
    //Maps known values to the unknown objectives
    markSrt(array,size);
    
    //Display the Inputs/Outputs
    //cout<<"After Sorting"<<endl;
    //prntAry(array,size,perLine);
    cout<<"Ob = "<<Ob<<endl;
    cout<<"Oi = "<<Oi<<endl;
    cout<<"Oj = "<<Oj<<endl;
    cout<<"POs = "<<POs<<endl;
    int sum=Ob+Oi+Oj+POs;
    cout<<"Sum = "<<sum<<endl;
    cout<<"N = "<<size<<endl;

    //Clean up the code, close files, deallocate memory, etc....
    delete []array;
    
    //Exit stage right
    return 0;
}

//Function Implementations
void markSrt(int *a,int n){
    Ob+=3;
    for(int i=0;i<n-1;i++){
        Oi+=6;
        for(int j=i+1;j<n;j++){
            Oj+=6;
            if(a[i]>a[j]){
                POs+=8;
                int temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
    }
}


void prntAry(const int *a,int n,int perLine){
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

int *filAray(int n){
    //Declare and allocate the array
    n=n<2?2:n;
    int *array=new int[n];
    for(int i=0;i<n;i++){
        array[i]=rand();//2 Digit Random Array
    }
    return array;
}