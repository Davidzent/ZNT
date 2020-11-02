/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on October 27, 2020, 1:14 PM
 */

#include <cstdlib>
using namespace std;


#include "Array.h"
#include "Stats.h"
/*
 * 
 */

Stats fill(const Array);

int main(int argc, char** argv) {

    return 0;
}
Stats fill(const Array){
    Stats* stats=new Stats;
    stats->mode=new Array;
    stats->mode->data=new float[nModes];
    stats->mode->size=nModes;
    stats->modFreq=0;
    stats->media=0;
    return Stats;
}

