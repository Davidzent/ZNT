/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on May 29, 2019, 7:28 PM
 */

//System Libraries
#include<iostream>
using namespace std;
 
//User Libraries
#include "Tree.h"

//Global Constants

//Function Prototypes
void menu();

//Execution Begins Here!
int main(){
    int choice;
    int item;
    Tree<int>*tree;
    /*do{
        menu();
        cin>>choice;
        switch(choice){
            case 1:
                cout<<"Enter value to be inserted: ";cin>>item;
                tree=tree->insert(tree,item);break;
            case 2:
                if (tree == NULL){cout<<"Tree is Empty"<<endl;continue;}
                cout<<"Balanced Tree:"<<endl;tree->display(tree,1);break;
            case 3:
                cout<<"In-order Traversal:"<<endl;tree->In_ord(tree);
                cout<<endl;break;
            case 4:
                cout<<"Pre-order Traversal:"<<endl;tree->Pre_ord(tree);
                cout<<endl;break;
            case 5:
                cout<<"Post-order Traversal:"<<endl;tree->Pos_ord(tree);    
                cout<<endl;break;
            default:
                cout<<"Exit Program"<<endl;
        }
    }while(choice>0&&choice<=5);*/
    for(int i=0;i<101;i++){
        tree=tree->insert(tree,i);
    }
    if (tree == NULL){cout<<"Tree is Empty"<<endl;}
    cout<<"\nBalanced Tree:"<<endl;
    tree->In_ord(tree);
    for(int i=0;i<101;i++){
        tree=tree->insert(tree,i);
    }
    if (tree == NULL){cout<<"Tree is Empty"<<endl;}
    cout<<"\nBalanced Tree:"<<endl;
    tree->In_ord(tree);
    //Exit stage right!
    return 0;
}

void menu(){
    cout<<"\n---------------------"<<endl;
    cout<<"Tree Implementation"<<endl;
    cout<<"\n---------------------"<<endl;
    cout<<"1.Insert Element into the tree"<<endl;
    cout<<"2.Display Balanced AVL Tree"<<endl;
    cout<<"3.InOrder traversal"<<endl;
    cout<<"4.PreOrder traversal"<<endl;
    cout<<"5.PostOrder traversal"<<endl;
    cout<<"6.Exit"<<endl;
    cout<<"Enter your Choice: ";
}