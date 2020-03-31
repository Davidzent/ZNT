/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on sep 18, 2018, 9:23 AM
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
void prntary(char[],int);
void fillary(char[],char[],int);
void add(char[],char[],int,char[]);
int cunt(char[],int);
//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    int size=53, count;
    char arr[size],arr2[size],sum[size];
    
    //Input or initialize values Here
    fillary(arr,arr2,size);
    
    //Process/Calculations Here
    cout<<" ";
    prntary(arr,size);
    cout<<" ";
    prntary(arr2,size);
    count=cunt(arr2,size);
    //Output Located Here
    add(arr,arr2,count,sum);
    prntary(sum,size);
    //Exit
    return 0;
}
int cunt(char a[],int n){
    int count;
    for(int i=0;i<n;i++){    
        if(a[i]=='/')i=n;
        else if(a[i]=='1'||a[i]=='0')count++;
    }
    return count;
}
void add(char arr[],char arr2[],int count,char arrsum[]){
    char more='0';
    for(int i=count-1;i>=0;i--){
        if(more=='0'&&arr[i]=='0'&&arr2[i]=='0')arrsum[i+1]='0';
        else if(more=='0'&&arr[i]=='1'&&arr2[i]=='0'||more=='0'&&
                arr[i]=='0'&&arr2[i]=='1')arrsum[i]='1';
        else if(more=='0'&&arr[i]=='1'&&arr2[i]=='1'){
            arrsum[i+1]='0';
            more='1';}
        else if(more=='1'&&arr[i]=='0'&&arr2[i]=='0'){
            arrsum[i+1]='1';
            more='0';}
        else if(more=='1'&&arr[i]=='1'&&arr2[i]=='0'||more=='1'&&
                arr[i]=='0'&&arr2[i]=='1'){
            arrsum[i+1]='0';
            more='1';}
        else if(more=='1'&&arr[i]=='1'&&arr2[i]=='1'){
            arrsum[i+1]='1';
            more='1';}
    }
    if(more=='1')arrsum[0]='1';
    else if(more=='0')arrsum[0]='0';
}
void fillary(char arr[],char arr2[],const int size){
    cout<<"Enter values from left to right To stop the values enter /"<<endl;
    int count=0;
    for(int j=0;j<2;j++){
        string stond;
                j==0?stond="first":stond="second";
        for(int i=0;i<size;i++){           
            do{
                cout<<"Input the "<<stond<<" binary value number "<<i+1
                        <<" with a maximum of 53 bites"<<endl;
                if (j==0)cin>>arr[i];
                else if(j==1)cin>>arr2[i];
                if(j==0&&arr[i]<'0'||j==0&&arr[i]>'1'||j==1&&arr2[i]<'0'||
                        j==1&&arr2[i]>'1'){
                    cout<<"Enter only values 0 or 1"<<endl;}
                else if(j==0&&arr[i]>'0'||j==0&&arr[i]<'1')count++;
                else if(j==1&&arr2[i]>'0'||j==1&&arr2[i]<'1')count--;
            }while(j==0&&arr[i]<'/'||j==0&&arr[i]>'1'||j==1&&arr2[i]<'/'||
                    j==1&&arr2[i]>'1');
            if(arr[i]=='/'||arr2[i]=='/')i=size;
            if(j==1&&count==0){arr2[i+1]='/';i=size;}
        }
    }
}
void prntary(char a[],const int n){
    for(int i=0;i<n;i++){    
        if(a[i]=='/')i=n;
        else if(a[i]=='1'||a[i]=='0')cout<<a[i];
    }cout<<endl;
}
