/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on February 3, 2021, 2:28 PM
    * The following table shows the approximate speed of sound in air, water, and steel.
    Medium Speed
    Air 1,100 feet per second
    Water 4,900 feet per second
    Steel 16,400 feet per second
    Write a program that displays a menu allowing the user to select air, water, or steel.
    After the user has made a selection, he or she should be asked to enter the distance
    a sound wave will travel in the selected medium. The program will then display the
    amount of time it will take. (Round the answer to four decimal places.)
    Input Validation: Check that the user has selected one of the available choices from the
    menu. Do not accept distances less than 0.
    t=d/v
 */

//System Libraries
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

//User Libraries

//Global Constants - No Global Variables
//Only Universal Constants, Math, Physics, Conversions, Higher Dimensions
const int AirSP=1100;
const int WaterSP=4900;
const int SteelSP=16400;

//Function Prototypes
int main(int argc, char** argv) {
    //Set Random Number seed
    
    //files
    ifstream in;
    ofstream out;
    in.open("in.txt");
    out.open("out.txt");
    
    //Declare Variable Data Types and Constants
    char ch;
    float time;
    float distance;
    
    //Initialize Variables
    out<<"Choose which medium the sound wave will travel in.\n"
        <<"1.Air\n"
        <<"2.Water\n"
        <<"3.Steel\n";
    in>>ch;
    out<<"Enter the distance the wave will travel:\n";
    in>>distance;
    
    //Process or map Inputs to Outputs
    if(distance>0){
        if(ch=='1'){
            time=distance/AirSP;
        }else if(ch=='2'){
            time=distance/WaterSP;
        }else if(ch=='3'){
            time=distance/SteelSP;
        }
        out<<fixed<<showpoint<<setprecision(4);
        out<<"The wave will take "<<time<<" seconds"<<endl;
    }else{
        out<<"The distance can not be less than or equal to 0"<<endl;
    }

    //Exit stage right!
    return 0;
}

