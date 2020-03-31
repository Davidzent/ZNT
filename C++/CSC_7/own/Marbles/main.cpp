/* 
 * File:   main.cpp
 * Author: Guijosa, David
 *
 * Created on October 30, 2019, 12:58 PM
 * purpose: to know what is the best way to out marbles in a box
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
long int *solve(long int*,long int*,long int,int);

int main(int argc, char** argv) {
    //declare variables
    const int size=2;               
    long int price[size],hold[size];
    long int input;
    long int *ans;
    char name[20]="inputs.txt";     //file name
    ifstream file;
    file.open(name);                //open file
    //calculate
    while(file>>input&&input>0&input<=2000000000){      //check if there are stuff in the file and if the input is not less than 0
                                                        //range (0,2000000000)
        for(int i=0;i<size;i++)file>>price[i]>>hold[i]; //inserts the price and the number that a box can handle 
        ans=solve(price,hold,input,size);   //finds the values
        if(ans[0]==0&&ans[1]==0)cout<<"failed"<<endl;   //if the returned value is 0s then there was no answer
        else{
            for(int i=0;i<size;i++)cout<<ans[i]<<" ";
            cout<<endl;
        }
    }
    //Exit
    file.close();   //close the file
    delete ans;     //clean memory
    return 0;
}
long int *solve(long int *price,long int *hold,long int quantity ,int size){
    long int *ans;
    ans=new long int[size];
    double permarble[size];
    for(int i=0;i<size;i++){
        permarble[i]=(float)price[i]/hold[i];   //price of one marble in a box
        ans[i]=0;
    }
    int cheapunit=0;        //cheapest box
    for(int i=1;i<size;i++){
        if(permarble[cheapunit]>permarble[i])cheapunit=i;
    }
    long int total=0;       //total of marbles that have a box
    while(total<quantity){
        ans[cheapunit]++;   //increase the number of cheap boxes to get
        total+=hold[cheapunit]; //increase the number of marbles that are in a box
    }
    if(total==quantity){return ans;}
    else{
        //decreases the hold of a box if the marbles added overpass the owned marbles
        do{
            total-=hold[cheapunit];   
            ans[cheapunit]--;
        }while(abs(total-quantity)%hold[!cheapunit]!=0&&total>0);//if the number is divisible by the expensive box then stop
                                                                 //or if the total try to become negative
        while(total<quantity){
            ans[!cheapunit]++;                                  //increase the number of expensive boxes to get 
            total+=hold[!cheapunit];                            //counts the total marbles that are in a box
        }
        if(total!=quantity)for(int i=0;i<size;i++)ans[i]=0;
    }
    return ans;
}
