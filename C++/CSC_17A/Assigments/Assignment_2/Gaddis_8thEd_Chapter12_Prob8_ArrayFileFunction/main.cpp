/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on March 22, 2018, 11:00 AM
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
int *fill1D(int n);
void arytofl(string,int*,int);
void prntary(int *,int,int);
void fltoary(string,int*,int);
//Program Execution Begins Here
int main(int argc, char** argv) {
    //random seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare all Variables Here
    int size=20;
    int *ary=fill1D(size);
    string iname,outname;
    //Input or initialize values Here
    cout<<"input the name extract file to fill the array values"<<endl;
    cin>>iname;
    cout<<"input the file name where you want to output the array values"<<endl;
    cin>>outname;
    //Process/Calculations Here
    prntary(ary,10,size);
    arytofl(outname,ary,size);
    fltoary(iname,ary,size);
    prntary(ary,10,size);
    //destroy array
    delete []ary;
    delete ary;
    //Exit
    return 0;
}
int *fill1D(int n){
    int *a=new int[n];
    for(int i=0;i<n;i++){
    a[i]=rand()%90+10;
    }
    return a;
}
void destroy(int *d1){
    delete []d1;
    delete d1;
}
void arytofl(string flname,int *a,int size){
    ofstream out;
    out.open(flname);
    for(int i=0;i<size;i++){
        out<<a[i]<<endl;
    }
    out.close();
}
void fltoary(string flname,int *a,int size){
    ifstream in;
    in.open(flname);
    for(int i=0;i<size;i++){
        in>>a[i];
    }
    in.close();
}
void prntary(int *a,int perLine,int size){
    for(int i=0;i<size;i++){
        cout<<a[i]<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}