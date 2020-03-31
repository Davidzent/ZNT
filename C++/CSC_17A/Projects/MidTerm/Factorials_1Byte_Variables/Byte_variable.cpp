/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on Oct 27, 2018, 11:00 AM
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
void factorial(unsigned char* ,int);
void posible(unsigned char*,int);
void print(unsigned char*,int);
int big(unsigned char*,int);
void destroy(unsigned char*);
//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int size=10;
    int max=0;
    unsigned char* array=new unsigned char[size];
    //Try for possible answers
    posible(array,size);
    //find the bigger factorial possible
    max=big(array,size);
    //output data
    cout<<"The maximum factorial in a byte variable is "<<max<<endl;
    print(array,max);
    //Exit
    destroy(array);
    return 0;
}
void print(unsigned char *array,int size){
    for(int i=0;i<size;i++){
        cout<<"the factorial of "<<i+1<<" is = "<<
                static_cast<int>(array[i])<<endl;
    }
}
void posible(unsigned char *array,int size){
    for(int i=0;i<size;i++){
        factorial(array,i);
    }
}
void factorial(unsigned char *array,int val){
    if(val==0)array[val]=val+1;
    else array[val]=array[val-1]*(val+1);
}
void destroy(unsigned char *array){
    delete []array;
}
int big(unsigned char *array,int size){
    int max=0;
    for(int i=2;i<size;i++){
        if(array[i]==array[i-1]*(i+1))max=i+1;
        else return max;
    }
}