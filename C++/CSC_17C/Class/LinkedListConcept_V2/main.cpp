/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on September 25th, 2020, 1:40 PM
 * Purpose: Linked List Concept, V1 -> V2
 *          replace all embedded elements with functions
 */

//System Level Libraries
#include <iostream>   //I/O Library
using namespace std;  //Libraries compiled under std

//User Level Libraries
#include "Link.h"

//Global Constants - Science/Math Related
//Conversions, Higher Dimensions

//Function Prototypes
void prntLst(Link *);//Print the list
void destroy(Link *);//Destroy the list
Link *endLst(Link *);//Find the last link in the list
Link *fillLnk(int);  //Fill a Link
Link *fillLst(int);  //Populate the List

//Execution Begins Here!
int main(int argc, char** argv) {
    //Random Number Seed Set Here
    
    //Variable Declarations
    Link *lnk1;
    
    //Variable Initialization
    lnk1=fillLst(5);

    //Mapping Process Inputs to Outputs
    
    //Display Outputs
    prntLst(lnk1);
    cout<<endl<<endLst(lnk1)->data<<endl;

    //Clean Up
    destroy(lnk1);
    
    //Exit stage right!
    return 0;
}

Link *fillLst(int nLinks){
    Link *front=fillLnk(1);//Create the first Link
    Link *next=front;      //Create a pointer to move thru the List
    for(int i=2;i<=nLinks;i++){//Create and attach one link after another
        Link *newLnk=fillLnk(i);
        next->lnkNxt=newLnk;
        next=newLnk;
    }
    next->lnkNxt=NULL;//Terminate the List with a NULL
    return front;//Always know where the front of the list is, don't redefine
}

Link *fillLnk(int data){
    Link *lnk=new Link;
    lnk->data=data;
    return lnk;
}

Link *endLst(Link *front){
    Link *next=front;
    Link *last;
    while(next!=NULL){
        last=next;
        next=next->lnkNxt;
    }
    return last;
}

void destroy(Link *front){
    Link *next=front;
    Link *temp;
    while(next!=NULL){
        temp=next;
        next=next->lnkNxt;
        delete temp;
    }
}

void prntLst(Link *front){
    Link *next=front;
    while(next!=NULL){
        cout<<next->data<<endl;
        next=next->lnkNxt;
    }
}