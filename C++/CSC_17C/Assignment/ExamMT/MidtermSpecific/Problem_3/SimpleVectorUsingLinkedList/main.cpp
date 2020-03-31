/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on April 18th, 2019, 4:31 PM
 * Purpose:  Test out push values onto simple vector
 *           with a very complex object
 *           Note:  This simple vector only works with objects
 *           Also overloading the == operator in this version of Object
 *           Simple Vector using Linked List
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
using namespace std;

//User Libraries
#include "Object.h"       //2D Object
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
    int loop=20000;
    int rSize=70;
    //Test an object
    Object a(3),b(4);
    
    //Output the objects
    cout<<"Test Object to put in front = ";
    cout<<a;
    cout<<"Test Object to put at   end = ";
    cout<<b;

    //Create a Simple Vector using Linked Lists
    SimpleVector<Object> svp(a);
    
    //Fill the simple vector with 10 randomly size 2D Array Objects and
    //print the last one
    for(int i=0;i<loop;i++){
        Object c(rSize);
        beg=time(0);
        svp.push(c);
        end=time(0);
        tottime+=end-beg;
    }
    nOp=svp.getOP();
    //End the Simple Vector using lists with object b
    /*svp.push(b);
    cout<<"Simple Vector Object size  = "<<svp.size()<<endl;
    cout<<"Simple Vector Front Object =  "<<svp[0];
    cout<<"Simple Vector End Object   =  "<<svp[svp.size()-1];
    */
    //output time and number of operations 
    cout<<endl<<endl;
    cout<<"Time required for push : "<<tottime/(loop)<<"s"<<endl;
    cout<<"Operations made in the push: "<<nOp/(loop)<<endl;
    
    //Exit*/
    return 0;
}