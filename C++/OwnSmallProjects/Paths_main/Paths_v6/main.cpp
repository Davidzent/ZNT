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

//data
/*
  nPaths   total        sec
    12      12^2          8
    13      13^2         59
    14      14^2        444
    15      15^2       3498
    16      16^2       
 */


//
Map* fillMap(char*,char*,int&);
void delMap(Map*,int&);
void printMap(Map*,int);
void printConected(Map&,int);
void findpath(Map*,int,string,string&);
pair<int,int> MinMax(Map&,int&,string);
pair<string, float> findpathR(Map&,string,string&,string,float);

int main(int argc, char** argv) {
    //Declare variables
    char filePaths[20]="../Paths.txt";
    char fileDistance[20]="../Distance.txt";
    string from="1";
    string to="3";
    int size;
    Map *map;

    //Fill Map with its phats
    map=fillMap(filePaths,fileDistance,size);
    
    //print map
    cout<<"In Map Data"<<endl;
    printMap(map,size);
    
    //Search for shortest path
    cout<<"Find Path"<<endl;
    findpath(map,size,from,to);
    
    //delete memory
    delMap(map,size);
    return 0;
}

void findpath(Map *map,int size,string a,string &b){
    pair<string, int> sPath;
    string s="";
    float nloops=1;
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
    //cout<<"Going from "<<a<<" To "<<b<<endl;
    //cout<<"The shortest path is : "<<sPath.first<<endl;
    //cout<<"Distance             : "<<sPath.second<<endl;
    //cout<<"Loops                : "<<nloops<<endl;
    //cout<<"Time                 : "<<(end-beg)<<endl<<endl;
    //cout<<"Average Time                 : "<<(end-beg)/nloops<<endl<<endl;
}

pair<string, float> findpathR(Map &map, string a, string &b, string s,float distance){
    pair<string, float> min;
    pair<string, float> temp;
    min.second=distance;
    min.first=s;
    if(a==b){
        min.first+=a;
        return min;
    }
    if(s.find(a)==string::npos){
        pair<int,int> pos;
        pair<int,int> pos2;
        Map *maptemp=&map.connected[pos.first][0];
        s+=a;
        s.push_back('-');
        s.push_back('>');
        pos=MinMax(map,map.npaths,s);
        pos2=MinMax(*maptemp,maptemp->npaths,s+maptemp->value);
        cout<<s<<endl;
        cout<<"first path: "<<pos.first<<" "<<pos.second<<endl;
        cout<<s+maptemp->value<<endl;
        cout<<"second path: "<<pos2.first<<" "<<pos2.second<<endl;
        cout<<"The shortest path: "<<s+maptemp->value+maptemp->connected[pos2.first][0].value<<endl;
        
    }
    else{
        min.second=-1;
        return min;
    }
    min.second+=distance;
    return min;
}
pair<int,int> MinMax(Map &map,int &npaths,string s){
    float min=map.distance[0];
    float max=map.distance[0];
    pair<int,int> pos;
    pos.first=0;
    pos.second=0;
    for(int i=1;i<npaths;i++){
        if(s.find(map.connected[i]->value)==string::npos){
            if(map.distance[i]<min){
                min=map.distance[i];
                pos.first=i;
            }
            if(map.distance[i]>max){
                max=map.distance[i];
                pos.second=i;
            }
        }
    }
    return pos;
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
    for(int i=0;i<map.npaths;i++){
        cout<<" -> "<<map.connected[i]->value<<" D = "<<map.distance[i];
    }
}

Map* fillMap(char *Paths, char *Distance,int &size){
    //Declare variables
    Map *map;
    ifstream file;
    ifstream file2;
    int cnt=0;
    int start=0;
    int ends=0;
    int temp=0;
    //open filestream
    file.open(Paths);
    file2.open(Distance);
    file>>size;
    cout<<"Number of main Rooms: "<<size<<endl;
    //create
    map=new Map[size];
    string line[size];
    getline(file,line[0]);  //get first extra line
    for(int i=0;i<size;i++){
        getline(file,line[i]);
        map[i].value=line[i].substr(0,line[i].find('>',0));
        cnt=count(line[i].begin(),line[i].end(),'>');
        map[i].npaths=cnt;
        map[i].connected=new Map*[cnt+1];
        map[i].distance=new float[cnt+1];
        for(int j=0;j<cnt;j++){
            file2>>map[i].distance[j];
        }
        cout<<line[i]<<endl;
    }
    cout<<endl;
    for(int i=0;i<size;i++){
        cnt=0;
        start=line[i].find('>',0)+1;
        for(int j=1;j<=map[i].npaths;j++){
            if(map[i].connected!=NULL){
                if(j<map[i].npaths){
                    ends=line[i].find('>',start);
                    temp=ends;
                    ends=stoi(line[i].substr(start,ends))-1;
                    map[i].connected[cnt++]=&map[ends];
                    start=temp+1;
                }
                else{
                    ends=stoi(line[i].substr(start))-1;
                    map[i].connected[cnt++]=&map[ends];
                }
            }
        }
        
        //printConected(map[i],size);
        //cout<<endl;
        
    }
    file.close();
    file2.close();
    return map;
}

void delMap(Map *map,int &size){
    delete []map->connected;
    delete []map->distance;
    delete []map;
}