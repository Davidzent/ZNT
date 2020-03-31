/* 
 * File:   main.cpp
 * Author: Guijosa David
 *
 * Created on November 26, 2019, 9:28 AM
 */

#include <cstdlib>
#include <fstream>
#include<iostream>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    ofstream file;
    file.open("Unique.txt");
    int numbers=10;
    int codeSz=4;
    string s;
    unsigned int unique=1;
    for(int i=(numbers-1+codeSz);i>(numbers-1);i--){
        unique*=i;
    }
    for(int i=codeSz;i>0;i--){
        unique/=i;
    }
    file<<unique<<endl;
    for(int i=0;i<numbers;i++){
        for(int j=i;j<numbers;j++){
            for(int x=j;x<numbers;x++){
                for(int k=x;k<numbers;k++){
                s=i+48;
                s+=j+48;
                s+=x+48;
                s+=k+48;
                file<<s<<" ";
                }
            }file<<endl;
        }
    }
    file.close();
    file.open("ALL.txt");
    for(int i=0;i<numbers;i++){
        for(int j=0;j<numbers;j++){
            for(int x=0;x<numbers;x++){
                for(int k=0;k<numbers;k++){
                s=i+48;
                s+=j+48;
                s+=x+48;
                s+=k+48;
                file<<s<<" ";
                }
            }file<<endl;
        }
    }
    file.close();

    return 0;
}

