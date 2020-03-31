/* 
 * File:   main.cpp
 * Author: David Guijosa
 *
 * Created on May 21, 2019, 1:11 PM
 */

//system libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

using namespace std;

// Functions 
string* fillary(int,int);
void prnt(string*,int);
void sndfile(string*,int,char[]);

//main
int main(int argc, char** argv) {
    //set random seed
    srand(static_cast<unsigned int>(time(0)));
    //declare variables
    int size=50000000;    //Number of words
    int wordsz=20;   //Size of words
    char flname[10]="words.txt";
    string *array=fillary(size,wordsz);
    //print array for test
    //prnt(array,size);
    //Send words to a file
    sndfile(array,size,flname);
    //delete memory
    delete array;
    
    return 0;
}

string* fillary(int n,int wordsz){
    string* ary=new string[n];
    string word;
    char letter;
    for(int i=0;i<n;i++){
        for(int j=0;j<wordsz;j++){
            if(j==0)letter=rand()%25+65;
            else letter=rand()%25+97;
            word+=letter;
        }
        ary[i]=word;
        word="";
    }
    return ary;
}
void prnt(string* ary,int n){
    cout<<"Random words generated: "<<endl;
    for(int i=0;i<n;i++){
        cout<<ary[i]<<endl;
    }
}
void sndfile(string *array,int n,char name[]){
    ofstream out;
    out.open(name);
    out<<n<<" ";
    for(int i=0;i<n;i++){
        out<<array[i]<<" ";
    }
    out.close();
}