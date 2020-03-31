/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   MAPS.cpp
 * Author: rcc
 *
 * Created on November 21, 2018, 12:44 PM
 */

#include <iostream>
#include <iomanip>
#include "Maps.h"
using namespace std;

MAP::MAP(){
    row=0;
    col=0;
}
MAP::MAP(int row,int col){
    this->row=row;
    this->col=col;
}
void MAP::setrow(int row){
    this->row=row;
}
void MAP::setcol(int col){
    this->col=col;
}
void MAP::setnmin(int nmines){
    this->nmines=nmines;
}
int MAP::getcol()const{
    return col;
}
int MAP::getrow()const{
    return row;
}
int MAP::getnmin() const{
    return nmines;
}
void MAP::shufle(){
    for(int nShuf=0;nShuf<=7;nShuf++){
        for(int i=0;i<row;i++){
            for (int j=0;j<col;j++){
                int random=rand()%row;
                int random2=rand()%col;
                char temp=map[i][j];
                map[i][j]=map[random][random2];
                map[random][random2]=temp;
            }        
        }
    }
}
void MAP::cntmine(){
    for(int j=0;j<row;j++){
        for (int i=0;i<col;i++){
            if(map[i][j]=='X'&&i!=0&&j!=0&&i!=9&&j!=9){
                for(int x=i-1;x<i+1;x++){
                    for(int y=j-1;y<=j+1;y++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }  
            }
            else if(map[i][j]=='X'&&i==0&&j==0){ //non-mine counter for the
                for(int x=i;x<i+1;x++){
                    for(int y=j;y<=j+1;y++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&i==9&&j==9){ //non-mine counter for the
                for(int x=i-1;x<i;x++){
                    for(int y=j-1;y<=j;y++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&i==0&&j==9){   //non-mine counter for 
                for(int x=i;x<i+1;x++){
                    for(int y=j-1;y<=j;y++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&i==9&&j==0){  //non-mine counter for 
                for(int x=i-1;x<i;x++){
                    for(int y=j;y<=j+1;y++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&i==0&&j>0&&j<9){   //non-mine counter for
                for(int x=i;x<i+1;x++){
                    for(int y=j-1;y<=j;y++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&i==9&&j>0&&j<9){//non-mine counter for the
                for(int x=i-1;x<i;x++){
                    for(int y=j-1;y<=j+1;y++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&j==0&&i>0&&i<9){   //non-mine counter for 
                for(int x=i-1;x<i+1;x++){
                    for(int y=j;y<=j+1;y++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&j==9&&i>0&&i<9){   //bottom corner line
                for(int x=i-1;x<i+1;x++){
                    for(int y=j-1;y<=j;y++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
        }
    }
}
void MAP::crtmaps(){
    map=new char*[row];
    index=new char*[row];
    for(int i=0;i<row;i++){
        map[i]=new char[col];
        index[i]=new char[col];
    }
    for(int i=0,x=0;i<row;i++,x++){
        for(int j=0;j<col;j++,x++){
            if(x<nmines)map[i][j]='X';
            else map[i][j]='0';
            index[i][j]='?';
        }
    }
    shufle();
    cntmine();
}
void MAP::reveal(int y,char x){
    index[y][x]=map[y][x];
    
}
void MAP::prntmap(){
    cout<<"#  A B C D E F G H I J"<<endl;
    cout<<"  ____________________"<<endl;
    for(int i=0;i<row;i++){
        cout<<i<<"|";
        for(int j=0;j<col;j++){
            cout<<setw(2)<<map[i][j];
        }
        cout<<endl;
    }
}
void MAP::prtindx(){
    cout<<"#  A B C D E F G H I J"<<endl; 
    cout<<"  ____________________"<<endl;
    for(int i=0;i<row;i++){
        cout<<i<<"|";
        for(int j=0;j<col;j++){
            index[i][j]='?';
            cout<<setw(2)<<index[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}
MAP::~MAP(){
    for(int i=0;i<row;i++){
        delete map[i];
        delete index[i];
    }
    delete []map;
    delete []index;
}
