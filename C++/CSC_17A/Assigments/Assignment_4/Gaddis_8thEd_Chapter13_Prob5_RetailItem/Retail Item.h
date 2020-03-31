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

#ifndef RETAIL_ITEM_H
#define RETAIL_ITEM_H
#include <cstring>
using namespace std;
class RtItem{
    private:
        string dscrp;
        int nHand;
        float price;
    public: 
    RtItem();
    RtItem(string,int,float);
    void setdesc(string);
    void setquan(int);
    void setprc(float);
    int gethand();
    float gerprc();
    string getname();
    void prnt(int);
};



#endif /* RETAIL_ITEM_H */

