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
        T data;
        Node<T> *ptr;
    public:
        Node(const T);
        Node(Node<T>*);
        ~Node();
        Node<T> *getPtr();
        T getData();
        T pop_front();
        T pop_back();
        int Size();
        bool duplict(const T);
        void Sort();
        void setData(T);
        void setPtr(Node<T>*);
        void push_front(T);
        void push_back(T);
        friend ostream& operator << (ostream &out, Node<T> *temp){
            while(temp!=NULL){
                out<<temp->data<<" -> ";
                temp=temp->ptr;
            }
            out<<endl;
            return out;
        }
};
template <class T>
Node<T>::Node(const T data){
    this->data=data;
    ptr=NULL;
}

template <class T>
Node<T>::Node(Node<T> *temp){
    data=temp->getData();
    ptr=temp->getPtr();
}

template <class T>
Node<T>::~Node(){
    Node<T> *temp=ptr;
    do{
        temp=temp->ptr;
        delete ptr;
        ptr=temp;
    }while(temp!=NULL);
}

template <class T>
Node<T> *Node<T>::getPtr(){
    return ptr;
}
template <class T>
bool Node<T>::duplict(const T data){
    Node<T> *temp=ptr;
    if(this->data==data)return true;
    while(temp!=NULL){
        if(temp->data==data)return true;
        temp=temp->ptr;
    }
    return false;
}

template <class T>
T Node<T>::getData(){
    return data;
}

template <class T>
T Node<T>::pop_back(){
    Node<T> *temp=ptr;
    Node<T> *prev;
    while(temp->getPtr()!=NULL){
        prev=temp;
        temp=temp->getPtr();
    }
    T some=temp->getData();
    prev->setPtr(NULL);
    return some;
}
template <class T>
T Node<T>::pop_front(){
    T dat=data;
    if(ptr!=NULL){
        data=ptr->getData();
        ptr=ptr->ptr;
    }
    return dat;
}

template <class T>
int Node<T>::Size(){
    int size=0;
    Node<T> *temp=ptr;
    while(temp!=NULL){
        temp=temp->getPtr();
        size++;
    }
    return size;
}

template <class T>
void Node<T>::setPtr(Node<T> *temp){
    ptr=temp;
}

template <class T>
void Node<T>::setData(T data){
    this->data=data;
}

template <class T>
void Node<T>::Sort(){
    T tempD;
    Node<T> *temp;
    Node<T> *next;
    for(int i=0;i<ptr->Size()+1;i++){
        temp=ptr;
        next=temp->getPtr();
        if(data>temp->getData()){
            tempD=data;
            data=temp->getData();
            temp->setData(tempD);
        }
        while(next!=NULL){
            if(temp->getData()>next->getData()){
                tempD=temp->getData();
                temp->setData(next->getData());
                next->setData(tempD);
            }
            temp=temp->getPtr();
            next=temp->getPtr();
        }
    }
}

template <class T>
void Node<T>::push_back(T data){
    //Initialize the front
    Node<T> *temp=new Node<T>(data);
    Node<T> *temp2=ptr;
    Node<T> *prev=this;
    while(temp2!=NULL){
        prev=temp2;
        temp2=temp2->ptr;
    }
    prev->setPtr(temp);
}

template <class T>
void Node<T>::push_front(T data){
    Node<T> *temp=new Node<T>(this->data);
    temp->setPtr(ptr);
    ptr=temp;
    this->data=data;
}


#endif /* NODE_H */