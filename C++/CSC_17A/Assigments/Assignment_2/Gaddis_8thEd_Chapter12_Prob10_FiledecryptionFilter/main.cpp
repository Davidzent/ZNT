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
void arytofl(string,char*,int);
string fltoary(string);
char *uncding(string);
//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    char *ary;
    int size;
    string iname,outname,words;
    //Input or initialize values Here
    cout<<"input the name extract file to fill the array values"<<endl;
    cin>>iname;
    cout<<"input the file name where you want to output the array values"<<endl;
    cin>>outname;
    //Process/Calculations Here
    words=fltoary(iname);
    size=words.size();
    ary=coding(words);
    arytofl(outname,ary,size);
    //destroy array
    delete []ary;
    //Exit
    return 0;
}
char *coding(string word){
    char *a=new char[word.size()];
    for(int i=0;i<word.size();i++){
    a[i]=word[i];
    a[i]-=10;
    }
    return a;
}
void arytofl(string flname,char *a,int size){
    ofstream out;
    out.open(flname);
    for(int i=0;i<size;i++){
        out<<a[i]<<endl;
    }
    out.close();
}
string fltoary(string flname){
    ifstream in;
    string ss;
    in.open(flname);
    while(in>>ss);
    in.close();
    return ss;
}
