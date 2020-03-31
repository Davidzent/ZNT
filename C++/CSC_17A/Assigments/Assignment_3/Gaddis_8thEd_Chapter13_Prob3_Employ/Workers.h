/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Workers.h
 * Author: gabriel
 *
 * Created on November 3, 2018, 5:16 PM
 */

#ifndef WORKERS_H
#define WORKERS_H
#include "Employee.h"
class worker{
    private:
        Employ *work;
        int size;
    public:
        worker(const int);
        void setInfo(Employ,int);
        void prntinfo();
        ~worker();
};


#endif /* WORKERS_H */

