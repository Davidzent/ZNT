/*
 * Author: Guijosa, David
 * Created on Feb 25th, 2019, 8:54 AM
 */
#include "Table.h" 

Table::Table(unsigned int szRow,unsigned int szCol){
    this->szCol=szCol;
    this->szRow=szRow;
    this->columns=new RowAray*[szRow];
    for(int i=0;i<szRow;i++){
        columns[i]=new RowAray(szCol);
    }
}
Table::Table(const Table &b){
    szCol=b.getSzCol();
    szRow=b.getSzRow();
    this->columns=new RowAray*[szRow];
    for(int i=0;i<szRow;i++){
        columns[i]=new RowAray(szCol);
    }
}
Table::~Table(){
    for(int i=0;i<szRow;i++){
        delete columns[i];
    }
    delete []columns;
}

int Table::getData(int row,int col)const{
    return columns[row]->getData(col);
}
void Table::setData(int row,int col,int data){
    columns[row]->setData(col,data);
}