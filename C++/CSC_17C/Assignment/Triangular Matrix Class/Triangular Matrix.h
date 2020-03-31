/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Triangular Matrix.h
 * Author: david
 *
 * Created on February 18, 2019, 5:10 PM
 */

#ifndef TRIANGULAR_MATRIX_H
#define TRIANGULAR_MATRIX_H


#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

class TrgMtrx{
    private:
        int size;
        int **array;
        int max;
        int min;
    public:
        TrgMtrx();
        TrgMtrx(int size);//create an array by declaring one size
        TrgMtrx(int size,int max,int min);//constructor for all values
        ~TrgMtrx();       //clear data
        void prntAry();   //print triangular array
        void SetVal(int row,int col);           //set one specific value 
        void SetRVal();                         //set a random value to all data
        void setRVal(int row,int col);          //set a random value to one data
        void SetRng(int max,int min);           //set maximum and minimum values
};


#endif /* TRIANGULAR_MATRIX_H */

