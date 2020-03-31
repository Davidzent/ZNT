/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Dynamic2DArray.h
 * Author: david
 *
 * Created on February 18, 2019, 6:17 PM
 */

#ifndef DYNAMIC2DARRAY_H
#define DYNAMIC2DARRAY_H

#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
template <class T>
class Array{
    private:
        int row;
        int col;
        T **array;
    public:
        Array(int row,int col);
        void setVal(int row,int col,T value);
        void setRVal();
        int getRow();
        int getCol();
        void prntAry();
        ~Array();
};
template <class T>
Array<T>::Array(int row,int col){
    srand(static_cast<unsigned int>(time(0)));
    this->row=row;
    this->col=col;
    array=new T*[row];
    for(int i=0;i<row;i++){
        array[i]=new T[col];
    }
}
template <class T>
void Array<T>::setVal(int row,int col,T value){
    array[row][col]=value;
}
template <class T>
void Array<T>::setRVal(){
    //Fill the array with values
    for(int r=0;r<row;r++){
        for(int c=0;c<col;c++){
            array[r][c]=rand()%90+10;
        }
    }
}
template <class T>
int Array<T>::getRow(){
    return row;
}
template <class T>
int Array<T>::getCol(){
    return col;
}
template <class T>
void Array<T>::prntAry(){
    cout<<endl;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cout<<array[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
template <class T>
Array<T>::~Array(){
    for(int i=0;i<row;i++){
        delete []array[i];
    }
    delete []array;
}

#endif /* DYNAMIC2DARRAY_H */

