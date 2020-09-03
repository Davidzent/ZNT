/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on August 17, 2020, 6:23 PM
 */

#include <iostream>
#include <cstdlib>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    int size=6;
    int range=3;
    int arr[size];
    int **cnvt;
    int p=size;
    for(int i=0;i<size;i++){
        if(i>range) p*=i;
        arr[i]=i+1;
    }
    for(int i=2;i<=range;i++){
        p/=i;
    }
    cnvt=new int*[range];
    for(int i=0;i<range;i++){
        cnvt[i]=new int[p];
    }
    int c=size-range+1;
    int s0=size-c+1;
    int s1=s0-1;
    int s2=s1-1;
    int cnt=s0;
    int cnt12=cnt;
    int cnt1=0;
    int cnt2=0;
    for(int i=0;i<range;i++){
        for(int j=0;j<p;p++){
            switch (i){
                case 0:{
                    cnvt[i][p]=s0++;
                    s0%range==0?s0=(cnt++)+1:s0;
                    break;
                }
                case 1:{
                    cnvt[i][p]=s1;
                    //cnt1%==0?s0=(cnt++)+1:s0;
                    break;
                }
            }
        }
    }
    return 0;
}

