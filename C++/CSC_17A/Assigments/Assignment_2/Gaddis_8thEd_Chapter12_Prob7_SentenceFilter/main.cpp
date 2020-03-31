/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on March 22, 2018, 11:00 AM
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
#include <fstream>

using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare and input all Variables Here
    string file,file2;
    cout<<"input the file name for input"<<endl;
    cin>>file2;
    cout<<"input the file name for output"<<endl;
    cin>>file;
    ofstream out;
    ifstream in;
    in.open(file);
    out.open(file);
    string words;
    in>>words;
    cout<<words<<endl;
    char letter[words.size()];
    //Process/Calculations Here
    for(int i=0;i<words.size();i++){
        if(letter[i]>=65&&letter[i]<=90&&i==0)letter[i]+=32;
        else if(letter[i]>=65&&letter[i-1]==46&&letter[i]<=90)letter[i]+=32;
        else if(letter[i]>=97&&letter[i-1]!=46&&letter[i]<=122)letter[i]-=32;
        out<<letter[i];}
    //Output Located Here    
    in.close();
    out.close();
    //Exit
    return 0;
}

