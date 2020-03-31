/* 
 * File:   RowAray.h
 * Author:  Guijosa David
 * Created on January 22nd, 2019, 8:36 PM
 * Specification for the RowAray
 */

#include <cstdlib>
#include <ctime>

#include "RowAray.h"

RowAray::RowAray(int size){   
    this->size=size;
    rowData=new int[size];
    for(int i=0;i<size;i++)rowData[i]=rand()%90+10;
}
RowAray::~RowAray(){
    delete []rowData;
}