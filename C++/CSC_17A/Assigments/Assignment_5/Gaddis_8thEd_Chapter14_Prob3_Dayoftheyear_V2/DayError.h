/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   DayError.h
 * Author: gabriel
 *
 * Created on November 12, 2018, 5:45 PM
 */

#ifndef DAYERROR_H
#define DAYERROR_H
#include <cstring>
using namespace std;
class error{
    private:
        int days;
        string eror="Your input was not correct";
    public:
        error(){
            days=0;
        }
        void iferror(int day){
            days=day;
            if(days>365||days<1){
                cout<<this->eror<<endl;
                exit(EXIT_FAILURE);
            }
        }
        
};


#endif /* DAYERROR_H */

