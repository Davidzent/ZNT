/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Employee.cpp
 * Author: gabriel
 *
 * Created on November 3, 2018, 4:43 PM
 */

#include <iostream>
#include <iomanip>
#include "Employee.h"
using namespace std;

Employ::Employ(string Name,string Pos,string Adress,int id){
    Dprtmnt=Adress;
    name=Name;
    position=Pos;
    ID=id;
}
Employ::Employ(string Name,int id){
    name=Name;
    ID=id;
    position.clear();
    Dprtmnt.clear();
}
Employ::Employ(){
    name.clear();
    ID=0;
    position.clear();
    Dprtmnt.clear();
}
void Employ::prtinfo(){
    cout<<name<<setw(20)<<ID<<setw(20)<<Dprtmnt<<setw(20)<<position<<endl;
}
string Employ::getname(){
    return name;
}
int Employ::getID(){
    return ID;
}
string Employ::getdep(){
    return Dprtmnt;
}
string Employ::getpos(){
    return position;
}
void Employ::setname(string name){
    this->name=name;
}
void Employ::setdep(string dep){
    Dprtmnt=dep;
}
void Employ::setpos(string pos){
    position=pos;
}
void Employ::setID(int ID){
    this->ID=ID;
}
