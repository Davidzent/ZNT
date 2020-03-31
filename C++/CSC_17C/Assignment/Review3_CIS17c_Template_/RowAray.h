/* 
 * File:   RowAray.h
 * Author:  Guijosa David
 * Created on January 22nd, 2019, 8:36 PM
 * Specification for the RowAray
 */

#ifndef ROWARAY_H
#define	ROWARAY_H

template <class T>

class RowAray{
    private:
        int size;
        T *rowData;
    public:
        RowAray(const int);
        ~RowAray();
        int getSize()const;
        T getData(const int)const;
        void setData(const int,const T);
};

template <class T>
int RowAray<T>::getSize()const{return size;}

template <class T>
T RowAray<T>::getData(const int i)const{return rowData[i];}

template <class T>
RowAray<T>::RowAray(const int size){   
    this->size=size;
    rowData=new T[size];
    for(int i=0;i<size;i++)rowData[i]=rand()%90+10;
}
template <class T>
RowAray<T>::~RowAray(){
    delete []rowData;
}
template <class T>
void RowAray<T>::setData(const int n,const T data){
    rowData[n]=data;
}

#endif	/* ROWARAY_H */