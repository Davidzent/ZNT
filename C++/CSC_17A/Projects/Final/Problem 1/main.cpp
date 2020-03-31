/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on March 22, 2018, 11:00 AM
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
using namespace std;

//User Libraries Here
#include "Random.h"
//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    	char n=5;
	char rndseq[]={18,33,56,79,125};
	int ntimes=100000;
	Prob1Random a(n,rndseq);
	for(int i=1;i<=ntimes;i++)
	{
		a.randFromSet();
	}
	int *x=a.getFreq();
	char *y=a.getSet();
	for(int i=0;i<n;i++)
	{
		cout<<int(y[i])<<" occured "<<x[i]<<" times"<<endl;
	}
	cout<<"The total number of random numbers is "<<a.getNumRand()<<endl;
    return 0;
}

