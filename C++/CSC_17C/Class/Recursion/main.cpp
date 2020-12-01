/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on October 13th, 2020
 * Purpose:  Examples of Recursion
 */

//System Libraries
#include <iostream>  //I/O Library
#include <iomanip>   //Formatting
#include <ctime>     //Setting random seed with time
#include <cstdlib>   //Random Function
using namespace std;

//User Libraries

//Global Constants Only
//Well known Science, Mathematical and Laboratory Constants

//Function Prototypes
int sumSrs(int,int);                //Recursive Sum C^i
int pow(int,int);                   //Recursive x^y integer
float pow(float,int);               //Recursive x^y power
float sav(float,float,int);         //Recursive p*(1+i)^n
float retRec(float,float,float,int);//Recursive Retirement Function
float ret(float,float,float,int);   //Formulaic Retirement function
float retSav(float,float,float,int);//Retirement function in Savings Form
float expSum(int,int);              //Expected Value sum
float expSumRec(int,int);           //Recursive Expected Value sum
int   simESum(int,int);             //Simulation of Expected Value
int   fibo(int);                    //Non-Recursive Fibonacci
int   fiboRec(int);                 //Recursive Fibonacci
float fiboAry(int);                 //Non-Recursive Fibonacci
int   factRec(int);                 //Factorial Recursion

//Execution of Code Begins Here
int main(int argc, char** argv) {
    //Set the random number seed here
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare all variables for this function
    int r,e,n;
    float d,i,p;
    
    //Initialize all known variables
    r=2;        //Rational value for sum of 2 power series
    e=10;       //Exponent of the power series
    n=49;       //Number of compounding periods
    d=10000;    //$ Initial Deposit
    i=5.0f/100; //% Interest Rate
    p=0;        //$ Principal
    
    //Let the Recursion Begin!
    cout<<"Recursive Integer Power "<<r<<"^"<<e<<" = "<<pow(r,e)<<endl<<endl;
    
    cout<<"Recursive Series Sum i=0 to "<<e<<" of "<<r<<"^i"<<" = "
            <<sumSrs(r,e)<<endl;
    cout<<"which should equal Formula = (1-"<<r<<"^"<<e+1<<")/(1-"<<r<<")"
            <<" = "<<(1-pow(r,e+1))/(1-r)<<endl<<endl;
    
    cout<<"Recursive Savings = $"<<d<<"(1+"<<i<<")^"<<n<<" = $"
            <<sav(d,i,n)<<endl<<endl;
    
    cout<<"Formula Retirement                  S"<<n<<"= "<<(1+i)
            <<"*S"<<(n-1)<<"+"<<d<<" = $"<<ret(p,d,i,n)<<endl;
     cout<<"Recursion Retirement                S"<<n<<"= "<<(1+i)
             <<"*S"<<(n-1)<<"+"<<d<<" = $"<<retRec(p,d,i,n)<<endl;
     cout<<"Retirement using Savings Recursion  S"<<n<<"= "<<(1+i)
             <<"*S"<<(n-1)<<"+"<<d<<" = $"<<retSav(p,d,i,n)<<endl<<endl;
     
     //Birthday Problem Expectations
     n=365;//n=365 days
     int m=80;//Number students in the class
     int diffCnt=1;
     cout<<"A group size that would have the same Expected Number of Birthdays"
             <<endl;
     cout<<fixed<<setprecision(2)<<showpoint;
     for(int i=5;i<=m;i++){
         int nBDsame=expSum(i,n)+1;
         if(i-nBDsame==diffCnt){
            cout<<i<<" students -> "<<expSum(i,n)<<" -> "<<diffCnt+1
                    <<" same Birthdays"<<endl;
            diffCnt++;
         }
     }
     
     //Compare the recursive and formulaic function
     cout<<endl;
     cout<<"Formula   Expected Value("<<m<<","<<n<<") = "<<expSum(m,n)<<endl;
     cout<<"Recursive Expected Value("<<m<<","<<n<<") = "<<expSumRec(m,n)<<endl;
     cout<<"Simulated Value         ("<<m<<","<<n<<") = "<<simESum(m,n)<<endl;
 
     //Compare the solutions
     int fibN=15;
     cout<<endl;
     cout<<"Recursive Fibonacci internally ("<<fibN<<") = "<<fibo(fibN)<<endl;
     cout<<"Recursive Fibonacci            ("<<fibN<<") = "<<fiboRec(fibN)<<endl;
     cout<<"Array Fibonacci                ("<<fibN<<") = "<<fiboAry(fibN)<<endl;
     cout<<fixed<<setprecision(5)<<showpoint;
     cout<<"Golden Ratio = "<<1.0f*fiboAry(100)/fiboAry(99)<<endl;
     
     cout<<endl;
     int factN=10;
     cout<<"The factorial of "<<factN<<"! = "<<factRec(factN)<<endl;
     
     //Exit stage right
    return 0;
}

