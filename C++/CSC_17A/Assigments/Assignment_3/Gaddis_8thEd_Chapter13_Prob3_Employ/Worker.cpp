/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Worker.cpp
 * Author: gabriel
 *
 * Created on November 3, 2018, 5:20 PM
 */

#include <iomanip>
#include <iostream>
#include "Workers.h"
using namespace std;

worker::worker(const int size){
    work=new Employ[size];
    this->size=size;
}
void worker::setInfo(Employ info, int number){
    work[number].setID(info.getID());
    work[number].setname(info.getname());
    work[number].setpos(info.getpos());
    work[number].setdep(info.getdep());
}
void worker::prntinfo(){
    cout<<"Name"<<setw(20)<<"ID Number"<<setw(20)<<"Department"
            <<setw(20)<<"Position"<<endl;
    for(int i=0;i<size;i++){
        work[i].prtinfo();
    }
}
worker::~worker(){
    delete []work;
}

