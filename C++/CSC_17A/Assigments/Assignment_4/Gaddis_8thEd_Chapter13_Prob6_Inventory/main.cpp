/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on Nov 08, 2018, 11:00 AM
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
#include "Inventory.h"
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    int name;
    float price;
    int quant;
    //Input or initialize values Here
    invent tot;
    cout<<"input the Item number of the product"<<endl;
    cin>>name;
    cout<<"Input the quantity of the product"<<endl;
    cin>>quant;
    cout<<"input the cost of the product"<<endl;
    cin>>price;
    tot.setID(name);
    tot.setcost(price);
    tot.setquan(quant);
    
    //Output Located Here
    cout<<"Product ID "<<tot.getID()<<endl;
    cout<<"Cost "<<tot.getcost()<<endl;
    cout<<"Quantity "<<tot.getquan()<<'\n';
    cout<<"total cost "<<tot.getotcs()<<'\n';

    //Exit
    return 0;
}