//Function Implementations
int   factRec(int n){
    //Base Case
    if(n<=1)return 1;
    //Recursive Case
    return factRec(n-1)*n;
}


int fiboRec(int n){
    //Base Case
    if(n==0)return 0;
    if(n==1)return 1;
    //Recursion
    return fiboRec(n-1)+fiboRec(n-2);
}

float fiboAry(int n){
    const int SIZE=1000;
    float fibo[SIZE];
    fibo[0]=0;
    fibo[1]=1;
    for(int i=2;i<=n;i++){
        fibo[i]=fibo[i-1]+fibo[i-2];
    }
    return fibo[n];
}


int fibo(int n){
    //Base Case
    if(n==0)return 0;
    if(n==1)return 1;
    //Recursion
    int cnt=1,fim2=0,fim1=1,fi;
    do{
        fi=fim1+fim2;
        fim2=fim1;
        fim1=fi;
        cnt++;
    }while(cnt<n);
    return fi;
}


int simESum(int m,int n){
    //Test for m and n
    //m number students
    //nDays of year
    if(m>n||m<0)return -1;
    if(n>1000||n<0)return-1;
    
    //Size a max array
    const int SIZE=1000;
    int dysInYr[SIZE];
    
    //Fill the array with zeroes
    for(int i=0;i<SIZE;i++){
        dysInYr[i]=0;
    }
    
    //Randomly fill the array with 1's for each student
    for(int i=1;i<=m;i++){
        dysInYr[rand()%n]=1;//This represents the students birthday
    }
    
    int sum=0;
    for(int i=0;i<n;i++){
        sum+=dysInYr[i];
    }
    
    return sum;
}

float expSumRec(int m,int n){
    //Base Case
    if(m<=1)return 1;
    //Recursive Case
    float c=1-1.0f/n;
    return expSumRec(m-1,n)*c+1;
}

float expSum(int m,int n){
    float c=1-1.0f/n;
    return n*(1-pow(c,m));
}

float retSav(float p,float d,float i,int n){
    float ddivi=d/i;
    return sav(p,i,n)+sav(ddivi,i,n)-ddivi;
}

float ret(float p,float d,float i,int n){
    float cton=pow(1.0f+i,n);
    return p*cton+d/i*(cton-1);
}

float retRec(float p,float d,float i,int n){
    //Base Case
    if(n==0)return p;
    //Function defined from itself
    return retRec(p,d,i,n-1)*(1+i)+d;
}

float sav(float d,float intRate,int n){
    //Base Case
    if(n==0)return d;
    //Function defined from itself
    return sav(d,intRate,n-1)*(1+intRate);
}

float pow(float r,int n){
    //Base Case
    if(n==0)return 1;
    //Function defined from itself
    return pow(r,n-1)*r;
}

int pow(int r,int n){
    //Base Case
    if(n==0)return 1;
    //Function defined from itself
    return pow(r,n-1)*r;
}

int sumSrs(int r,int n){
    //Base Case
    if(n==0)return 1;
    //Function defined from itself
    return sumSrs(r,n-1)+pow(r,n);
}