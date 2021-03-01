/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on December 9, 2020, 3:37 PM
 */

#include <fstream>
#include <cstdlib>
#include <iostream>
#include "Map.h"

using namespace std;

/*
 * 
 */


Map* fillMap(char*,int&);
void delMap(Map*,int&);
void printMap(Map*,int&);
void printConected(Map&,int&);
int main(int argc, char** argv) {
    //Declare variables
    char *filename="infile.txt";
    int size;
    Map *map;
    
    //Fill Map
    map=fillMap(filename,size);
    
    cout<<"Conected"<<endl;
    printMap(map,size);
    
    //delete memory
    delMap(map,size);
    return 0;
}
void printMap(Map *map, int &size){
    for(int i=0;i<size;i++){
        cout<<map[i].value;
        printConected(map[i],size);
        cout<<endl;
    }
}

void printConected(Map &map,int &size){
    
    for(int i=0;i<size;i++){
        if(map.connected[i]!=NULL)
            cout<<"->"<<map.connected[i]->value;
    }
}

Map* fillMap(char *name,int &size){
    //Declare variables
    Map *map;
    ifstream file;
    int cnt=0;
    
    //open filestream
    file.open(name);
    file>>size;
    cout<<size<<endl;
    
    //create
    map=new Map[size];
    string line[size];
    getline(file,line[0]);  //get first extra line
    for(int i=0;i<size;i++){
        getline(file,line[i]);
        cout<<line[i]<<endl;
        map[i].value=line[i][0];
        map[i].connected=new Map*[size];
    }
    cout<<"check"<<endl;
    for(int i=0;i<size;i++){
        for(int j=1;j<=line[i].size()/3;j++){
            map[i].connected[cnt++]=&map[(line[i][j*3]-'1')];
            cout<<(line[i][j*3]-'0')<<" ";
        }
        cout<<endl;
        cnt=0;
    }
    return map;
}

void delMap(Map *map,int &size){
    delete map;
}