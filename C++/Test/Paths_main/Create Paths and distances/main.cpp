/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on February 22, 2021, 2:35 PM
 */

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    //Random seed
    srand(static_cast<unsigned int>(time(0)));
    //variables
    int size = 3;
    int x=0;
    ofstream paths;
    ofstream distance;
    
    //open files
    paths.open("../Paths.txt");
    distance.open("../Distance.txt");
    
    //creates paths
    paths<<size<<endl;
    for(int i=1;i<=size;i++){
        paths<<i<<'>';
        for(int j=1;j<size;j++){
            if(!((j+i+x)%(size+1))||i==(x+j+i)%(size+1))x++;
            if(j<size-1)paths<<((x+j+i)%(size+1))<<'>';
            else paths<<((x+j+i)%(size+1))<<endl;
        }
        x=0;
        cout<<endl;
    }
    
    //create random distances
    for(int i=1;i<=size;i++){
        for(int j=1;j<size;j++){
            distance<<(rand()%89+10)<<" ";
        }
        distance<<endl;
    }
    
    //exit
    paths.close();
    distance.close();
    return 0;
}

