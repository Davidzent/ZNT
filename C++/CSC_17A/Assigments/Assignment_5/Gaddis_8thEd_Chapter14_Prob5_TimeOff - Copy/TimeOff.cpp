/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TimeOff.cpp
 * Author: gabriel
 *
 * Created on November 12, 2018, 8:39 PM
 */

#include <iomanip>
#include "TimeOff.h"
TimeOff::TimeOff(){
    this->ID=0;
    this->name.clear();
    this->sicktk=0;
    this->upaidtk=0;
    this->vactake=0;
}
ostream &operator<<(ostream &strm,const TimeOff &obj){
    strm<<"Name: "<<obj.name<<endl<<"ID: "<<obj.ID<<endl;
    strm<<"sick days taken"<<obj.sicktk<<endl;
    strm<<"Maximum allowed = "<<obj.sicktk<<endl;
    strm<<"Unpaid Vacations Taken = "<<obj.upaidtk<<endl;
    strm<<"Maximum allowed = "<<obj.mxUpaid<<endl;
    strm<<"Paid vacations days taken = "<<obj.vactake<<endl;
    strm<<"Maximum allowed = "<<obj.mxvact<<endl;
    return strm;
}
istream &operator>>(istream&strm,TimeOff &obj){
    cout<<"Name"<<endl;
    strm>>obj.name;
    cout<<"ID"<<endl;
    strm>>obj.ID;
    cout<<"Sick days taken"<<endl;
    strm>>obj.sicktk;
    cout<<"Unpaid Vacations"<<endl;
    strm>>obj.upaidtk;
    cout<<"Paid Vacations"<<endl;
    strm>>obj.vactake;
    return strm;
}
