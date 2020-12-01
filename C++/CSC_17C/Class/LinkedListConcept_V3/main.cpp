/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on September 25th, 2020, 1:40 PM
 * Purpose: Linked List Concept, V2 -> V3
 *          Add a bunch of functions and test
 */

//System Level Libraries
#include <iostream>   //I/O Library
using namespace std;  //Libraries compiled under std

//User Level Libraries
#include "Link.h"

//Global Constants - Science/Math Related
//Conversions, Higher Dimensions

//Function Prototypes
void prntLst(Link *);       //Print the list
void destroy(Link *);       //Destroy the list
Link *endLst(Link *);       //Find the last link in the list
Link *fillLnk(int);         //Fill a Link
Link *fillLst(int);         //Populate the List
//Version 3
void   addLst(Link *,int);  //Add data at the end of the list
int   findLst(Link *,int);  //Determine what link   contains the data
Link * fndLst(Link *,int);  //Determine address of link that contains the data
int    cntLst(Link *);      //How many elements are in the list

//Execution Begins Here!
int main(int argc, char** argv) {
    //Random Number Seed Set Here
    
    //Variable Declarations
    Link *lnk1;
    
    //Variable Initialization
    lnk1=fillLst(5);

    //Mapping Process Inputs to Outputs
    
    //Display Outputs
    cout<<endl<<"The Printed List"<<endl;
    prntLst(lnk1);
    cout<<"Where is the end of the List?"<<endl;
    cout<<endl<<endLst(lnk1)->data<<endl<<endl;
    
    //Test new functions
    addLst(lnk1,20);
    cout<<endl<<"The Printed List with an added element"<<endl<<endl;
    prntLst(lnk1);
    
    //Find some values in the List
    int valFnd1=3;
    int valFnd2=32;
    cout<<endl<<valFnd1<<" is found at link    "<<findLst(lnk1,valFnd1)<<endl;
    cout<<valFnd1<<" is from the address where data = "
            <<fndLst(lnk1,valFnd1)->data<<endl;
    cout<<valFnd2<<" is found at link   "<<findLst(lnk1,valFnd2)<<endl;
    cout<<"The number of elements in the list = "<<cntLst(lnk1)<<endl;

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

//Function Add a link and data to the end of the list
//Input -> front  The address to the front of the allocated list.
//         data   Data to embed at the last link in the list
void   addLst(Link *front,int data){
    Link *last=endLst(front);  //Find the last link
    Link *add=new Link;        //Create the new link
    add->data=data;            //Add the data
    add->lnkNxt=NULL;         //Set the pointer to NULL
    last->lnkNxt=add;         //Point to the new end of the list
}

//Function Find the number of the link that matches the data
//Input -> front  The address to the front of the allocated list.
//Output-> The Link number from the front where the data is found
int   findLst(Link *front,int value){
    int n=0;                //Initialize the counter
    Link *temp=front;       //Prepare to traverse the Linked list
    do{
        n++;                //Increment the counter
        if(temp->data==value)return n;//Return where the data is found
        temp=temp->lnkNxt; //Move to the next link
    }while(temp!=NULL);     //End when reaching the end of the linked list
    return -1;               //Not found then return a -1;
}

//Function Find the address of the link that matches the data
//Input -> front  The address to the front of the allocated list.
//Output-> The Link address from the front where the data is found
Link  *fndLst(Link *front,int value){
    Link *temp=front;       //Set the cursor to move through the list
    do{
        if(temp->data==value)return temp;  //Address of data match
        temp=temp->lnkNxt;                //Next link in the list
    }while(temp!=NULL);                    //End of the list
    return NULL;                           //Not found
}

//Function Find the number of links in the list
//Input -> front  The address to the front of the allocated list.
//Output-> The number of links in the list
int   cntLst(Link *front){
    int n=0;            //Initialize the counter
    Link *temp=front;   //Set the cursor to the front
    do{
        n++;            //Increment the counter
        temp=temp->lnkNxt;//Move to the next link
    }while(temp!=NULL); //Loop until the end is reached
    return n;           //Return the counter value
}