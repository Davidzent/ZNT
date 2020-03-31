/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: rcc
 *
 * Created on October 30, 2019, 5:19 PM
 */

#include <cmath>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int *solve(int,int,vector <int>);//10000000

int main(int argc, char** argv) {
    int size=4;
    int number=8;
    vector<int> vec;
    char name[20]="input.txt";
    ifstream file,file2;
    file.open(name);
    while(file>>number){
        int *ans;
        ans=solve(number,size,vec);
        if(ans[0]==0)cout<<"impossible";
        else for(int i=0;i<size;i++)cout<<ans[i]<<" ";
        cout<<" = "<<number<<endl;
        delete ans;
    }
        file.close();
    return 0;
}
int *solve(int number,int size,vector<int> vec){
    int *sum;
    sum=new int[size];
    if(number<8){
        for(int i=0;i<size;i++)sum[i]=0;
        return sum;
    }
    int j=3;
    int left=number;
    int temp;
    bool prime;
    while(left>0){
        for(int num2Tst=number;num2Tst>=2;num2Tst--){
            prime=true;
            for(int i=2;i<=sqrt(number)&&prime;i++){
                prime=num2Tst==i?true&&prime:prime&&num2Tst%i;
            }
            if(prime&&){
                vec.push_back(num2Tst);
                for(int i=0;i<vec.size()&&vec.size()>=4;i++){
                    cout<<vec.size()<<endl;
                    while(vec[i]<left&&(left-vec[i])>=vec[vec.size()-1]*j&&left>0){
                        if((vec[vec.size()-1]*j)==(left-vec[i])){
                            sum[j]=vec[i];
                            j--;
                            for(int i=j;i>=0;i--)sum[i]=vec[vec.size()-1];
                            return sum;
                        }
                        else{
                            if(j==3)temp=i;
                            sum[j]=vec[i];
                            left-=vec[i];
                            if(j==0){
                                int sums=0;
                                for(int k=0;k<size;k++){
                                    sums+=sum[k];
                                }
                                if(sums==number)return sum;
                                else j=3;
                            }
                            else j--;                
                        }
                    }
                }
            }
        }
    }
    return sum;
}
/*

 */