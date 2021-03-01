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
#include <map>
#include "Map.h"

using namespace std;

/*
 * 
 */


Map* fillMap(char*,char*,int&);
void delMap(Map*,int&);
void printMap(Map*,int);
void printConected(Map&,int);
void findpath(Map*,int,char,char);
pair<string, float> findpathR(Map,char,char,string,float);

int main(int argc, char** argv) {
    //Declare variables
    char filePaths[20]="Paths.txt";
    char fileDistance[20]="distance.txt";
    int size;
    Map *map;
    
    //Fill Map with its phats
    map=fillMap(filePaths,fileDistance,size);
    
    //print map
    cout<<"In Map Data"<<endl;
    printMap(map,size);
    
    //Search for shortest path
    cout<<"Find Path"<<endl;
    findpath(map,size,'1','0');
    
    //delete memory
    delMap(map,size);
    return 0;
}

void findpath(Map *map,int size,char a,char b){
    pair<string, int> sPath;
    string s="";
    int nloops=1;
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
    int beg=time(0);
    for(int i=0;i<nloops;i++)
        sPath=findpathR(map[0],a,b,s,0);
    int end=time(0);
    cout<<"Going from "<<a<<" To "<<b<<endl;
    cout<<"The shortest path is : "<<sPath.first<<endl;
    cout<<"Distance             : "<<sPath.second<<endl;
    cout<<"Loops                : "<<nloops<<endl;
    cout<<"Time                 : "<<end-beg<<endl<<endl;
}

pair<string, float> findpathR(Map map, char a, char b, string s,float distance){
    pair<string, float> min;
    pair<string, float> temp;
    min.second=distance;
    min.first=s;
    int i=0;
    int x=0;
    if(a==b){
        min.first.push_back(a);
        return min;
    }
    if(s.find(a)==string::npos){
        s.push_back(a);
        s.push_back('-');
        s.push_back('>');
        while(map.connected[i]!=NULL){
            if(i==x){
                temp=findpathR(map.connected[i][0],map.connected[i][0].value,b,s,map.distance[i]);
                if(temp.second!=-1){
                    min.first=temp.first;
                    min.second=temp.second;
                }else x++;
            }else{
                temp=findpathR(map.connected[i][0],map.connected[i][0].value,b,s,map.distance[i]);
                if(temp.second!=-1&&min.second>temp.second){
                    min.second=temp.second;
                    min.first=temp.first;
                }
            }
            i++;
        }
    }
    else{
        min.second=-1;
        return min;
    }
    min.second+=distance;
    return min;
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
        cout<<" -> "<<map.connected[i]->value<<" D = "<<map.distance[i++];
    
}

Map* fillMap(char *Paths, char *Distance,int &size){
    //Declare variables
    Map *map;
    ifstream file;
    int cnt=0;
    char start;
    //open filestream
    file.open(Paths);
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
        map[i].npaths=cnt;
        map[i].connected=new Map*[cnt+1];
        map[i].distance=new float[cnt];
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
    file.open(Distance);
    for(int i=0;i<size;i++){
        for(int j=0;j<map[i].npaths;j++){
            file>>map[i].distance[j];
        }
    }
    file.close();
    return map;
}

void delMap(Map *map,int &size){
    delete map->connected;
    delete map;
}