/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Created on October 21st, 2020, 12:45 PM
 * Purpose:  Recursion and Comparison with Simulations/Loops/Approximations
 *           Fibonacci and Hash Expectations/Bloom Filter
 *           Factorial with products and logs
 */

//System Level Libraries
#include <iostream>   //I/O Library
#include <cstdlib>    //Random for simulation
#include <ctime>      //Time to set the seed
#include <cmath>      //Math for Log's and Exp's
#include <iomanip>    //Format Library
using namespace std;  //Library Scope

//User Libraries

//Global Constants
//Science and Math, Conversions, Higher Dimensions

//Function Prototypes
//Fibonacci
unsigned int fibRec(int);  //Fibonacci Recursive
unsigned int fibVar(int);  //Fibonacci Variable Loop-Swap
unsigned int fibAry(int);  //Fibonacci Using an Array
//Bloom Filter Hash
int   hashRnd(int,int);    //Simulation
float hashRec(int,int);    //Recursion
float hashExc(int,int);    //Exact Functional
float hashApx(int,int);    //Approximate Functional
//Factorial
int   factPrd(int);        //Product
int   factRec(int);        //Recursive Product
float factLog(float);      //Recursive Sum

//Execution Starts Here
int main(int argc, char** argv){
    //Set Random Number Seed Here
    srand(static_cast<unsigned int>(time(0)));
    
    //Test the Fibonacci Sequence Implementations
    cout<<"Fibonacci Sequence Comparisons"<<endl;
    cout<<"Term  Recursion    Var Swap       Array  Phi Approx"<<endl;
    for(int i=0;i<=40;i+=4){
        cout<<setw(3)<<i<<setw(12)<<fibRec(i)
            <<setw(12)<<fibVar(i)<<setw(12)<<fibAry(i)<<setw(12)
            <<static_cast<float>(fibVar(i))/fibVar(i-1)<<endl;
    }
    
    //Test the Bloom Filter Hash Comparisons
    int n=200;//Size the bit array/vector
    int k=10; //Number of hashes
    int m=20; //Number of elements in dictionary to hash
    cout<<endl<<"Hash Comparisons with Bloom Filter"<<endl;
    cout<<"Size of the bit array/vector  n = "<<n<<endl
        <<"Number of Hashes              k = "<<k<<endl
        <<"Number of dictionary elements m = "<<m<<endl;
    cout<<"c = (1-1/n)  E = Expected Value of Hashed Bit Vector"<<endl;
    cout<<"Simulation           sum(1,km)(bitAray[rand()%n]=1)   = "<<hashRnd(n,k*m)<<endl;
    cout<<"Recursive Call       Ekm = c*Ekm-1+1                  = "<<hashRec(n,k*m)<<endl;
    cout<<"Exact Calculation    Ekm = n*(1-c^km)                 = "<<hashExc(n,k*m)<<endl;
    cout<<"Approx Calculation   Ekm = n*(1-exp(-km/n)            = "<<hashApx(n,k*m)<<endl;
    
    
    //Test the Factorial Implementations
    n=12;
    cout<<endl<<"Factorial Implementations"<<endl;
    cout<<"Recursive Product   "<<n<<"! = "<<factRec(n)<<endl;
    cout<<"Product Loop        "<<n<<"! = "<<factPrd(n)<<endl;
    cout<<"Recursive Log Sum   "<<n<<"! = "<<exp(factLog(n))<<endl;
    
    //Clean up - File closing, memory deallocation, etc....

    //Exit Stage Right!
    return 0;
}

//Factorial using the product implemented with a for-loop
int factPrd(int n){
    if(n<=1||n>12)return 1;//Out of range for int
    int prod=1;            //Initialize the product
    //Loop on the product
    for(int i=2;i<=n;i++){
        prod*=i;
    }
    return prod;
}

//Simplest recursive call by Product
int factRec(int n){
    //Base Conditions as well as out of range
    if(n<=1||n>12)return 1;//Out of range for int
    return  n*factRec(n-1);//Decreasing recursion
}

//Recursive sum of Logs for the Factorial
float factLog(float n){
    //Base Conditions
    if(n<=1)return 0;
    return log(n)+factLog(n-1);
}

//Exact Bloom Filter Calculation
float hashExc(int n,int km){
    float c=(1-1.0f/n);//Recursive product term
    return n*(1-pow(c,km));
}

//Approximate Bloom Filter Calculation
float hashApx(int n,int km){
    return n*(1-exp(-km/n));
}

//The Recursive Bloom Filter Expected Value of Bit Vector Hash Values
float hashRec(int n,int km){
    //Base Case for Recursion
    if(km<=0)return 0;
    if(km==1)return 1;
    //Product and Sum
    float c=(1-1.0f/n);
    return c*hashRec(n,km-1)+1;
}

//Simulation of Hashing a Bit Vector of Size n with k*m hashes
int hashRnd(int n,int km){
    //Dynamically Create the Bit Vector
    char *bitAray=new char[n];
    //Initialize all values to 0
    for(int i=0;i<n;i++){
        bitAray[i]=0;
    }
    //Hash the array km times setting the hash bit to 1
    for(int i=0;i<km;i++){
        bitAray[rand()%n]=1;
    }
    //Now sum the hashed array
    int sum=0;
    for(int i=0;i<km;i++){
        sum+=bitAray[i];
    }
    //Clean up and return the value from the simulation
    delete []bitAray;
    return sum;
}

//Calculating the Fibonacci sequence using a Dynamic Array
unsigned int fibAry(int i){
    //Base Condition with overflow limits
    if(i==0)return 0;
    if(i<=1||i>46)return 1;
    //Size and fill the array defined by sequence
    unsigned int *f=new unsigned int[i+1];
    f[0]=0,f[1]=1;
    for(int cnt=2;cnt<=i;cnt++){
        f[cnt]=f[cnt-1]+f[cnt-2];
    }
    //Clean up and return
    unsigned int ans=f[i];
    delete []f;
    return ans;
}

//Fibonacci sequence using a loop - variable - swap
unsigned int fibVar(int i){
    //Base Condition with overflow limits
    if(i==0)return 0;
    if(i<=1||i>46)return 1;
    //Declare, Initialize and Loop
    int fi,fim1=1,fim2=0;
    for(int cnt=2;cnt<=i;cnt++){
        fi=fim1+fim2;
        fim2=fim1;
        fim1=fi;
    }
    return fi;
}

//The famous Fibonacci Recursive Function
unsigned int fibRec(int i){
    //Base Condition with overflow limits
    if(i==0)return 0;
    if(i<=1||i>46)return 1;
    //Fn=Fn-1+Fn-2
    return fibRec(i-1)+fibRec(i-2);
}