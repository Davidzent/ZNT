/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   car.cpp
 * Author: gabriel
 *
 * Created on November 4, 2018, 9:38 AM
 */

#include "Car.h"
using namespace std;
car::car(int yr,string mke){
    year=yr;
    make=make;
    speed=0;
}
int car::getyr(){
    return year;
}
int car::getspeed(){
    return speed;
}
string car::getmake(){
    return make;
}
void car::aclrt(){
    speed+=5;
}
void car::brake(){
    if (speed>0){
    speed-=5;
    }
}


