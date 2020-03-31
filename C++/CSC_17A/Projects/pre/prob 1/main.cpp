/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on 06/05/2018
 * Purpose:  Input something, output it reversed with some modifications
 * Note:Range should be 5 digits, 321 = 00321 reverse = 12300 before subtraction
 *      12300 - 999 = 11301 after subtraction
 *      12300 = 00321 = 321 after reversal and no subtraction
 */

//System Libraries Here
#include <iostream>//cin,cout,endl
#include <cstring> //strlen()
#include <cmath> //math library
using namespace std;
//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, conversions, or the columns for 2-D arrays

//Function Prototypes Here
bool  inRange(char []);//Output true,unsigned or false
bool  reverse(unsigned short,signed short &,char[]);//Output true,short or false
short subtrct(signed short,int);

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int SIZE=80;     //More than enough
    char  digits[SIZE];    //Character digits or not
    unsigned short unShort=0;//Unsigned short
    short snShort=0;         //Signed short
    
    //Input or initialize values Here
    for(int i=0;i<SIZE;i++){digits[i]=0;}
    cout<<"Reverse a number and subtract if possible."<<endl;
    cout<<"Input a number in the range of an unsigned short"<<endl;
    cin>>digits;
    
    //Test if it is in the Range of an unsigned short
    if(!inRange(digits)){
        cout<<"No Conversion Possible"<<endl;
        return 0;
    }
    //Reverse and see if it falls in the range of an signed short
    if(!reverse(unShort,snShort,digits)){
       cout<<"No Conversion Possible"<<endl;
       return 0;
    }
    
    //Now subtract if the result is not negative else don't subtract
    snShort=subtrct(snShort,999);
    
    //Output the result
    cout<<snShort<<endl;
    
    //Exit
    return 0;
}
bool  inRange(char digits[]){
    while(digits[4]==0){
        char temp[5]; 
        for (int i=0;i<5;i++){
            temp[i]=digits[i];}
        digits[0]='0';
        for(int i=1;i<5;i++){
        digits[i]=temp[i-1];}
    }
    for (int i=0;i<80;i++){
        if(i<5&&digits[i]>'9'||i<5&&digits[i]<'0')return false;
        else if(i>4&&digits[i]!=0)return false;
    }
    return true; 
}
bool  reverse(unsigned short unShort,signed short &snShort,char digits[]){
      for (int i=0;i<5;i++){
          unShort+=(digits[i]-48)*pow(10,i);
      }
      snShort=unShort;
      if(unShort<-32767||unShort>32767)return false;
      return true;
}
short subtrct(signed short snShort,int a){
    snShort-=a;
    if(snShort>=0)return snShort;
    return snShort+=a;
}
