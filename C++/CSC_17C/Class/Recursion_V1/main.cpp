/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on October 14th, 2020 6pm
 * Purpose:  More Recursions
 */

//System Level Libraries
#include <iostream>   //I/O Library
#include <cmath>      //Comparitive Functions
#include <iomanip>    //Formatting Library
using namespace std;  //Library Scope

//User Libraries

//Global Constants
//Science and Math, Conversions, Higher Dimensions
const float PId4=atan(1);//45 degree angle

//Function Prototypes
float  expRec(float);      //Another way to do the exp(), not accurate
float  expRecm1(float);    //Recursive e^x-1
double expRec(double);     //The accurate approximations
int    bCoef(int,int);     //Binomial Coefficients and Pascal's Triangle
int    gcd(int,int);       //Euclid's, the greatest common denominator
float  sinAprx(float);     //Mutual Recursion with the cos
float  cosAprx(float);     //Mutual Recursion with the sin
void   hanoi(int,int,int,int);//Towers of Hanoi Solution
int    mrkMax(int *,int,int);//Super Slow Max - O(nlgn)



//Execution Starts Here
int main(int argc, char** argv){
    //Set Random Number Seed Here
    
    //Declare Variables - Known and Unknown, units, range, description
    float fx;      //Floating Real
    double dx;     //Floating Double
    int rows;      //Size of the Triangular matrix of Pascal's Triangle
    int num,denom; //Simplifying a fraction numerator/denominator
    
    //Initialize Variables
    fx=5;
    dx=5;
    rows=20;
    num=154;
    denom=105;
    
    //Map inputs to outputs -> i.e. process the inputs
    
    //Display the outputs
    cout<<"The Exponential Recursion e(x)=e(x/2)*e(x/2)"<<endl;
    cout<<"Approximate float  exponential ~ e^"<<fx<<" = "<<expRec(fx)<<endl;
    cout<<"Approximate double exponential ~ e^"<<dx<<" = "<<expRec(dx)<<endl;
    cout<<"Exact              exponential = e^"<<fx<<" = "<<exp(fx)<<endl;
    
    cout<<endl<<endl;

    cout<<endl<<"Pascal's Triangle using Cn,m -> Binomial Coefficients"<<endl;
    for(int row=0;row<=rows;row++){
        cout<<"n = "<<setw(2)<<row<<"      ";
        for(int col=0;col<=row;col++){
            cout<<bCoef(row,col)<<" ";
        }
        cout<<endl;
    }
    cout<<endl<<endl;
    
    cout<<"The GCD Recursion using %"<<endl;
    cout<<"Output the ratio as relative prime"<<endl;
    cout<<num<<"/"<<denom<<" = "
            <<num/gcd(num,denom)<<"/"<<denom/gcd(num,denom)<<endl;
    
    
    cout<<endl<<endl;
    cout<<"Mutual Recursion of the Sin and Cos using the 1/2 angle"<<endl;
    cout<<"Same problem as float exp(), because base of Cos, need double"<<endl;
    cout<<"angle = "<<PId4<<" radians"<<endl;
    cout<<"sin approx("<<PId4<<") = "<<sinAprx(PId4)<<endl;
    cout<<"sin  exact("<<PId4<<") = "<<sin(PId4)<<endl;
    cout<<"cos approx("<<PId4<<") = "<<cosAprx(PId4)<<endl;
    cout<<"cos  exact("<<PId4<<") = "<<cos(PId4)<<endl;
    
    cout<<endl<<endl;
    int nDisks=3;
    cout<<"Playing Hanoi Towers using Recursion"<<endl;
    cout<<"Number of theoretical moves to make in Hanoi Towers = "<<
            pow(2,nDisks)-1<<" for "<<nDisks<<" disks"<<endl<<endl;
    hanoi(4,1,2,3);
    
    cout<<endl<<endl;
    cout<<"Max Recursion O(nLogn) but points to How To Sort"<<endl;
    int a[]={1,2,3,4,5,4,3,2,1};
    cout<<"Max Array Element = "<<mrkMax(a,0,sizeof(a)/sizeof(int))<<endl;
    int b[]={6,2,3,4,5,4,3,2,1};
    cout<<"Max Array Element = "<<mrkMax(b,0,sizeof(b)/sizeof(int))<<endl;
    int c[]={1,2,3,4,5,4,3,2,7};
    cout<<"Max Array Element = "<<mrkMax(c,0,sizeof(c)/sizeof(int))<<endl;
    
    //Clean up - File closing, memory deallocation, etc....

    //Exit Stage Right!
    return 0;
}

//Function Implementations
int mrkMax(int *a,int beg,int end){
    //Base Case
    if(end-beg<=1)return a[beg];
    //Recursive Case
    int half=(beg+end)/2;
    int m1=mrkMax(a,beg,half);
    int m2=mrkMax(a,half,end);
    return m1>m2?m1:m2;
}


void   hanoi(int nDisks,int src,int spare,int dest){
    static int mvCnt;
    if(nDisks>1)hanoi(nDisks-1,src,dest,spare);
    cout<<++mvCnt<<" Move -> "<<src<<" to -> "<<dest<<endl;
    if(nDisks>1)hanoi(nDisks-1,spare,src,dest);
}

float cosAprx(float x){
    //Base Case
    float tol=1.0e-6f;
    if(abs(x)<tol)return 1-x*x/2;
    //Recursive Call
    float a=cosAprx(x/2);
    float b=sinAprx(x/2);
    return a*a-b*b;
}

float sinAprx(float x){
    //Base Case
    float tol=1.0e-6f;
    if(abs(x)<tol)return x-x*x*x/6;
    //Recursive Call
    return 2*sinAprx(x/2)*cosAprx(x/2);
}

int gcd(int m,int n){
    //Base Case
    if(m==0)return n;
    //Recursive Call
    if(m>=n)return gcd(m%n,n);
    return gcd(n%m,m);
}

int bCoef(int n,int j){
    //Base Case
    if(j==0)return 1;
    if(j==n)return 1;
    //Recursive Call
    return bCoef(n-1,j-1)+bCoef(n-1,j);
}

double expRec(double x){
    //Base Case
    double tol=1.0e-6f;
    if(abs(x)<tol)return 1+x;
    //Recursive Call
    double a=expRec(x/2);
    return a*a;
}

float expRec(float x){
    //Base Case
    float tol=1.0e-6f;
    if(abs(x)<tol)return 1+x;
    //Recursive Call
    float a=expRec(x/2);
    return a*a;
}