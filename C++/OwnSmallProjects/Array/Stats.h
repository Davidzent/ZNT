/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Stats.h
 * Author: david
 *
 * Created on October 27, 2020, 1:21 PM
 */

#ifndef STATS_H
#define STATS_H

#include "Array.h"

struct Stats
{
    Array *mode;
    float modFreq;
    float media;
};

#endif /* STATS_H */

