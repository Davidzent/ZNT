/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   day.cpp
 * Author: rcc
 *
 * Created on November 8, 2018, 1:00 PM
 */

#include <iostream>
#include "Days.h"

DAY::DAY(){
    date=0;
    name.clear();
}
DAY::DAY(int day){
    this->date=day;
    name.clear();
}
DAY::DAY(string name){
    date=0;
    this->name=name;
}
void DAY::setdat(int date){
    this->date=date;
    
}
void DAY::setname(string name){
    this->name=name;
}
int DAY::getdat(){
    return date;
}
string DAY::getname(){
    return name;
}
void DAY::operator ++(int){
    date++;
    name=month[date-1];
}
void DAY::operator --(int){
    date--;
    name=month[date-1];
}
void DAY::prnt(){
    cout<<"Month = "<<name<<'\n';
    cout<<"Number of month = "<<date<<'\n';
}