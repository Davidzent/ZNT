
/* 
 * File:   main.cpp
 * Author: Jason Handen
 * Created on June 3, 2021, 4:53 PM
 * Purpose: 
 */

#include "Problem 2 Sort.h"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    cout<<"The start of Problem 2, the sorting problem"<<endl;
    Prob2Sort<char> rc;
    bool ascending=true;
    ifstream infile;
    infile.open("Problem2.txt",ios::in);
    char *ch2=new char[10*16];
    char *ch2p=ch2;
    char *ch3p="Lbekoeddhoffbmh\n"
                "Lkcmggjcdhhglif\n"
                "Cgldjhcekjigcdo\n"
                "Cgldjhcekjigcdd\n"
                "Bffmdbkcenlafjk\n"
                "Fggdijijegfblln\n"
                "Jjlncnimjldfedj\n"
                "Amliglfohajcdmn\n"
                "Balgfcaelhfkgea\n"
                "Kmlhmhcddfoeilc\n";
    short count=0;



    while(infile.get(*ch2)){cout<<*ch2;ch2++;count++;}
    infile.close();
    cout<<endl;

    cout<<"Count was: "<<count<<endl;



    cout<<"Sorting on which column"<<endl;
    int column;
    cin>>column;
    char *zc=rc.sortArray(ch3p,10,16+1,column,ascending);//16+1 because of the '\n'



    for(short i=0;i<168;i++){
        cout<<zc[i];
    }




    /*
    for(int i=0;i<10;i++)
    {
        for(int j=0;j<16;j++)
        {
            cout<<zc[i*16+j];
        }
    }
    */
    delete []zc;
    cout<<endl;
    
    return 0;
}