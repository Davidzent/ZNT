/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on April 13th, 2019, 4:31 PM
 * Purpose:  Test out push values onto simple vector
 *           with a very complex object
 *           Note:  This simple vector only works with objects
 *           Also overloading the == operator in this version of Object
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
using namespace std;

//User Libraries
#include "Object.h"       //2D Objects
#include "SimpleVector.h" //Simple Vector only works with Classes

//Global Constants

//Execution Begins Here!
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    //declare variables 
    int beg,end;
    float tottime=0;
    long long int nOp=0;
    int temp;
    int loop=50000;
    int rSize=1000;
    //Test an object
    Object a(3),b(4);
    
    //Test an object by populating the simple vector and print
    SimpleVector<Object> svp(a);
    cout<<"Simple Vector Object Size = "<<svp.mxSize()<<svp[svp.size()-1];
    //Push an Object 
    svp.push(b);
    temp=svp.getOP();
    //printout the last object
    cout<<"Simple Vector Push Size = "<<svp.mxSize()<<svp[svp.size()-1];
    //Fill the simple vector with 100 randomly size 2D Array Objects and
    //print the last one
    for(int i=0;i<loop;i++){
        Object c(rSize);
        beg=time(0);
        svp.push(c);
        end=time(0);
        tottime+=end-beg;
    }
    nOp=svp.getOP();
    nOp-=temp;
    /*
    cout<<"Max Size and Size of the Simple Vector = "
            <<svp.mxSize()<<" "<<svp.size()<<endl;
    cout<<"The last object in the Vector is "<<endl;
    cout<<svp[svp.size()-1];
    
    //Create another simple vector by copy constructor
    SimpleVector<Object> csvp(svp);
    cout<<"Max Size and Size of the Copy Constructed Simple Vector = "
            <<csvp.mxSize()<<" "<<csvp.size()<<endl;
    cout<<"The last object in the Vector is "<<endl;
    cout<<csvp[csvp.size()-1];
 
    //Utilize a simple integer Simple Vector
    int size=50;
    SimpleVector<Object> svi(size);
    cout<<"Last 2 values of the Simple Vector"<<endl;
    cout<<"The Max Size and Size = "
            <<svi.mxSize()<<" "<<svi.size()<<endl
            <<svi[svi.size()-2]<<svi[svi.size()-1];
    */
    //output time and number of operations 
    cout<<endl<<endl;
    cout<<"Time required for push : "<<tottime/(loop)<<"s"<<endl;
    cout<<"Operations made in the push: "<<nOp/(loop)<<endl;
    
    //Exit
    return 0;
}