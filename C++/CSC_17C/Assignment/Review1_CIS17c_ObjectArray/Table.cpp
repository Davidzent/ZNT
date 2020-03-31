/* 
 * File:   Table.h
 * Author: Guijosa David
 * Created on January 22nd, 2019, 8:36 PM
 * Specification for the Table
 */

#include "Table.h"


Table::Table(int szRow,int szCol){
    this->szCol=szCol;
    this->szRow=szRow;
    records=new RowAray*[szRow];
    for(int i=0;i<szRow;i++){
        records[i]=new RowAray (szCol);
    }
}
Table::~Table(){
    for(int i=0;i<szRow;i++){
        delete records[i];
    }
    delete []records;
}
int Table::getData(int i,int x){
    return records[i]->getData(x); 
}