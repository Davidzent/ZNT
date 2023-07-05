/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Formula.h
 * Author: david
 *
 * Created on September 24, 2020, 1:59 PM
 */

#ifndef FORMULA_H
#define FORMULA_H

#include "Variables.h"

#include <string>
using namespace std;

struct Formula{
    Variables Equal;
    Variables Values;
};

#endif /* FORMULA_H */

