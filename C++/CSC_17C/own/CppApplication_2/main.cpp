/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: rcc
 *
 * Created on October 10, 2019, 8:04 AM
 */
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <fstream>

using namespace std;

const int size=5;

int sumof(int[][size],int,int,bool[]);
int sumof(int[][size],int,bool[]);
int sumkind(int[][size],int,int,bool[]);
int sumstraight(int[][size],int,int,bool[]);
int fullhouse(int[][size],int,bool[]);

int main(int argc, char** argv) {
    char name[10]="input.txt";
    ifstream file;
    file.open(name);
    
    while(file){
        int row=13;
        int data[row][size];
        bool t[row];
        int output=0;
        int sum[15];
        sum[14]=0;
        int sum6=0;
        for(int i=0;i<row;i++){
            t[i]=true;
        }
        for(int i=0;i<13;i++){
            sum[i]=0;
            for(int j=0;j<size;j++){
                file>>data[i][j];
            }
        }
        for(int i=6;i>0;i--){
            sum[i-1]=sumof(data,row,i,t);
            sum6+=sum[i-1];
            sum[14]+=sum[i-1];
        }
        sum[6]=sumof(data,row,t);
        sum[13]=0;
        if(sum6>=63)sum[13]=35;
        sum[14]+=sum[6];
        sum[14]+=sum[13];
        for(int i=size;i>=3;i--){
            sum[4+i]=sumkind(data,row,i,t);
            sum[14]+=sum[4+i];
        }
        for(int i=size-1;i<=size;i++){
            sum[6+i]=sumstraight(data,row,i,t);
            sum[14]+=sum[6+i];
        }
        sum[12]=fullhouse(data,row,t);
        sum[14]+=sum[12];
        for(int i=0;i<15;i++){
            cout<<sum[i]<<" ";
        }
        cout<<endl;
        file.peek();
    }
    file.close();
    return 0;
}
int sumof(int data[][size],int row,int number,bool check[]){
    int sum=0;
    int max=0;
    int pos;
    for(int j=0;j<row;j++){
        sum=0;
        for(int i=0;i<size;i++){
            if(data[j][i]==number)sum+=data[j][i];
        }
        if(check[j]&&sum>max){
            pos=j;
            max=sum;
        }
    }
    check[pos]=false;
    return max;
}
int sumof(int data[],int i){
    if(i>=0)return sumof(data,i-1)+data[i];
    return 0;
}
int sumof(int data[][size],int row,bool check[]){
    int sum=0;
    int max=0;
    int pos;
    for(int j=0;j<row;j++){
        sum=0;
        for(int i=0;i<size;i++){
            sum+=data[j][i];
        }
        if(check[j]&&sum>max){
            pos=j;
            max=sum;
        }
    }
    check[pos]=false;
    return max;
}
int sumkind(int data[][size],int row,int quantity,bool chck[]){
    int cnt;
    bool check[size];
    int max=0;
    int pos;
    for(int j=0;j<row;j++){
        cnt=1;
        for(int i=0;i<size;i++){
            check[i]=true;
        }
        for(int i=0;i<size-1;i++){
            for(int x=i+1;x<size;x++){
                if(data[j][i]==data[j][x]&&check[x])cnt++,check[x]=false;
            }
        }
        if(chck[j]&&cnt>=quantity&&max<sumof(data[j],size))max=sumof(data[j],size),pos=j;
        //cout<<max<<endl;
    }
    chck[pos]=false;
    return max;
}
int sumstraight(int data[][size],int row,int straight,bool check[]){
    int cnt=1;
    int add=10;
    if(straight==size)add=20;
    for(int j=0;j<row;j++){
        for(int i=0;i<size-1;i++){
            if(data[j][i]==data[j][i+1]-1)cnt++;
        }
        if(cnt>=straight){
                check[j]=false;
                if(straight==size)return 35;
                else return 25;
        }
           
    }

    return 0;
}
int fullhouse(int data[][size],int row,bool chck[]){
    int cnt=0;
    int cnt2=1;
    bool check[size];
    for(int x=0;x<row;x++){
        cnt=1;
        cnt2=1;
        for(int i=0;i<size;i++){
            check[i]=true;
        }
        for(int i=0;i<size-1;i++){
            if(data[x][i]==data[x][i+1]&&check[x])cnt++;
            else cnt2++;
        }
        if(cnt==4&&cnt2==2){
            chck[x]=false;
            return 40;
        }
    }
    return 0;
}