/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on April s18, 2019, 11:00 AM
 * Purpose: 
 */

//System Libraries Here
#include <cmath>
#include <iomanip>
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
void sort(int*,int);
//Program Execution Begins Here
int main(int argc, char** argv) {
    //setRandom Seed
    srand(static_cast<unsigned int>(time(0)));   
    //Declare all Variables Here
    int dices=4;
    float pair=0,triple=0,all=0,similar=0;
    int trw=5000;
    int *dice=new int[dices];
    //Input or initialize values Here
    for(int i=0;i<trw;i++){
        similar=0;
        for(int j=0;j<dices;j++){
            dice[j]=rand()%6+1;
        }
        sort(dice,dices);
        for(int j=0;j<dices-1;j++){
            if(dice[j]==dice[j+1])similar++;
            if(similar==3&&dice[0]==dice[3])similar++;
        }
        if(similar==1)pair++;
        else if(similar==2)triple++;
        else if(similar==3)pair++;
        else if(similar==4)all++;
    }
    //Output Located Here
    cout<<fixed;
    cout<<"Simulated"<<endl;
    cout<<"You get pairs = "<<setprecision(0)<<pair<<" with a probability of = "
            <<setprecision(3)<<pair/trw<<endl;
    cout<<"You get triples = "<<setprecision(0)<<triple<<" with a probability of = "
            <<setprecision(3)<<triple/trw<<endl;
    cout<<"You get all = "<<setprecision(0)<<all<<" with a probability of = "
            <<setprecision(3)<<all/trw<<endl;
    cout<<endl<<endl;
    //formula
    delete dice;
    return 0;
}
//9519418408
