/* 
 * File:   main.cpp
 * Author: David Guijosa
 *
 * Created on May 22, 2019, 9:40 AM
 */


//System libraries
#include <iostream> //out/in
#include <ctime>    //Time function
#include <fstream>  //files
#include <stdlib.h> //qsort  - Sort String
#include <string.h> //strcmp - Compare strings
using namespace std;

//User Libraries
#include "Array.h"

//Functions
ary filstr(char[]);
void cpyData(const ary,ary&);
string getWord(char[]);
int linSrch(ary,string);
int binSrch(ary,int,int,string);
void sort(ary);
int hshSrch(ary,string);
static int myCompare(const void *, const void *); 
void prnt(ary);
void sndfile(ary,char[]);
void deltstr(ary);

int main(int argc, char** argv) {
    //Declare and initialize variables
    char flname[10]="words.txt";
    char outname[11]="sorted.txt";
    char srcname[11]="search.txt";
    string word=getWord(srcname); //word to search
    ary data=filstr(flname);
    ary data2;
    ary data3;
    int posLin;
    int posBin;
    int posHsh;
    
    //Copy data structure
    cpyData(data,data2);
    cpyData(data,data3);
    
    /*//print data
    prnt(data);
    cout<<endl;
    prnt(data2);
    cout<<endl;
    prnt(data3)*/
    
    //linear search
    posLin=linSrch(data,word);
    //binary search
    sort(data2);
    posBin=binSrch(data2,0,data2.size-1,word);
    //hash search
    posHsh=hshSrch(data3,word);
    
    
    cout<<"Word to search: "<<word<<endl;
    
    cout<<"Linear search: ";
    posLin>0?cout<<"The word was found in position = "<<posLin<<endl:
        cout<<"The word was NOT found in data"<<endl;
    
    cout<<"Binary search in sorted array: ";
    posBin>0?cout<<"The word was found in position = "<<posBin<<endl:
        cout<<"The word was NOT found in data"<<endl;
    if(posBin!=linSrch(data2,word))cout<<"Something is wrong with the binary search"<<endl;
    
    cout<<"Hash   search: ";
    posHsh>0?cout<<"The word was found in position = "<<posHsh<<endl:
        cout<<"The word was NOT found in data"<<endl;
    //print array
    //prnt(data);
    
    //send data to a file
    sndfile(data2,outname);
    
    //delete allocated memory
    deltstr(data);
    deltstr(data2);
    deltstr(data3);
    //Exit
    return 0;
}

ary filstr(char name[]){
    ary data;
    ifstream file;
    file.open(name);
    file>>data.size;
    data.array=new string[data.size];
    for(int i=0;i<data.size;i++){
        file>>data.array[i];
    }
    return data;
}

void cpyData(const ary data,ary &data2){
    data2.size=data.size;
    data2.array=new string[data.size];
    for(int i=0;i<data.size;i++){
        data2.array[i]=data.array[i];
    }
}

string getWord(char name[]){
    ifstream file;
    file.open(name);
    string word;
    file>>word;
    return word;
}

int linSrch(ary data,string sr){
    for(int i=0;i<data.size;i++){
        if(data.array[i]==sr)return i+1;
    }
    return -1;
}

int binSrch(ary data,int start,int max,string x) { 
    if (max>=start){ 
        int mid=start+(max-start)/2; 
        if (data.array[mid]==x)return mid+1; 
        if (data.array[mid]>x)return binSrch(data,start,mid-1,x); 
        return binSrch(data,mid+1,max,x); 
    } 
    return -1; 
} 
// Function to sort the array 
void sort(ary data){ 
    // calling qsort function to sort the array 
    // with the help of Comparator 
    qsort(data.array,data.size, sizeof(const string), myCompare); 
}
static int myCompare(const void *a, const void *b) { 
    // setting up rules for comparison 
    return strcmp(*(const char**)a, *(const char**)b); 
} 

int hshSrch(ary,string){
    return -1;
}

void prnt(ary data){
    for(int i=0;i<data.size;i++){
        if(i%10==0)cout<<endl;
        cout<<data.array[i]<<" ";                
    }
}

void sndfile(ary data,char name[]){
    ofstream out;
    out.open(name);
    out<<data.size<<" ";
    for(int i=0;i<data.size;i++){
        out<<data.array[i]<<" ";
    }
    out.close();
}

void deltstr(ary data){
    delete []data.array;
}