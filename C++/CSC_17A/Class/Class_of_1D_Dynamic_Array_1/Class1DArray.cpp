/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on October 10th, 2018, 1:40 PM
 * Purpose:  1D Array Class
 */

#include "Class1DArray.h"
#include <cstdlib>
using namespace std;

DynAry1::DynAry1(int n){
    n=n<2?2:n;
    n=n>100?100:n;
    array=new int[n];
    for(int i=0;i<n;i++){
        array[i]=rand()%90+10;//Random 2 Digit numbers
    }
    size=n;
}

int DynAry1::getElem(int n) const {
    if(n>=0&&n<MAX) return array[n];
}

void DynAry1::setElem(int n,int val){
    if(n>=0&&n<MAX) array[n]=val;
}