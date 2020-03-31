/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: rcc
 *
 * Created on October 31, 2019, 11:22 AM
 */

#include <cstdlib>
#include <fstream>
#include <cmath>
using namespace std;

int main(int argc, char** argv) {
    ofstream file;
    file.open("primes.txt");
    int max=1000000;
    bool prime;
    for(int num2Tst=max;num2Tst>=2;num2Tst--){
        prime=true;
        for(int i=2;i<=sqrt(max)&&prime;i++){
            prime=num2Tst==i?true&&prime:prime&&num2Tst%i;
        }
        if(prime){
            file<<num2Tst<<" ";
        }
    }
    file.close();
    return 0;
}

