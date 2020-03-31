/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   inher.h
 * Author: Guijosa, David
 *
 * Created on December 11, 2018, 10:31 PM
 */

#ifndef INHER_H
#define INHER_H

template <class T>
class Prob3TableInherited{
	protected:
		T *augTable;     //Augmented Table with sums
                int rows;                                 //Number of rows in the table
		int cols;                                 //Number of cols in the table
                T sum;
		T *table;                                 //Table array
		void calcTable(void);                     //Calculate all the sums
	public:
		Prob3TableInherited(char *nm,int row,int col){  //Constructor
                    ifstream infile;
                    infile.open(nm,ios::in);
                    this->rows=row;
                    this->cols=col;
                    sum=0;
                    table=new T[row*col];
                    augTable=new T[(row+1)*(col+1)];
                    int i=0,x=0;
                    while(infile>>this->augTable[i+x]){
                        table[i]=augTable[i+x];
                        if(i%col==col-1&&i!=0)x++;
                        i++;
                        
                    }
                    for(int i=(row)*(col+1);i<(row+1)*(col+1);i++){
                        for(int j=i-((row)*(col+1));j<(row)*(col+1);j+=col+1){
                                augTable[i]+=augTable[j];
                        }
                    }
                    for(int i=col,x=0;i<(row+1)*(col+1);i+=col,x++){
                        augTable[i+x]=0;
                        for(int j=0;j<col;j++){
                                augTable[i+x]+=augTable[j+(x*col)+x];
                        }
                    }
                    
                }     
                const T* getTable(){return table;}
		~Prob3TableInherited(){delete [] augTable;delete []table;}
		const T *getAugTable(void){return augTable;}
};


#endif /* INHER_H */