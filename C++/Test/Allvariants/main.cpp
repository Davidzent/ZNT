/* 
 * File:   main.cpp
 * Author: david Guijosa
 * Purpose: To create all 24 possible combinations from a non-repetition array
 * Created on December 3, 2020, 4:44 PM
 */

#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

/*
 * 
 */
void moveleft(char[],int);
int main(int argc, char** argv) {
    int size=4;
    char str[size]={'0','1','7','9'};
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(i==j)continue;
            for(int k=0;k<size;k++){
                if(i==k||j==k)continue;
                for(int l=0;l<size;l++){
                    if(i==l||j==l||k==l)continue;
                    cout<<str[i]<<str[j]<<str[k]<<str[l]<<endl;
                }
            }
        }
    }
    return 0;
}
