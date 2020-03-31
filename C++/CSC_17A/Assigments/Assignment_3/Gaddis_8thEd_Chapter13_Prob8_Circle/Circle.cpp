/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Circle.cpp
 * Author: gabriel
 *
 * Created on November 4, 2018, 8:39 PM
 */

#include "Circle.h"

using namespace std;

Circle::Circle(){
    radius=0;
}
Circle::Circle(float rad){
    radius=rad;
}
void Circle::setRad(float rad){
    radius=rad;
}
float Circle::getrad(){
    return radius;
}
float Circle::getarea(){
    return pi*radius*radius;
}
float Circle::getdmtr(){
    return radius*2;
}
float Circle::getcirc(){
    return 2*pi*radius;
}
