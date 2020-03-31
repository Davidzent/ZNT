/*
 * Author: Guijosa, David
 * Created on Feb 25th, 2019, 8:54 AM
 */

#include <cstdlib>
#include <ctime>
#include "RowAray.h"

RowAray::RowAray(unsigned int size){
    this->size=size;
    rowData=new int[size];
    for(int i=0;i<size;i++){
        rowData[i]=rand()%90+10;
    }
}
RowAray::~RowAray(){
    delete[]rowData;
}
void RowAray::setData(int n,int data){
    rowData[n]=data;
}