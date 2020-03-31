/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: rcc
 *
 * Created on October 29, 2019, 10:12 AM
 */

#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

int main(int argc, char** argv) {
    //set random seed
    srand(static_cast<unsigned int>(time(0)));
    //variables
    char name[20]="inputs.txt";
    ofstream file;
    char max='z';
    char min='a';
    bool upercase=true;
    int inputs=10;
    int wordsz;
    int maxwordsz=20;
    file.open(name);
    //calculations
    char *word=new char[maxwordsz];
    int type=1;
    for(int i=0;i<inputs;i++){
        wordsz=rand()%(maxwordsz-1)+1;
        for(int j=0;j<wordsz;j++){
            if(upercase)type=rand()%2;
            if(type==0)word[j]=rand()%(max-min)+min;
            else word[j]=rand()%(max-min)+(min-32);
        }
        file<<word<<endl;
        for(int j=0;j<maxwordsz;j++){
            word[j]='\0';
        }
    }
    file.close();
    delete word;
    return 0;
}

