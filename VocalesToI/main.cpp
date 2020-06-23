/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on April 19, 2020, 10:13 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


/* 
 * File:   Node.h
 * Author: Guijosa David
 * Created on March 28th, 2018, 9:26 AM
 * Purpose:  Template Link List
 */
int main(int argc, char** argv) {
    char name[15]="Message.txt";
    ofstream out;
    ifstream file;
    file.open(name);
    out.open("out.txt");
    string s;
    string sentence="";
    while(file>>s){
        for(int i=0;i<s.length();i++){
            if(s[i]=='a'||s[i]=='e'||s[i]=='o'||s[i]=='u')s[i]='i';
            else if(s[i]=='A'||s[i]=='E'||s[i]=='O'||s[i]=='U')s[i]='I';
        }
        sentence+=s+" ";
    }
    //cout<<sentence;
    out<<sentence;
    file.close();
    out.close();
    return 0;
}

