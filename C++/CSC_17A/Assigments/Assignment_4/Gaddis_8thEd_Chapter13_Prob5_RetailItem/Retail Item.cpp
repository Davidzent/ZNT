/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Retail Item.cpp
 * Author: David Guijosa
 *
 * Created on November 8, 2018, 10:27 AM
 */
#include <iomanip>
#include <iostream>
#include "Retail Item.h"

using namespace std;
RtItem::RtItem(){
    dscrp.clear();
    price=0;
    nHand=0;
}
RtItem::RtItem(string name,int quant,float price){
    this->price=price;
    this->dscrp=name;
    this->nHand=quant;
}
void RtItem::setquan(int quant){
    this->nHand=quant;
}
void RtItem::setprc(float price){
    this->price=price;
}
void RtItem::setdesc(string name){
    this->dscrp=name;
}
void RtItem::prnt(int i){
    cout<<"Item #"<<setw(20)<<"Description"<<setw(20)<<"Units On Hand"
            <<setw(20)<<"Price"<<endl;
    cout<<"Item "<<i<<setw(20)<<dscrp<<setw(20)<<nHand<<setw(20)<<price<<endl;
}
string RtItem::getname(){
    return dscrp;
}
int RtItem::gethand(){
    return nHand;
}
float RtItem::gerprc(){
    return price;
}
