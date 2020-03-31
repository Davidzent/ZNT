/* 
 * File:   NODE.h
 * Author: david
 *
 * Created on May 29, 2019, 7:28 PM
 */

#ifndef TREE_H
#define TREE_H

#include <iostream>
using namespace std;
template <class T>
class Tree{
    private:
        T data;
        Tree<T> *Sroot;     //Smaller number
        Tree<T> *Broot;     //bigger number
    public:
        int height(Tree<T> *);         //Tree height
        int diff(Tree<T> *);           //Difference of right/left subtrees
        Tree<T> *gtSRoot(){return Sroot;}
        Tree<T> *gtBRoot(){return Broot;}
        T   gtData(){return data;} 
        Tree<T> *RRrot(Tree<T> *);        //Right-Right rotation
        Tree<T> *LLrot(Tree<T> *);        //Left-Left   rotation
        Tree<T> *LRrot(Tree<T> *);        //Left-Right  rotation
        Tree<T> *RLrot(Tree<T> *);        //Right-Left  rotation
        Tree<T> *balance(Tree<T> *);      //Balance subtrees with diff > 1
        Tree<T> *insert(Tree<T>*,T);     //Insert and balance the tree
        void display(Tree<T> *, int);  //Funky display root left to right
        void In_ord(Tree<T> *);        //In order display
        void Pre_ord(Tree<T> *);       //Pre order display
        void Pos_ord(Tree<T> *);       //Post order display
        Tree(){Sroot = NULL; Broot=NULL;}  //Constructor   
        Tree(Tree<T> *root){Sroot=root->Sroot;Broot=root->Broot;data=root->data;}
        ~Tree(){delete Sroot;delete Broot;}
};
//******************************************************************************
//                            Height of Trees
//******************************************************************************
template <class T>
int Tree<T>::height(Tree<T> *temp){
    int h = 0;
    if (temp != NULL){
        int l_height = height (temp->Sroot);
        int r_height = height (temp->Broot);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}
 
//******************************************************************************
//                      Height Difference of AVL Sub Trees
//******************************************************************************
template <class T>
int Tree<T>::diff(Tree<T> *temp){
    int l_height = height (temp->Sroot);
    int r_height = height (temp->Broot);
    int b_factor= l_height - r_height;
    return b_factor;
}
 
//******************************************************************************
//                      Right-Right Rotations of Sub Trees
//******************************************************************************
template <class T>
Tree<T> *Tree<T>::RRrot(Tree<T> *parent){
    Tree<T> *temp;
    temp = parent->Broot;
    parent->Broot = temp->Sroot;
    temp->Sroot = parent;
    return temp;
}

//******************************************************************************
//                      Left-Left Rotations of Sub Trees
//******************************************************************************
template <class T>
Tree<T> *Tree<T>::LLrot(Tree<T> *parent){
    Tree<T> *temp;
    temp = parent->Sroot;
    parent->Sroot = temp->Broot;
    temp->Broot = parent;
    return temp;
}
 
//******************************************************************************
//                      Left-Right Rotations of Sub Trees
//******************************************************************************
template <class T>
Tree<T> *Tree<T>::LRrot(Tree<T> *parent){
    Tree<T> *temp;
    temp = parent->Sroot;
    parent->Sroot = RRrot (temp);
    return LLrot (parent);
}
 
//******************************************************************************
//                      Right-Left Rotations of Sub Trees
//******************************************************************************
template <class T>
Tree<T> *Tree<T>::RLrot(Tree<T> *parent){
    Tree<T> *temp;
    temp=parent->Broot;
    parent->Broot=LLrot(temp);
    return RRrot(parent);
}
 
//******************************************************************************
//                         Balancing of Sub Trees
//******************************************************************************
template <class T>
Tree<T> *Tree<T>::balance(Tree<T> *temp){
    int balfact=diff(temp);
    if (balfact>1){
        if (diff(temp->Sroot)>0)
            temp=LLrot(temp);
        else
            temp=LRrot(temp);
    }else if(balfact<-1){
        if (diff(temp->Broot)>0)
            temp=RLrot(temp);
        else
            temp=RRrot(temp);
    }
    return temp;
}
 
//******************************************************************************
//                    Insert the Data into the Sub Trees
//******************************************************************************
template <class T>
Tree<T> *Tree<T>::insert(Tree<T> *pos,T value){
    if (pos == NULL){
        pos=new Tree;
        pos->data=value;
        pos->Sroot = NULL;
        pos->Broot = NULL;
        return pos;
    }else if (value<pos->data){
        pos->Sroot = insert(pos->Sroot,value);
        pos = balance (pos);
    }else if (value >= pos->data){
        pos->Broot = insert(pos->Broot,value);
        pos = balance(pos);
    }
    return pos;
}
 
//******************************************************************************
//                         Display all Sub Trees
//******************************************************************************
template <class T>
void Tree<T>::display(Tree<T> *ptr,int level){
    if (ptr!=NULL){
        display(ptr->Broot, level + 1);
        cout<<endl;
        if (ptr == this)
        cout<<"R -> ";
        for(int i=0;i<level&&ptr!=this;i++)
            cout<<"     ";
        cout<<ptr->data;
        display(ptr->Sroot, level + 1);
    }
}
 
//******************************************************************************
//                      In-order Output of Tree
//******************************************************************************
template <class T>
void Tree<T>::In_ord(Tree<T> *tree){
    static int i=1;
    if (tree == NULL)return;
    In_ord (tree->Sroot);
    cout<<tree->data<<(i++%10==0?'\n':' ');
    In_ord (tree->Broot);
}

//******************************************************************************
//                      Pre-order Output of Tree
//******************************************************************************
template <class T>
void Tree<T>::Pre_ord(Tree<T> *tree){
    if (tree == NULL)
        return;
    cout<<tree->data<<"  ";
    Pre_ord (tree->Sroot);
    Pre_ord (tree->Broot);
}
 
//******************************************************************************
//                      Post-order Output of Tree
//******************************************************************************
template <class T>
void Tree<T>::Pos_ord(Tree<T> *tree){
    if (tree == NULL)
        return;
    Pos_ord ( tree ->Sroot );
    Pos_ord ( tree ->Broot );
    cout<<tree->data<<"  ";
}

#endif /* Tree_H */

