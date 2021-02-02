/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Problem 2 Sort.h
 * Author: gabriel
 *
 * Created on December 10, 2018, 12:21 PM
 */

#ifndef PROBLEM_2_SORT_H
#define PROBLEM_2_SORT_H


#include <iostream>
using namespace std;

template<class T>
class Prob2Sort
{
	private:
		T *index;                                 //Index that is utilized in the sort
	public:
		Prob2Sort(){index=NULL;};                   //Constructor
		~Prob2Sort(){delete []index;};              //Destructor
		T * sortArray(const T* aray,int size,bool acending){           //Sorts a single column array
                    for(int i=0;i<size-1;i++){
                        for(int j=i+1;j<size;j++){
                            if(aray[i]>aray[j]&&acending){
                                aray[i]=aray[i]^aray[j];
                                aray[j]=aray[i]^aray[j];
                                aray[i]=aray[i]^aray[j];
                            }
                            if(aray[i]<aray[j]&&acending){
                                aray[i]=aray[i]^aray[j];
                                aray[j]=aray[i]^aray[j];
                                aray[i]=aray[i]^aray[j];
                            }
                        }
                    }
                    return aray;
                }
		T * sortArray(const T* aray,int row,int col,int tochange,
                        bool acending){   //Sorts a 2 dimensional array represented as a 1 dim array
                    index=new T[row];
                    for(int i=0;i<row*col;i++){
                            index[i]=aray[i];
                            cout<<index[i];
                    }
                    cout<<endl;
                    cout<<endl;
                        for(int i=0,y=-1;i<row-1;i++,y++){
                            for(int j=i+1,x=i;j<row;j++,x++){
                                if(index[i*col+tochange+y]>index[j*col+tochange+x]&&acending){
                                    T temp=index[i*col+tochange+y];
                                    index[i*col+tochange+y]=index[j*col+tochange+x];
                                    index[j*col+tochange+x]=temp;
                                }
                                if(index[i*col+tochange+y]<index[j*col+tochange+x]&&!acending){
                                    T temp=index[i*col+tochange+y];
                                    index[i*col+tochange+y]=index[j*col+tochange+x];
                                    index[j*col+tochange+x]=temp;
                                }
                            }
                        } 
                    return index;
                    }
}; 
#endif /* PROBLEM_2_SORT_H */
//0123456789\0 10
//0123456789\0
