/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on Nov 08, 2018, 11:00 AM
 * Purpose:  
 */
#include <iostream>
#include "Number.h"
using namespace std;
number::number(int number){
    this->numbe=number;
    name.clear();
}
void number::prnt(){
    int num=numbe;
    int res=numbe;
    if(res>=1000){
        num/=1000;
        switch (num){
            case 1:name+=lsthn20[1];break;
            case 2:name+=lsthn20[2];break;
            case 3:name+=lsthn20[3];break;
            case 4:name+=lsthn20[4];break;
            case 5:name+=lsthn20[5];break;
            case 6:name+=lsthn20[6];break;
            case 7:name+=lsthn20[7];break;
            case 8:name+=lsthn20[8];break;
            case 9:name+=lsthn20[9];break;
        }
        name+=thusand;
        num*=1000;
        res-=num;
        num=res;
    }
    if(res>=100){
        num/=100;
        switch (num){
            case 1:name+=lsthn20[1];break;
            case 2:name+=lsthn20[2];break;
            case 3:name+=lsthn20[3];break;
            case 4:name+=lsthn20[4];break;
            case 5:name+=lsthn20[5];break;
            case 6:name+=lsthn20[6];break;
            case 7:name+=lsthn20[7];break;
            case 8:name+=lsthn20[8];break;
            case 9:name+=lsthn20[9];break;
        }
        name+=hundred;
        num*=100;
        res-=num;
        num=res;
    }
    if(res>20){
        num/=10;
        cout<<num<<endl;
        cout<<tens[7]<<endl;
        switch (num){
            case 2:name+=tens[0];break;
            case 3:name+=tens[1];break;
            case 4:name+=tens[2];break;
            case 5:name+=tens[3];break;
            case 6:name+=tens[4];break;
            case 7:name+=tens[5];break;
            case 8:name+=tens[6];break;
            case 9:name+=tens[7];break;
        }
        num*=10;
        res-=num;
        num=res;
        if(res>0){
            switch (res){
            case 1:name+=lsthn20[1];break;
            case 2:name+=lsthn20[2];break;
            case 3:name+=lsthn20[3];break;
            case 4:name+=lsthn20[4];break;
            case 5:name+=lsthn20[5];break;
            case 6:name+=lsthn20[6];break;
            case 7:name+=lsthn20[7];break;
            case 8:name+=lsthn20[8];break;
            case 9:name+=lsthn20[9];break;
            }
        }
    }
    else if(num<20&&num>=0){
        switch (num){
            case 1:name+=lsthn20[1];break;
            case 2:name+=lsthn20[2];break;
            case 3:name+=lsthn20[3];break;
            case 4:name+=lsthn20[4];break;
            case 5:name+=lsthn20[5];break;
            case 6:name+=lsthn20[6];break;
            case 7:name+=lsthn20[7];break;
            case 8:name+=lsthn20[8];break;
            case 9:name+=lsthn20[9];break;
            case 10:name+=lsthn20[10];break;
            case 11:name+=lsthn20[11];break;
            case 12:name+=lsthn20[12];break;
            case 13:name+=lsthn20[13];break;
            case 14:name+=lsthn20[14];break;
            case 15:name+=lsthn20[15];break;
            case 16:name+=lsthn20[16];break;
            case 17:name+=lsthn20[17];break;
            case 18:name+=lsthn20[18];break;
            case 19:name+=lsthn20[19];break;   
        }
        
    }
    cout<<name<<endl;
}