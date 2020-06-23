/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template cin, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on June 18, 2020, 4:49 PM
 */

#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    ofstream cout;
    ifstream cin;
    cin.open("in.txt");
    cout.open("out.txt");
    string s;
    int temp=0;
    while(cin>>s){
        cout<<s<<" ";
        temp=s.find(';');
        if(temp<s.size())cout<<endl<<'\t';
        else{
            temp=s.find('{');
            if(temp<s.size())cout<<endl<<'\t';
        }
    }
    
    cout.close();
    cin.close();
    return 0;
}

