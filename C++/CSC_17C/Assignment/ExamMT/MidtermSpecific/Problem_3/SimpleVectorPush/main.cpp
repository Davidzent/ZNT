/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on April 13th, 2019, 4:31 PM
 * Purpose:  Test out push values onto simple vector
 *           with a very complex object
 *           Note:  This simple vector only works with objects
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
    int loop=1000;
    int temp;
    int rSize=70;
    //Test an object
    Object a(3),b(4);
    cout<<"One of the Objects"<<a;
    //Test an object by populating the simple vector and print
    SimpleVector<Object> svp(a);
    cout<<"Simple Vector Object Initialization"<<svp[svp.size()-1];
    //Push an Object
    //calculate the time and number of operations
    svp.push(b);
    temp=svp.getOP();
    
    //printout the last object
    cout<<"Simple Vector Push next object"<<svp[svp.size()-1];
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
    /*cout<<"Size of the Simple Vector = "<<svp.size()<<endl;
    cout<<"The last object in the Vector is "<<endl;
    cout<<svp[svp.size()-1];
    //Create another simple by copy constructor
    SimpleVector<Object> csvp(svp);
    cout<<"Size of the Copy Constructed Simple Vector = "<<csvp.size()<<endl;
    cout<<"The last object in the Vector is "<<endl;
    cout<<csvp[csvp.size()-1];
    //Utilize a simple integer Simple Vector
    int size=15;
    SimpleVector<Object> svi(size);
    cout<<"Size of this vector = "<<svi.size()<<endl;
    cout<<"Last 2 Objects of the Simple Vector"<<endl;
    cout<<"The size = "<<svi.size()<<endl<<svi[svi.size()-2]
                                         <<svi[svi.size()-1];
    //output time and number of operations 
    */
    cout<<endl<<endl;
    cout<<"Time required for push : "<<tottime/(loop)<<"s"<<endl;
    cout<<"Operations made in the push: "<<nOp/(loop)<<endl;
    
    //Exit
    return 0;
}