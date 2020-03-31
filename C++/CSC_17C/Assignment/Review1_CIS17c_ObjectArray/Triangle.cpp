/* 
 * File:   Triangle.h
 * Author: Guijosa David
 * Created on January 22nd, 2019, 8:36 PM
 * Purpose:  Specification of a Triangular array from a Row Array
 */

#include "Triangle.h"


Triangle::Triangle(int szRow){
    this->szRow=szRow;
    records=new RowAray*[szRow];
    for(int i=0;i<szRow;i++){
        records[i]=new RowAray (i+1);
    }
}
Triangle::~Triangle(){
    for(int i=0;i<szRow;i++){
        delete records[i];
    }
    delete []records;
      
}
int Triangle::getData(int y,int x){
    return records[y]->getData(x);
}


