/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on March 22, 2018, 11:00 AM
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
using namespace std;

//User Libraries Here
#include "personal information.h"
//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
void menu(string,string,string,int);
//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    int size=3;
    string name,adress,number;
    int age; 
    //Input or initialize values Here
    cout<<"Enter name"<<endl;
    cin>>name;
    cout<<"Enter Age"<<endl;
    cin>>age;
    cout<<"Enter address"<<endl;
    cin>>adress;
    cout<<"Enter phone number"<<endl;
    cin>>number;
    data myinfo(name,adress,number,age);
    cout<<"Enter name"<<endl;
    cin>>name;
    cout<<"Enter Age"<<endl;
    cin>>age;
    cout<<"Enter address"<<endl;
    cin>>adress;
    cout<<"Enter phone number"<<endl;
    cin>>number;
    data frind1(name,adress,number,age);
    cout<<"Enter name"<<endl;
    cin>>name;
    cout<<"Enter Age"<<endl;
    cin>>age;
    cout<<"Enter address"<<endl;
    cin>>adress;
    cout<<"Enter phone number"<<endl;
    cin>>number;
    data frind2(name,adress,number,age);
    //Output Located Here
    myinfo.prnt();
    frind1.prnt();
    frind2.prnt();

    //Exit
    return 0;
}
void menu(string name,string adress,string number,int age){
    cout<<"Enter name"<<endl;
    cin>>name;
    cout<<"Enter Age"<<endl;
    cin>>age;
    cout<<"Enter address"<<endl;
    cin>>adress;
    cout<<"Enter phone number"<<endl;
    cin>>number;
}
