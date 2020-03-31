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

//Program Execution Begins Here
int main(int argc, char** argv) {
    //setRandom Seed
    srand(static_cast<unsigned int>(time(0)));   
    //Declare all Variables Here
    int size=10;
    int coins=5;
    float all=0,inrange=0;
    int trw=100000;
    int *rnd=new int[coins];
    bool **coin=new bool*[coins];
    //Input or initialize values Here
    //set the values of a biased coin
    for(int i=0;i<coins;i++){
        coin[i]=new bool[size];
    }
    for(int i=0;i<coins;i++){
        for(int j=0;j<size;j++){
            if(size*0.3>=j)coin[i][j]=true;
            else coin[i][j]=false;
        }
    }
    //throw coins
    for(int i=0;i<trw;i++){
        inrange=0;
        for(int j=0;j<coins;j++){
            rnd[j]=rand()%size;
        }
        for(int j=0;j<coins;j++){
            if(coin[j][rnd[j]])inrange++;
        }
        if(inrange==coins)all++;
    }
    //Output Located Here
    cout<<fixed;
    cout<<"all of them fall in range = "<<setprecision(0)<<all<<" Times out of "
            <<trw<<" throws with a probability of = "<<setprecision(3)<<all/trw<<endl;
    cout<<endl<<endl;
    
    //with formula
    float chanceX,chanceY;
    chanceX=0.3f;
    chanceY=0.7f;
    //P(X,X,X,X)
    cout<<"The probability of getting all in the range is = "
            <<chanceX*chanceX*chanceX*chanceX<<endl;
    //Exit
    for(int i=0;i<coins;i++){
        delete coin[i];
    }
    delete coin;
    return 0;
}
//9519418408