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
    day=0;
    this->nmonth[0]=31;
    for(int x=0,i=1;x<size;i++,x++){
        if(i==3||i==5||i==7||i==8||i==10||i==12){
            nmonth[x]=31+nmonth[x-1];
        }
        else if(i==11||i==4||i==6||i==9){
            nmonth[x]=30+nmonth[x-1];
        }
        else if(i==2)nmonth[x]=nmonth[x-1]+28;
    }
    rday=0;
    numnth=0;
}
void DAY::setdat(int day){
    this->day=day;
    
}
void DAY::prnt(){
    for(int i=0;i<size;i++){
        if(day<=31){rday=day;i=size;}
        else if(nmonth[i-1]<day&&i>0&&day<=nmonth[i]){rday=day-nmonth[i-1];
        i=size;}
        else {numnth++;}
    }
    cout<<"Day "<<day<<" Would be "<<month[numnth]<<" "<<rday<<endl;
}