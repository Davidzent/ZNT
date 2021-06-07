/* 
 * File:   Prob2Sort.h
 * Author: Jason Handen
 * Created on June 3, 2021, 4:54 PM
 * Purpose: Problem 2 header file
 */

#ifndef PROB2SORT_H
#define PROB2SORT_H

#include <cstddef>
#include <iostream>
using namespace std;

//This class sorts arrays either ascending or descending
template<class T>
class Prob2Sort
{
    private:
        int *index;                                 //Index that is utilized in the sort
    public:
        Prob2Sort(){index=NULL;};                   //Constructor
        ~Prob2Sort(){delete []index;};              //Destructor
        T* sortArray(const T*,int,bool);            //Sorts a single column array
        T* sortArray(const T*,int,int,int,bool);    //Sorts a 2 dimensional array represented as a 1 dim array
}; 

template<class T>
T* Prob2Sort<T>::sortArray(const T *array,int row,bool asc){     //only one column to sort

}
template<class T>
T* Prob2Sort<T>::sortArray(const T *array,int row,int col,int colSort,bool asc){
    
    colSort--;
    
    
    
    T *newArray = new T[row*col];           //array to sort
    index = new int[row];
    /*
    for(short i=0;i<row;i++){
        index[i]=-1;                        //fill index array with dummy data
    }
    
    for(short i=0;i<row;i++){
        for(short j=i+1;j<row;j++){
            if(array[i*col+colSort]<array[j*col+colSort]){
                index[i]=j;
            }
        }
        if(index[i]==-1){
            index[i]=i;
        }
        cout<<"Index is "<<index[i]<<endl;
    }
    */
    for(short i=0;i<row*col;i++){
        newArray[i]=array[i];     //assign values
        cout<<newArray[i];
    }
    cout<<endl<<endl<<endl;

    for(short i=0;i<row;i++){
        for(short j=0;j<col;j++){
            newArray[i*col+j]=array[i*col+j];     //assign values
            cout<<newArray[i*col+j];
        }
    }
    cout<<endl<<endl<<endl;
    //newArray[161]='N';
    

    /*
    for(short i=0;i<row-1;i++){             //exclusive or swapping algorithm
        for(short j=i+1;j<row;j++){
            if(newArray[i*col+colSort]>newArray[j*col+colSort]){
                newArray[i*col+colSort]=newArray[i*col+colSort]^newArray[j*col+colSort];
                newArray[j*col+colSort]=newArray[i*col+colSort]^newArray[j*col+colSort];
                newArray[i*col+colSort]=newArray[i*col+colSort]^newArray[j*col+colSort];
            }
        }
        
    }
    */
    return newArray;
}

#endif /* PROB2SORT_H */
