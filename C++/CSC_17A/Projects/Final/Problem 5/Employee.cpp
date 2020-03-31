/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Employee.cpp
 * Author: gabriel
 *
 * Created on December 12, 2018, 12:48 PM
 */

#include "Employee.h"
#include <iostream>
using namespace std;
Employee::Employee(char name[],char job[],float payrate){
    for(int i=0;i<20;i++){
        this->MyName[i]=name[i];
        this->JobTitle[i]=job[i];
    }
    setHourlyRate(payrate);
    this->GrossPay=0;
    this->HoursWorked=0;
    this->NetPay=0;
}
float  Employee::CalculatePay(float hrsrate,int hrswrk){
    return getNetPay(getGrossPay(setHourlyRate(hrsrate)
		,setHoursWorked(hrswrk)));
}
float  Employee::getGrossPay(float hrsrate,int hrswrk){
    this->HourlyRate=hrsrate;
    if(hrswrk<=40)this->GrossPay+=this->HourlyRate*hrswrk;
    else if(hrswrk>40&&hrswrk<=50)
        GrossPay+=(HourlyRate*40)+(HourlyRate*(hrswrk-40));
    else if(hrswrk>50)GrossPay+=(HourlyRate*40)+(HourlyRate*(hrswrk-40))
            +(HourlyRate*(hrswrk-50));
}
float  Employee::getNetPay(float){
    NetPay=GrossPay-(GrossPay*Tax());
    return NetPay;
}
void   Employee::toString(){
    cout<<"Name = "<<this->MyName<<" Job Title = "<<this->JobTitle<<endl;
    cout<<" Hourly Rate = "<<this->HourlyRate<<" Hours Worked = "<<this->HoursWorked
            <<" Gross Pay = "<<this->GrossPay<<" Net Pay = "<<this->NetPay<<endl;
}
int    Employee::setHoursWorked(int hrs){
    this->HoursWorked=0;
    if(hrs>0&&hrs<84)this->HoursWorked=hrs;
    return this->HoursWorked;
}
float  Employee::setHourlyRate(float hrsrate){
    this->HourlyRate=0;
    if(hrsrate>0&&hrsrate<200)this->HourlyRate=hrsrate;
    return this->HourlyRate;
}
float  Employee::Tax(){
    if(this->GrossPay<500)return 0.1;
    else if(this->GrossPay<1000)return 0.2;
    else return 0.3;
    
}
