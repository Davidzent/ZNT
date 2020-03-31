/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Date.h
 * Author: David Guijosa
 *
 * Created on November 3, 2018, 2:52 PM
 */

#ifndef DATE_H
#define DATE_H

#include <iostream>
using namespace std;
class Date{
private:
    int month;
    int year;
    int day;
    string name;
public:
    Date(){};
    Date(int,int,int);
    void nDate();
    void operator++(int);
    void operator--(int);
    //friends
    friend istream &operator>>(istream &,Date &);
    friend ostream &operator<<(ostream &,const Date &);
};


#endif /* DATE_H */

