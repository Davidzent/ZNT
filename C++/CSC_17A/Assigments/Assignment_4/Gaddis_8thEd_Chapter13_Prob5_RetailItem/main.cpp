/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on Nov 08, 2018, 11:00 AM
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
#include "Retail Item.h"
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    int size;
    string name;
    float price;
    int quant;
    //Input or initialize values Here
    cout<<"Input the number of products"<<endl;
    cin>>size;
    RtItem item[size];
    for(int i=0;i<size;i++){
        cout<<"input the description of the product"<<endl;
        cin>>name;
        cout<<"Input the quantity of the product"<<endl;
        cin>>quant;
        cout<<"input the price of the product"<<endl;
        cin>>price;
        item[i].setquan(quant);
        item[i].setdesc(name);
        item[i].setprc(price);
    }
    //Output Located Here
    for(int i=0;i<size;i++){
        item[i].prnt(i);
    }
    //Exit
    return 0;
}

