/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on November 21, 2018, 1:11 PM
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries
#include "Link.h"

//Functions associated with lists
Link *fillLst(int);
void  prntLst(Link *);
void  delLst(Link *);
Link *ptrEnd(Link *);
void  addEnd(Link *,int);


int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Create 2 link pointers
    Link *link1;
    
    //Dynamically allocate memory
    link1=fillLst(10);
    
    //Print the list
    prntLst(link1);
    
    //Add some data
    addEnd(link1,0);
    
    //Print the list
    prntLst(link1);
   
    //Delete Allocated List
    delLst(link1);
    
    //Exit stage right!
    return 0;
}

void  addEnd(Link *front,int val){
    Link *end=ptrEnd(front);
    Link *next=new Link;
    end->node=next;
    next->data=val;
    next->node=NULL;
}

Link *ptrEnd(Link *front){
    Link *end=front;
    while(front!=NULL){
        end=front;
        front=front->node;
    }
    return end;
}

void  prntLst(Link * front){
    while(front!=NULL){
        cout<<front->data<<endl;
        front=front->node;
    }
}

void  delLst(Link * front){
    Link *toBXed;
    while(front!=NULL){
        toBXed=front;
        front=front->node;
        delete toBXed;
    }
}

Link *fillLst(int n){
    Link *front=new Link;
    Link *ptr=front;
    front->data=n--;
    for(int i=n;i>=1;i--){
        Link *next=new Link;
        ptr->node=next;
        next->data=i;
        next->node=NULL;
        ptr=next;
    }
    return front;
}