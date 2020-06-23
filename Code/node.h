#pragma once
/*
 * File:   Node.h
 * Author: Guijosa David
 * Created on March 28th, 2018, 9:26 AM
 * Purpose:  Template Link List
 */


 //Change if file name is changed
#ifndef NODE_H
#define NODE_H

//System Libraries
#include <iostream>
using namespace std;

//if wanted change it to a normal class
template <class T>
class Node {
private:
	T data;
	Node<T>* ptr;
public:
	Node() {};			//Default constructor
	Node(const T data);		//Base data constructor
	Node(Node<T>* ptr);		//Node constructor
	~Node();			//Destructor
	void push_front(T data);	//Push data to the first pointer
	bool find(T data);		//Finds data in link list 
	//Outputs Linklist
	friend ostream& operator << (ostream& out, Node<T>* temp) {
		while (temp != NULL) {
			out << temp->data << " ";
			temp = temp->ptr;
		}
		out << endl;
		return out;
	}
};
template <class T>
Node<T>::Node(const T data) {
	this->data = data;
	ptr = NULL;
}

template <class T>
Node<T>::Node(Node<T>* temp) {
	data = temp->data;
	ptr = temp->ptr;
}

template <class T>
Node<T>::~Node() {
	Node<T>* temp = ptr;
	do {
		temp = temp->ptr;
		delete ptr;
		ptr = temp;
	} while (temp != NULL);
}
template <class T>
void Node<T>::push_front(T data){
	Node<T>* temp = new Node<T>(this->data);	temp->ptr;	ptr = temp;	this->data = data;

}
template <class T>
bool Node<T>::find(T data) {
	Node<T>* temp = ptr;
	if (this->data == data)
	{
		return true;
	}

	 while (temp != NULL)
	 {
		temp = temp->ptr;

		if (temp->data == data)
		{
			return true;
		}		
	 } 
	 return false;
}
#endif
//Questions? Discord Zentinel#2376