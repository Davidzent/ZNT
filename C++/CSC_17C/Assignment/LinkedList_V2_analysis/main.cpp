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
#include <iomanip>
using namespace std;

//User Libraries
#include "Node.h"

//Global Constants
//Physics/Math/Conversions/2+ArrayDimenstions
//No Global Variables

//Function Prototypes Here
Node<int> *filNode(int);
Node<int> *filNodePB(int);
Node<int> *filSort(int);
//Execution Begins with Main
int main(int argc, char** argv) {
    //Random Number seed set once here
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare and initialize variables
    int loop = 10;
    int size = 50000;
    float tim=0;
    cout<<fixed<<showpoint<<setprecision(10);
    unsigned long int beg = time(0);
    /*for(int i=0;i<loop;i++){
        Node<int> *temp=filNode(size);
        delete temp;
    }*/
    unsigned int end = time(0);
    /*tim=end-beg;
    cout<<"Time to fill push front = "<<end<<endl;
    cout<<"average time            = "<<(tim)/loop<<endl;
    */
    beg=time(0);
    for(int i=0;i<loop;i++){
        Node<int> *temp=filSort(size);
        //delete temp;
    }
    end=time(0);
    tim=end-beg;
    cout<<"Time to fill sort       = "<<end<<endl;
    cout<<"average time            = "<<(tim)/loop<<endl;
    
    beg=time(0);
    for(int i=0;i<loop;i++){
        Node<int> *temp=filNodePB(size);
        //delete temp;
    }
    end=time(0);
    tim=end-beg;
    cout<<"Time to fill push back  = "<<end<<endl;
    cout<<"average time            = "<<(tim)/loop<<endl;
    
    /*beg = time(0);
    for(int i=0;i<loop;i++){
        Node<int> *temp=filNode(size);
        temp->Sort();
        delete temp;
    }
    end = time(0);
    tim=end-beg;
    cout<<fixed<<showpoint<<setprecision(10)<<endl;
    cout<<"Time to fill push front then sort = "<<end<<endl;
    cout<<"average time                      = "<<(tim)/loop<<endl;
    
    //Display results here
    */
    //Exit stage right
    return 0;
}

Node<int> *filNode(int n){
    //Initialize the front
    Node<int> *head=new Node<int>();
    for(int i=0;i<n;i++){
        head->push_front(rand());
    }
    return head;
}
Node<int> *filNodePB(int n){
    //Initialize the front
    Node<int> *head=new Node<int>();
    for(int i=0;i<n;i++){
        head->push_back(rand());
    }
    return head;
}
Node<int> *filSort(int n){
    //Initialize the front
    Node<int> *node=new Node<int>();
    for(int i=0;i<n;i++){
        node->push_sort(rand());
    }
    return node;
}