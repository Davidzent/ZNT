/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   personal information.cpp
 * Author: gabriel
 *
 * Created on November 4, 2018, 8:36 AM
 */
#include <iomanip>
#include <iostream>
#include "personal information.h"

using namespace std;
data::data(){
    age=0;
    phone.clear();
    name.clear();
    adress.clear();
}
data::data(string nme,string addres,string pone,int age){
    this->age=age;
    phone=pone;
    name=nme;
    adress=addres;
}
string data::getadrs(){
    return adress;
}
int data::getage(){
    return age;
}
string data::getname(){
    return name;
}
string data::getphon(){
    return phone;
}
void data::setname(string name){
    this->name=name;
}
void data::setage(unsigned int age){
    this->age=age;
}
void data::setadrs(string adrs){
    adress=adrs;
}
void data::setphon(string phn){
    phone=phn;
}
void data::prnt(){
    cout<<"Name"<<setw(20)<<"Age"<<setw(20)<<"Address"
            <<setw(20)<<"Phone number"<<endl;
    cout<<name<<setw(20)<<age<<setw(20)<<adress
            <<setw(20)<<phone<<endl;
}