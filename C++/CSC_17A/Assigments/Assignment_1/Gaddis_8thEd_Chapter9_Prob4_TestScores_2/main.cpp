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
void fillAry(int *,string *,int);
void prntAry(int*,int,string *);
void swap(int &, int&,string &);
void smlLst(int*,int,int,string *);
void Sort(int *,int,string *);
float avrg(int *,int);

//Program Execution Begins Here
int main(int argc, char** argv) {
    srand(static_cast<unsigned int>(time(0)));
    //Declare and initialize all Variables Here
    cout<<"enter the number of scores "<<endl;
    int size;
    cin>>size;
    string *names= new string [size];
    int *array= new int [size];
    fillAry(array,names,size);
    //Short the array
    Sort(array,size,names);
    
    //Output Located Here
    prntAry(array,size,names);
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
void fillAry(int *array,string *name,int n){
    for(int i=0;i<n;i++){
        cout<<"enter the name for student #"<<i+1<<endl;
        cin>>name[i];
        cout<<"enter the value for test #"<<i+1<<endl;
        cin>>array[i];
    }
}
void prntAry(int *array,int n,string *names){
    cout<<endl;
    for(int i=0;i<n;i++){
        cout<<names[i]<<" got "<<array[i]<<endl;
    }
    cout<<endl;
}
void swap(int &a, int &b,string &c,string &d){
    a=a^b;
    b=a^b;
    a=a^b;
    string temp=c;
    c=d;
    d=temp;
}
void smlLst(int *a,int n,int pos,string *c){
    for(int i=pos;i<n;i++){
        if(a[pos]>a[i])swap(a[pos],a[i],c[pos],c[i]);
    }
}
void Sort(int *a,int n,string *c){
    for(int i=0;i<n-1;i++){
        smlLst(a,n,i,c);
    }
}
