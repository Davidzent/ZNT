/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on September 19th, 2020, 11:40 AM
 * Purpose: Linked List Concept
 */

//System Level Libraries
#include <iostream>   //I/O Library
using namespace std;  //Libraries compiled under std

//A basic Link structure that holds data and a pointer to the next
//in the list
struct Link{
    int data;
    Link *lnkNxt;
};

//Global Constants - Science/Math Related
//Conversions, Higher Dimensions

//Function Prototypes

//Execution Begins Here!
int main(int argc, char** argv) {
    //Random Number Seed Set Here
    
    //Variable Declarations, Create 5 Links
    Link *lnk1=new Link;
    Link *lnk2=new Link;
    Link *lnk3=new Link;
    Link *lnk4=new Link;
    Link *lnk5=new Link;
    
    //Variable Initialization, Fill the 5 links with data
    lnk1->data=1;
    lnk2->data=2;
    lnk3->data=3;
    lnk4->data=4;
    lnk5->data=5;
    
    //Mapping Process Inputs to Outputs, Take each link and tie them into
    //a list
    lnk1->lnkNxt=lnk2;
    lnk1->lnkNxt->lnkNxt=lnk3;
    lnk1->lnkNxt->lnkNxt->lnkNxt=lnk4;
    lnk1->lnkNxt->lnkNxt->lnkNxt->lnkNxt=lnk5;
    lnk1->lnkNxt->lnkNxt->lnkNxt->lnkNxt->lnkNxt=NULL;
    
    //Display Outputs, Traverse the list, one link at a time.
    Link *next=lnk1;
    while(next!=NULL){
        cout<<next->data<<endl;
        next=next->lnkNxt;
    }

    //Clean Up, Delete all the elements in the list
    delete lnk1,lnk2,lnk3,lnk4,lnk5;
    
    //Exit stage right!
    return 0;
}