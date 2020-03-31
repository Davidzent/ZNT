/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Car.h
 * Author: gabriel
 *
 * Created on November 4, 2018, 9:33 AM
 */
#include <string>
#ifndef CAR_H
#define CAR_H
using namespace std;
class car{
    private:
        int speed;
        string make;
        int year;
    public:
        car(int,string);
        int getyr();
        string getmake();
        int getspeed();
        void aclrt();
        void brake();
};


#endif /* CAR_H */

