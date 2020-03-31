/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Circle.h
 * Author: gabriel
 *
 * Created on November 4, 2018, 8:34 PM
 */
#ifndef CIRCLE_H
#define CIRCLE_H
class Circle{
    private:
        float radius;
        const float pi=3.1416;
    public:
        Circle();
        Circle(float);
        void setRad(float);
        float getrad();
        float getarea();
        float getdmtr();
        float getcirc();
    
};


#endif /* CIRCLE_H */

