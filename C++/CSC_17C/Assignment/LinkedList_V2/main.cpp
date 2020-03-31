/* 
 * File:   main.cpp
 * Author: David Guijosa
 * Created on March 20th, 2019, 9:26 AM
 * Purpose:  test Template Linked List
 */

//System Libraries
#include <cstdlib>   //Random Function
#include <iostream>  //I/O Stream
#include <ctime>     //Time Function setting random seed
using namespace std;

//User Libraries
#include "Node.h"

//Global Constants
//Physics/Math/Conversions/2+ArrayDimenstions
//No Global Variables

//Function Prototypes Here
Node<int> *filNode(int);

//Execution Begins with Main
int main(int argc, char** argv) {
    //Random Number seed set once here
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare and initialize variables
    Node<int> *head=new Node<int>(filNode(10));
    
    //Display results here
    cout<<head<<endl;
    //try the functions
    cout<<"1: pop Back"<<endl<<head->pop_back()<<endl<<endl;
    cout<<"2: pop Front"<<endl<<head->pop_front()<<endl<<endl;
    cout<<"3: push Back 15"<<endl;
    head->push_back(15);
    cout<<head<<endl;
    cout<<"4: Push Front 15"<<endl;
    head->push_front(15);
    cout<<head<<endl;
    cout<<"5: Sort"<<endl;
    head->Sort();
    cout<<head<<endl;
    cout<<"6: get Size"<<endl;
    cout<<head->Size()<<endl;
    //Exit stage right
    return 0;
}

Node<int> *filNode(int n){
    //Initialize the front
    Node<int> *head=new Node<int>(rand()%100+10);
    Node<int> *tail=new Node<int>(rand()%100+10);
    n-=2;
    head->setPtr(tail);
    //Loop until filled
    do{
        n--;
        Node<int> *next=new Node<int>(rand()%100+10);
        tail->setPtr(next);
        tail=tail->getPtr();
    }while(n>=0);
    return head;
}