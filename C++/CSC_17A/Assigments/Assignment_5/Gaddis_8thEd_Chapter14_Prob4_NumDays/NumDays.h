/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   NumDays.h
 * Author: gabriel
 *
 * Created on November 12, 2018, 6:11 PM
 */

#ifndef NUMDAYS_H
#define NUMDAYS_H
class NumDay{
    private:
        unsigned int hour;
        float day;
    public:
        NumDay(unsigned int);
        void calday();
        void operator+(const NumDay &);
        void operator-(const NumDay &);
        void operator++(int);
        void operator--(int);
        void operator=(const NumDay&);
        void prnt();
        
};


#endif /* NUMDAYS_H */

