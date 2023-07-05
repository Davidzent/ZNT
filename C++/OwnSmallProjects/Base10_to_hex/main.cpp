/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on September 15, 2020, 9:56 AM
 */

#include <cstdlib>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    ifstream in;
    ofstream out;
    out.open("out.txt");
    in.open("in.txt");
    int temp=0;
    int base10;
    int bmodhex;
    int base1=16;
    int base2=8;
    int base3=2;
    string s="";
    string reverse="";
    while(in>>base10){
        //base 10 to base 16
       
        s="";
        temp=base10;
        while(temp>base1-1){
            out<<temp<<"/"<<base1<<" = ";
            bmodhex=temp%base1;
            bmodhex>=10?s+=static_cast<char>('A'+bmodhex-10):s+='0'+bmodhex;
            temp/=base1;
            out<<temp<<" with a remainder of "<<bmodhex<<endl;
        }
        bmodhex=temp%base1;
        out<<temp<<"/"<<base1<<" = 0 with a remainder of "<<bmodhex<<endl;
        bmodhex>=10?s+=static_cast<char>('A'+bmodhex-10):s+='0'+bmodhex;
        reverse="";
        for(int i=s.size()-1;i>=0;i--){
            reverse+=s[i];
        }   
        out<<base10<<" base 10 is:"<<endl<<"\t"<<reverse<<" in base "<<base1<<endl;
        //base 10 to base 8
        temp=base10;
        s="";
        while(temp>base2-1){
            bmodhex=temp%base2;
            s+='0'+bmodhex;
            temp/=base2;
        }
        bmodhex=temp%base2;
        s+='0'+bmodhex;
        reverse="";
        for(int i=s.size()-1;i>=0;i--){
            reverse+=s[i];
        }   
        out<<"\t"<<reverse<<" in base "<<base2<<endl;
        //base 10 to binary
        temp=base10;
        s="";
        while(temp>base3-1){
            bmodhex=temp%base3;
            s+='0'+bmodhex;
            temp/=base3;
        }
        bmodhex=temp%base3;
        s+='0'+bmodhex;
        reverse="";
        for(int i=s.size()-1;i>=0;i--){
            reverse+=s[i];
        }   
        out<<"\t"<<reverse<<" in base "<<base3<<endl<<endl;
                
    }
    
    
    return 0;
}

