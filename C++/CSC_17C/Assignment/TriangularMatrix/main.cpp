/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on February 13th, 2019, 1:30 M
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
int **fillAry(int);
void prntAry(int **,int);
void destroy(int **,int);

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare all Variables Here
    int row=10;
    
    //Input or initialize values Here
    int **array=fillAry(row);
    
    //Output Located Here
    prntAry(array,row);
    
    //Return Memory
    destroy(array,row);

    //Exit
    return 0;
}

void destroy(int **a,int n){
    for(int row=0;row<n;row++){
        delete []a[row];
    }
    delete []a;
}

void prntAry(int **array,int n){
    cout<<endl;
    for(int row=0;row<n;row++){
        for(int col=0;col<row;col++){
            cout<<array[row][col]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}

int **fillAry(int n){
    //Create the 2-D allocated pointer
    int **array=new int*[n];
    for(int row=0;row<n;row++){
        array[row]=new int[row+1];
    }
    //Fill the array with values
    for(int row=0;row<n;row++){
        for(int col=0;col<row;col++){
            array[row][col]=rand()%90+10;
        }
    }
    //return the Array pointer
    return array;
}