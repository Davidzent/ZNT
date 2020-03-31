/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NumDay.cpp
 * Author: gabriel
 *
 * Created on November 12, 2018, 6:20 PM
 */

#include "NumDays.h"
#include <iostream>
#include <iomanip>
using namespace std;
NumDay::NumDay(unsigned int hour){
    this->hour=hour;
    day=0;
    calday();
}
void NumDay::calday(){
    day=static_cast<float>(hour)/8;
}
void NumDay::operator +(const NumDay &right){
    this->hour+=right.hour;
    calday();
}
void NumDay::operator -(const NumDay &right){
    this->hour-=right.hour;
    calday();
}
void NumDay::operator ++(int){
    this->hour++;
    calday();
}
void NumDay::operator --(int){
    this->hour--;
    calday();
}
void NumDay::prnt(){
    cout<<fixed<<showpoint<<setprecision(2);
    cout<<"Hours = "<<hour<<endl;
    cout<<"Days = "<<day<<endl;
}
void NumDay::operator =(const NumDay&right){
    this->hour=right.hour;
    calday();
}


