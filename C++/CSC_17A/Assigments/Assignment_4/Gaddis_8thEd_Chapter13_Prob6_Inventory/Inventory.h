/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Retail Item.h
 * Author: rcc
 *
 * Created on November 8, 2018, 10:30 AM
 */

#ifndef INVENTORY_H
#define INVENTORY_H
#include <cstring>
using namespace std;
class invent{
    private:
        int ID;
        int quantty;
        float cost;
        float totcost;
    public: 
    invent();
    invent(int,int,float);
    void setID(int);
    void setquan(int);
    void setcost(float);
    int getquan();
    float getcost();
    int getID();
    float getotcs();
};



#endif /* RETAIL_ITEM_H */

