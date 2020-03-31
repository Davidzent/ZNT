/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   personal information.h
 * Author: gabriel
 *
 * Created on November 4, 2018, 8:27 AM
 */
#include <string>
#ifndef PERSONAL_INFORMATION_H
#define PERSONAL_INFORMATION_H
using namespace std;
class data{
    private:
        unsigned int age;
        string name;
        string adress;
        string phone;
    public:
        data();
        data(string,string,string,int);
        void setage(unsigned int);
        void setname(string);
        void setadrs(string);
        void setphon(string);
        string getname();
        string getadrs();
        int getage();
        string getphon();
        void prnt();
};



#endif /* PERSONAL_INFORMATION_H */

