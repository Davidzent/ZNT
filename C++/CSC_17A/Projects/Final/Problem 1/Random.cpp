/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on December 10, 2018, 11:00 AM
 * Purpose:  Hello World Template
 */

#include <iostream>
#include <cstdalign>
#include <ctime>
#include "Random.h"
using namespace std;
Prob1Random::Prob1Random(const char size,const char *vals){
    srand(static_cast<unsigned int>(time(0)));
    this->nset=size;
    this->set=new char[nset];
    this->freq=new int[nset];
    for(int i=0;i<nset;i++){
        set[i]=vals[i];
        freq[i]=0;
    }
    this->numRand=0;
}
Prob1Random::~Prob1Random(){
    delete []set;
    delete []freq;
}
char Prob1Random::randFromSet(){
    int x=rand()%nset;
    for(int i=0;i<nset;i++){
        if(set[i]==set[x])freq[i]++;
    }
    numRand++;
    return set[x];
}
int *Prob1Random::getFreq() const{
    return freq;
}
char *Prob1Random::getSet()const{
    return set;
}  
int Prob1Random::getNumRand(void) const{
    return numRand;
}