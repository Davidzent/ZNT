/* 
 * File:   Table.h
 * Author: Guijosa David
 * Created on January 22nd, 2019, 8:36 PM
 * Specification for the Table
 */

#ifndef TABLE_H
#define	TABLE_H

#include "RowAray.h"

template <class T>
class Table{
    private:
        int szRow;
        int szCol;
        RowAray<T> **records;
    public:
        Table(int ,int);
        Table(const Table <T>&);
        ~Table();
        int getSzRow()const;
        int getSzCol()const;
        void setData(const int,const int,const T);
        T getData(const int, const int);
        Table<T> operator+(Table<T> &a){
            Table<T> b(a.getSzRow(),a.getSzCol());
            for(int i=0;i<a.getSzRow();i++){
                for(int j=0;j<a.getSzCol();j++){
                    b.setData(i,j,a.getData(i,j)+this->getData(i,j));
                }
            }
            return b;
        }
};

template <class T>
Table<T>::Table(int szRow,int szCol){
    this->szCol=szCol;
    this->szRow=szRow;
    records=new RowAray<T>*[szRow];
    for(int i=0;i<szRow;i++){
        records[i]=new RowAray<T>(szCol);
    }
}
template <class T>
Table<T>::Table(const Table <T> &a){
    this->szCol=a.getSzCol();
    this->szRow=a.getSzRow();
    records=new RowAray<T>*[szRow];
    for(int i=0;i<szRow;i++){
        records[i]=new RowAray<T>(szCol);
    }
}

template <class T>
int Table<T>::getSzRow()const{return szRow;}

template <class T>
int Table<T>::getSzCol()const{return szCol;}

template <class T>
void Table<T>::setData(int row,int col,T data){
    records[row]->setData(col,data);
}

template <class T>
Table<T>::~Table(){
    for(int i=0;i<szRow;i++){
        delete records[i];
    }
    delete []records;
}
template <class T>
T Table<T>::getData(const int i,const int x){
    return records[i]->getData(x); 
}


#endif	/* TABLE_H */

