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

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main() {
     //Declare variables and arrays
     const int MAX=300; 
     const int ROW=200;
     int a[MAX]={};//1-D Array
     int rc[ROW]={};//1-D Array where each row will start in the 1-D array above
     int n,q,cnt,k;
     //Read in the data
     cin>>n>>q;//#Rows and #Queries
     //Read in the entire array
     cnt=0;//Start the array count at 0
     //start
     for(int i=0;i<n;i++){
         cin>>rc[i]; 
         if(i>0)rc[i]+=rc[i-1];
         for(int j=0;j<rc[i]-cnt;j++){
            if(i>0)cin>>a[j+rc[i-1]];
            else cin>>a[j];
         }
         cnt=rc[i];
         
     }
    //output
    for(int i=0;i<q;i++){
        cin>>cnt>>k;
        if(cnt==0)cout<<a[k]<<endl;  
        else if(cnt>0){
            cout<<a[rc[cnt-1]+k]<<endl;      
        }  
    }
    return 0;
}

