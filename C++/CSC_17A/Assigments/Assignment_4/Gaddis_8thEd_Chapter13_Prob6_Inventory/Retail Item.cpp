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
#include "Inventory.h"

using namespace std;
invent::invent(){
    ID=0;
    cost=0;
    quantty=0;
    totcost=0;
}
invent::invent(int name,int quant,float cost){
    this->ID=name;
    this->cost=cost;
    this->quantty=quant;
}
void invent::setquan(int quant){
    if(quant>=0)this->quantty=quant;
    else exit(EXIT_FAILURE);
}
void invent::setcost(float price){
    if(price>=0)this->cost=price;
    else exit(EXIT_FAILURE);
}
void invent::setID(int name){
    if(name>=0)this->ID=name;
    else exit(EXIT_FAILURE);
}
int invent::getID(){
    return ID;
}
int invent::getquan(){
    return quantty;
}
float invent::getcost(){
    return cost;
}
float invent::getotcs(){
    return totcost=cost*quantty;
}
