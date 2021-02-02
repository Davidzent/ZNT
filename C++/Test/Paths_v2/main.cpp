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
#include <algorithm>
#include "Map.h"

using namespace std;

/*
 * 
 */


Map* fillMap(char*,int&);
void delMap(Map*,int&);
void printMap(Map*,int);
void printConected(Map&,int);
void findpath(Map*,int,char,char);
int findpathR(Map,char,char,string);
int main(int argc, char** argv) {
    //Declare variables
    char filename[20]="Paths.txt";
    int size;
    Map *map;
    
    //Fill Map with its phats
    map=fillMap(filename,size);
    
    //print map
    cout<<"In Map Data"<<endl;
    printMap(map,size);
    
    //Search for shortest path
    cout<<"Find Path"<<endl;
    findpath(map,size,'1','5');
    
    //delete memory
    delMap(map,size);
    return 0;
}

void findpath(Map *map,int size,char a,char b){
    int sPath;
    string s="";
    bool inmap=true;
    if(a==b){
        cout<<"The values are the same"<<endl;
        return;
    }
    for(int i=0;i<size;i++){
        if(map[i].value==a||map[i].value==b)inmap=!inmap;
    }
    if(!inmap){
        cout<<"at least one of the places inputed is not in the map"<<endl;
        return;
    }
    sPath=findpathR(map[0],a,b,s);
    cout<<"Going from "<<a<<" To "<<b<<endl;
    cout<<"The shortest path is : "<<s<<endl;
    cout<<"Distance             : "<<sPath<<endl<<endl;
}

int findpathR(Map map, char a, char b, string s){
    int min;
    int temp;
    int cnt=0;
    int i=0;
    
    if(a==b)return cnt;
    if(s.find(a)==string::npos){
        s.push_back(a);
        cnt++;
        while(map.connected[i]!=NULL){
            if(i==0){
                min=findpathR(map.connected[i][0],map.connected[i][0].value,b,s);
            }else{
                temp=findpathR(map.connected[i][0],map.connected[i][0].value,b,s);
                min<=temp?:min=temp;
            }
            i++;
        }
    }
    else{
        return cnt;
    }
    return cnt+min;
}

void printMap(Map *map, int size){
    for(int i=0;i<size;i++){
        cout<<map[i].value;
        printConected(map[i],size);
        cout<<endl;
    }
    cout<<endl;
}

void printConected(Map &map,int size){
    int i=0;
    while(map.connected[i]!=NULL)
        cout<<"->"<<map.connected[i++]->value;
    
}

Map* fillMap(char *name,int &size){
    //Declare variables
    Map *map;
    ifstream file;
    int cnt=0;
    char start;
    //open filestream
    file.open(name);
    file>>size;
    cout<<"Number of main Rooms: "<<size<<endl;
    //create
    map=new Map[size];
    string line[size];
    getline(file,line[0]);  //get first extra line
    for(int i=0;i<size;i++){
        getline(file,line[i]);
        cout<<line[i]<<endl;
        map[i].value=line[i][0];
        cnt=count(line[i].begin(),line[i].end(),'-');
        map[i].connected=new Map*[cnt+1];
    }
    cout<<endl;
    for(int i=0;i<size;i++){
        cnt=0;
        for(int j=1;j<=line[i].size()/3;j++){
            if(map[i].connected!=NULL){
                map[i].connected[cnt++]=&map[(line[i][j*3]-'1')];
            }
            map[i].connected[cnt]=NULL;
        }
        
    }
    file.close();
    return map;
}

void delMap(Map *map,int &size){
    delete map->connected;
    delete map;
}