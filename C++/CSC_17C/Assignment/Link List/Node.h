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
        T getData();
        void setData(T);
        Node<T> *getPtr();
        void setPtr(Node<T>*);
        T pop_front();
        T pop_back();
        void push_front(T);
        void push_back(T);
        friend ostream& operator << (ostream &out, Node<T> *temp){
            do{
                out<<temp->data<<endl;
                temp=temp->ptr;
            }while(temp!=NULL);
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
void Node<T>::setData(T data){
    this->data=data;
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
void Node<T>::setPtr(Node<T> *temp){
    ptr=temp;
}

template <class T>
T Node<T>::pop_front(){
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
T Node<T>::pop_back(){
    Node<T> *some=new Node<T>(data);
    T dat=data;
    data=ptr->getData();
    ptr=ptr->getPtr();
    return dat;
}

template <class T>
void Node<T>::push_front(T data){
    //Initialize the front
    Node<T> *temp=ptr;
    Node<T> *next=new Node<T>(data);
    while(temp->getPtr()!=NULL){
        temp=temp->getPtr();
    }
    temp->setPtr(next);
}

template <class T>
void Node<T>::push_back(T data){
    Node<T> *temp=new Node<T>(this->data);
    temp->setPtr(ptr);
    ptr=temp;
    this->data=data;
}


#endif /* NODE_H */

