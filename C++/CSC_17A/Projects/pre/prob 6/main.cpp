/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on 06/7/2018
 * Purpose:  Sum Rows, Sum Columns, Grand Sum of an integer array
 */

//System Libraries Here
#include <iostream>//cin,cout
#include <iomanip> //setw(10)
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Allowed like PI, e, Gravity, conversions, array dimensions necessary
const int COLMAX=80;  //Max Columns much larger than needed.

//Function Prototypes Here
void read(int [][COLMAX],int &,int &);//Prompt for size then table
void sum(const int [][COLMAX],int,int,int[][COLMAX]);//Sum rows,col,grand total
void print(const int [][COLMAX],int,int,int);//Either table can be printed

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int ROW=80;           //Max Rows much larger than needed
    int array[ROW][COLMAX]={};  //Declare original array
    int augAry[ROW][COLMAX]={}; //Actual augmented table row+1, col+1
    int row,col;                
    cout<<"Input a table and output the Augment row,col and total sums."<<endl;
    //Input the original table
    read(array,row,col);
    
    //Augment the original table by the sums
    sum(array,row,col,augAry);
    
    //Output the original array
    cout<<endl<<"The Original Array"<<endl;
    print(array,row,col,10);//setw(10)
    
    //Output the augmented array
    cout<<endl<<"The Augmented Array"<<endl;
    print(augAry,row+1,col+1,10);//setw(10)
    
    //Exit
    return 0;
}
void read(int arr[][COLMAX],int &row,int &col){
    cout<<"First input the number of rows and cols. <20 for each"<<endl;
    cin>>row>>col;
    cout<<"Now input the table."<<endl;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cin>>arr[i][j];
        }
    }
}
void sum(const int arr[][COLMAX],int row,int col,int arrS[][COLMAX]){
    int sumRow,sumCol;
    int grndSum=0,grndSm2=0;
    for(int i=0;i<row;i++){
        sumCol=0;
        for(int j=0;j<col;j++){
            arrS[i][j]=arr[i][j];
            sumCol+=arrS[i][j];
        }
        arrS[i][col]=sumCol;
        grndSm2+=sumCol;
    }
    for(int i=0;i<col;i++){
        sumRow=0;
        for(int j=0;j<row;j++){
            sumRow+=arrS[j][i];
        }
        arrS[row][i]=sumRow;
        grndSum+=sumRow;
    }
    grndSm2>grndSum?arrS[row][col]=grndSm2:arrS[row][col]=grndSum;
}
void print(const int arr[][COLMAX],int row,int col,int a){
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            cout<<setw(a)<<arr[i][j];
        }
        cout<<endl;
    }
}
