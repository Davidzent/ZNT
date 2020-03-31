/* 
 * File:   main.cpp
 * Author: Dr Mark E. Lehr
 * Created on October 10th, 2018, 1:40 PM
 * Purpose:  1D Array Class
 */

#ifndef CLASS1DARRAY_H
#define CLASS1DARRAY_H

class DynAry1{
    private:
        int size;
        int *array;
        const int MAX=100;
    public:
        DynAry1(int);
        ~DynAry1(){delete []array;}
        int getSize()const {return size;}
        int getElem(int) const;
        void setElem(int,int);
};

#endif /* CLASS1DARRAY_H */