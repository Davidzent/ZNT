/* 
 * File:   main.cpp
 * Author: Guijosa David
 *
 * Created on October 30, 2019, 4:07 PM
 */

#include <cstdlib>
#include <iostream>
using namespace std;
bool divisible(long int,long int);

int main(int argc, char** argv) {
    long int lol=27;
    long int lol2=6;
    bool divide=divisible(lol,lol2);
    cout<<lol<<(divide?" divides ":" does not divide ");
    cout<<lol2<<"!\n";
    return 0;
}
bool divisible(long int divide,long int number){
    if(divide==1||divide<number)return true;
    for(long int i=2;i<divide;i++){
            if((divide%i)==0){          
                int temp=divide/i;
                if(temp==i&&divisible(i,number))return true;
                else if(i>number||temp>number)if(divisible(i,number)&&divisible(temp,number))return true;
                else if(i==number||temp==number)return false;
                else return true;
        }
    }
    return false;
}