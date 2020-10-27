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
Node<int> *filSort(int);
//Execution Begins with Main
int main(int argc, char** argv) {
    //Random Number seed set once here
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare and initialize variables
    Node<int> *head=filNode(10);
    Node<int> *temp=filSort(100);
    Node<int> *cpsort=new Node<int>(temp);
    //Display results here
    temp->push_sort(50000);
    cout<<"Normal Fill"<<endl;
    cout<<head<<endl;
    cout<<"Sort Fill"<<endl;
    cout<<temp<<endl;
    cout<<"Sort Fill - Copy"<<endl;
    cout<<cpsort<<endl;
  
    //try the functions
    cout<<"1: pop Back"<<endl<<head->pop_back()<<endl<<endl;
    cout<<"2: pop Front"<<endl<<head->pop_front()<<endl<<endl;
    cout<<head<<endl;
    cout<<"3: push Back 15"<<endl;
    head->push_back(15);
    cout<<head<<endl;
    cout<<"4: Push Front 15"<<endl;
    head->push_front(18);
    cout<<head<<endl;
    cout<<"5: Sort"<<endl;
    head->Sort();
    cout<<head<<endl;
    cout<<"6: get Size"<<endl;
    cout<<head->Size()<<endl;
    cout<<"7: Sort push"<<endl;
    head->push_sort(20);
    cout<<head<<endl;
    cout<<"Sort push the biggest number"<<endl;
    head->push_sort(2000);
    head->push_sort(1000);
    head->push_sort(4000);
    head->push_sort(200);
    head->push_sort(99);
    head->push_sort(999);
    cout<<head<<endl;
    cout<<"Sort push the smallest number"<<endl;
    head->push_sort(0);
    cout<<head<<endl;
    cout<<"Sort push the 2nd smallest number"<<endl;
    head->push_sort(5);
    cout<<head<<endl;
    cout<<"Check for a value in the link list"<<endl;
    if(head->chckval(5)){
        cout<<"The value "<<5<<" is in the link list"<<endl;
    }else{
        cout<<"The value "<<5<<" is not in the link list"<<endl;
    }
    cout<<"Check for a value in the link list"<<endl;
    cout<<"The value "<<3000<<" is "<<(head->chckval(3000)?"":"not ")<<"in the link list"<<endl;
    
    delete head;
    delete temp;
    delete cpsort;
    //Exit stage right
    return 0;
}

Node<int> *filNode(int n){
    //Initialize the front
    Node<int> *head=new Node<int>();
    for(int i=0;i<n;i++){
        head->push_front(rand()%90+10);
    }
    return head;
}
Node<int> *filSort(int n){
    //Initialize the front
    Node<int> *node=new Node<int>();
    for(int i=0;i<n;i++){
        node->push_sort(rand()%90+10);
    }
    return node;
}