/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <iostream>
#include <cstdlib>
#include "Date.h"
using namespace std;

Date::Date(int Day,int Month,int Year){
    if(Month<=12&&Month>=1)month=Month;
    else exit(EXIT_FAILURE);
    if(Day<=31&&Day>=1)day=Day;
    else exit(EXIT_FAILURE);
    year=Year;
}
void Date::nDate(){
    cout<<endl;
    if(month==1) name="January";
    else if(month==2)name="February";
    else if(month==3)name="March";
    else if(month==4)name="April";
    else if(month==5)name="May";
    else if(month==6)name="June";
    else if(month==7)name="July";
    else if(month==8)name="August";
    else if(month==9)name="September";
    else if(month==10)name="October";
    else if(month==11)name="November";
    else if(month==12)name="December";
}
void Date::prtDate(){
    cout<<day<<'/'<<month<<'/'<<year<<endl;
    cout<<name<<" "<<day<<", "<<year<<endl;
    cout<<day<<" "<<name<<" "<<year<<endl;
}