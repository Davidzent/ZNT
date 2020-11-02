/* 
 * File:   main.cpp
 * Author: Guijosa David
 * Created on March 28th, 2019, 9:26 AM
 * Purpose:  Template Link List
 */

#ifndef NODE_H
#define NODE_H

#include <iostream>
using namespace std;

template <class T>
class Node{
    private:
        unsigned int size;
        T data;
        Node<T> *ptr;
    public:
        Node(){size=0;};
        Node(const T);
        Node(Node<T>*);
        ~Node();
        Node<T> *getPtr();
        T getData();
        T pop_front();
        T pop_back();
        int Size();
        bool chckval(const T);
        void Sort();
        void setData(T);
        void setPtr(Node<T>*);
        void push_front(T);
        void push_back(T);
        void push_sort(T);
        friend ostream& operator << (ostream &out, Node<T> *temp){
            unsigned int i=0;
            while(temp!=NULL){
                if(i%10==0&&i!=0)cout<<endl;
                out<<temp->data<<" ";
                temp=temp->ptr;
                i++;
            }
            out<<endl;
            return out;
        }
};
template <class T>
Node<T>::Node(const T data){
    size=1;
    this->data=data;
    ptr=NULL;
}

template <class T>
Node<T>::Node(Node<T> *temp){
    if(temp!=NULL){
        size=temp->size;
        data=temp->data;
        if(temp->ptr!=NULL)ptr=new Node<T>(temp->ptr);
    }
}

template <class T>
Node<T>::~Node(){
    delete this->ptr;
}

template <class T>
Node<T> *Node<T>::getPtr(){
    return ptr;
}

template <class T>
T Node<T>::getData(){
    return data;
}

template <class T>
T Node<T>::pop_back(){
    Node<T> *temp=this;
    Node<T> *prev;
    while(temp->ptr!=NULL){
        prev=temp;
        temp=temp->ptr;
    }
    T some=temp->data;
    prev->ptr=NULL;
    size--;
    return some;
}
template <class T>
T Node<T>::pop_front(){
    Node<T> *some=new Node<T>(data);
    T dat=data;
    data=ptr->data;
    ptr=ptr->ptr;
    size--;
    return dat;
}

template <class T>
int Node<T>::Size(){
    /*int size=0;
    Node<T> *temp=this;
    while(temp!=NULL){
        temp=temp->ptr;
        size++;
    }*/
    return size;
}

template <class T>
bool Node<T>::chckval(const T data){
    Node<T> *temp=this;
    while(temp!=NULL){
        if(temp->data==data)return true;
        temp=temp->ptr;
    }
    return false;
}

template <class T>
void Node<T>::setPtr(Node<T> *temp){
    size++;
    ptr=temp;
}

template <class T>
void Node<T>::setData(T data){
    if(this->data==NULL)size++;
    this->data=data;
}

template <class T>
void Node<T>::Sort(){
    T tempD;
    Node<T> *temp;
    Node<T> *next;
    for(int i=0;i<ptr->Size()+1;i++){
        temp=this;
        next=temp->ptr;
        while(next!=NULL){
            if(temp->data>next->data){
                tempD=temp->data;
                temp->data=next->data;
                next->data=tempD;
            }
            temp=temp->ptr;
            next=temp->ptr;
        }
    }
}

template <class T>
void Node<T>::push_back(T data){
    size++;
    //Initialize the front
    Node<T> *temp=this;
    Node<T> *next=new Node<T>(data);
    while(temp->ptr!=NULL){
        temp=temp->ptr;
    }
    temp->ptr=next;
}

template <class T>
void Node<T>::push_front(T data){
    size++;
    if(this->data==NULL){
        this->data=data;
    }else{
        Node<T> *temp=new Node<T>(this->data);
        temp->ptr=ptr;
        ptr=temp;
        this->data=data;
    }
}

template <class T>
void Node<T>::push_sort(T data){
    size++;
    if(this->data==NULL){
        this->data=data;
    }
    else{
        //Initialize the front
        Node<T> *temp=this;
        while(temp->ptr!=NULL&&data>temp->data){
            temp=temp->ptr;
        }
        if(data>temp->data){
            temp->ptr=new Node<T>(data);
        }else{
            Node<T> *next=new Node<T>(temp->data);
            next->ptr=temp->ptr;
            temp->ptr=next;
            temp->data=data;
        }
    }
}
#endif /* NODE_H */

