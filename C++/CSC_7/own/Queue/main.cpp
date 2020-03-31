/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: rcc
 *
 * Created on October 31, 2019, 9:36 AM
 */

#include <cstdlib>
#include <iostream>

using namespace std;
int solve(int,int,int);
int main(int argc, char** argv) {
    int persons=10;
    int front=4;
    int back=4;
    solve(persons,front,back);
    return 0;
}
int solve(int size,int front,int back){
    int queu[size];
    for(int i=0;i<size;i++){
        if(i<size-2)queu[i]=i+1;
        else{
            queu[i]=0;
            for(int j=0;j<size-2;j++){
                queu[i]+=queu[j];
            }
            if(queu[i]==queu[i-1])queu[i]--;
        }
        cout<<queu[i]<<" ";
    }
    cout<<endl;
    int seenpos[size];
    int ntseenps[size];
    for(int i=0;i<size;i++){
        seenpos[i]=2;
        ntseenps[i]=0;
        for(int j=1;j<size-1;j++){
            if(queu[i]>queu[j])seenpos[i]++;
        }
        ntseenps[i]=size-seenpos[i];
        cout<<"not seen for "<<i+1<<" "<<ntseenps[i]<<endl;
        cout<<"seen for "<<i+1<<" "<<seenpos[i]<<endl;
    }
    
}
