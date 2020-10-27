/* 
 * File:   main.cpp
 * Author: david
 */

//System libraries
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

//User functions
void fillarr(int**,int,int,int,int,int);
void print(int**,int,int);

//main
int main(int argc, char** argv) {
    ofstream f;
    //initialize and declare variables
    int row=10,
        col=10;
    int **arr;
    
    //user input
    cout<<"Enter number of rows and cols"<<endl;
    cin>>row>>col;
    
    //create 2D array
    arr=new int*[row];
    for(int i=0;i<row;i++){
        arr[i]=new int[col];
    }
    
    //fill 2D array
    fillarr(arr,row,col,0,0,0);
    
    //print 2D array
    print(arr,row,col);
    
    //Delete memory
    for(int i=0;i<row;i++){
        delete arr[i];
    }
    delete []arr;
    
    //exit
    return 0;
}

void fillarr(int** arr,int row,int col,int x,int y,int strt){
    float min=(row>col?col/2.0f:row/2.0f);              //find the minimum half
    for(int n=0;n<min;n++,y++,x++){
        int yx=(2*(col-x*2)+(row-2*(y+1)))+strt;        //used to calculate the bottom left part
        for(int i=x;i<col-x;i++){
            arr[y][i]=i+1+(!x?0:arr[y][x-1]-x);         //top part of the array
            /* EX:
             1 2 3 4 5
             0 0 0 0 0
             0 0 0 0 0
             0 0 0 0 0
             */
            if(arr[row-y-1][i]==0)arr[row-y-1][i]=yx--; //bottom part of array 
            /* EX:
              1  2  3  4  5
              0  0  0  0  0
              0  0  0  0  0
             12 11 10  9  8
             */
        }
        for(int i=y+1;i<row-(y+1);i++){
            if(arr[i][col-x-1]==0)arr[i][col-x-1]=arr[i-1][col-x-1]+1;  //right part of array
            /* EX:
              1  2  3  4  5
              0  0  0  0  6
              0  0  0  0  7
             12 11 10  9  8
             */
            if(arr[row-i-1][x]==0)arr[row-i-1][x]=arr[row-i][x]+1;      //left part of array
            /* EX:
              1  2  3  4  5
             14  0  0  0  6
             13  0  0  0  7
             12 11 10  9  8
             */
        }
        strt+=2*(row-(2*y)-2)+2*(col-(2*x));            //calculate the new start
    }
}
void print(int** arr,int row,int col){
    cout<<fixed<<endl;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cout<<setw(4)<<arr[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}