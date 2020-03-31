/* 
 * Author: Guijosa David
 * Created on Feb 25th, 2019, 8:54 AM
 * Specification for the Table addition operator
 */

#ifndef PLUSTAB_H
#define	PLUSTAB_H

#include "Table.h"
#include <iostream>
using namespace std;

class PlusTab:public Table{
    public:
        PlusTab(unsigned int r,unsigned int c):Table(r,c){};
        PlusTab operator+(const PlusTab &a){
            PlusTab b(szRow,szCol);
            for(int i=0;i<szRow;i++){
                for(int j=0;j<szCol;j++){
                    b.setData(i,j,this->getData(i,j)+a.getData(i,j));
                }
            }
            return b;
        };  
};

#endif	/* PLUSTAB_H */