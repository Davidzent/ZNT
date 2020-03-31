/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Employee.h
 * Author: David Guijosa
 *
 * Created on November 3, 2018, 4:27 PM
 */
#include <string>
#ifndef EMPLOYEE_H
#define EMPLOYEE_H
using namespace std;
class Employ{
    private:
        string name;
        int ID;
        string Dprtmnt; //department
        string position;
    public:
        Employ();
        Employ(string,int);
        Employ(string,string,string,int);
        void prtinfo();
        string getname();
        int getID();
        string getdep();
        string getpos();
        void setname(string);
        void setdep(string);
        void setpos(string);
        void setID(int);
        
};

#endif /* EMPLOYEE_H */

