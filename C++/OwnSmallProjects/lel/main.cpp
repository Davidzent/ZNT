/* 
 * File:   main.cpp
 * Author: Dr. Mark E. Lehr
 * Purpose:  Common searching and sorting algorithms
 */

//System Libraries Here
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions
int Ob,Oi;

//Function Prototypes Here
void prntAry(const int [],int,int);
void fillAry(int [],int,int,int);
void swap(int &,int &);
void smlLst(int [],int,int);
void mrkSort(int [],int);
int  linSrch(int [],int, int);
int  binSrch(int [],int, int);
void bublSrt(int [],int);
void selSort(int [],int);
void copyAry(int [],int [],int);

Gradetype lol;
//Program Execution Begins Here
int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare all Variables Here
    const int SIZE=3000;
    int array[SIZE],brray[SIZE];
    int perLine=10;
    Ob,Oi = 0;
        
    //Finish initializing the rest of the array
    fillAry(array,SIZE,0,0);
    copyAry(brray,array,SIZE);
    array[SIZE - 2] = -1;
    //Print the values in the array
    //prntAry(array,SIZE,perLine);
    //prntAry(brray,SIZE,perLine);
    
    //Sort the array the for all positions
    //mrkSort(array,SIZE);
    //bublSrt(array,SIZE);
    //selSort(brray,SIZE);
    
    //Test the linear search by randomly choosing a value and
    //determine if found;
//    int value=rand()%(highRng-lowRng+1)+lowRng;
// 
//    cout<<"Using the Linear Search"<<endl;
//    cout<<"The value "<<value<<" was found at position "
//            <<linSrch(array,SIZE,value)<<endl;
//    cout<<"Using the Binary Search"<<endl;
//    cout<<"The value "<<value<<" was found at position "
//            <<binSrch(brray,SIZE,value)<<endl;
    
    int numLoop = 1000000;
    int beg=time(0);
    for(int i = 0; i < numLoop; i++){
        int value=rand()%SIZE;
        int memes = linSrch(array,SIZE,value);
        //cout << "Chicken";
    }
    int end = time(0);
    cout << endl << (end-beg)/(float)numLoop;;
    
    
    
    
    
    //Print the values in the array
    //prntAry(array,SIZE,perLine);
    //prntAry(brray,SIZE,perLine);

    //Exit
    return 0;
}

void copyAry(int copyIt[],int source[],int n){
    for(int i=0;i<n;i++){
        copyIt[i]=source[i];
    }
}

void selSort(int a[],int n){
    //Loop and declare variables
    int indx,min;
    //Ob += 6;
    for(int pos=0;pos<n-1;pos++){
        //Opos += 9
        //Find the smallest in the list, swap after finding
        min=a[pos];indx=pos;
        for(int i=pos+1;i<n;i++){
            //Oi += 4
            if(a[i]<min){
                //POs += 3
                min=a[i];
                indx=i;
            }
        }
        //Oa += 5
        //Perform the swap
        a[indx]=a[pos];
        a[pos]=min;
    }
}

void bublSrt(int a[],int n){
    //Keep looping and comparing until no swaps are left
    bool swap;
    do{
        swap=false;
        //Check the list and Swap when necessary
        for(int i=0;i<n-1;i++){
            if(a[i]>a[i+1]){
                int temp=a[i];
                a[i]=a[i+1];
                a[i+1]=temp;
                swap=true;
            }
        }
    }while(swap);
}

int  binSrch(int a[],int n, int val){
    //Initialize end points which are indexes
    int lowEnd=0;
    int highEnd=n-1;
    
    //Loop until value found not indexes
    do{
        int middle=(highEnd+lowEnd)/2;
        if(val==a[middle])return middle;
        else if(val>a[middle])lowEnd=middle+1;
        else highEnd=middle-1;
    }while(lowEnd<=highEnd);
    
    //Not found
    return -1;
}

int  linSrch(int a[],int n, int val){
    Ob += 2;
    for(int indx=0;indx<n;indx++){
        Oi += 4;
        if(val==a[indx])return indx;
    }
    return -1;
}

void fillAry(int a[],int n,int hr,int lr){
    for(int indx=0;indx<n;indx++){
        a[indx]=rand()%n;
    }
}

void prntAry(const int a[],int n,int perLine){
    //Print the values in the array
    cout<<endl<<"The Array Values"<<endl;
    for(int indx=0;indx<n;indx++){
        cout<<a[indx]<<" ";
        if(indx%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

void mrkSort(int a[],int n){
    for(int pos=0;pos<n-1;pos++){
        smlLst(a,n,pos);
    }
}

void smlLst(int a[],int n,int pos){
    for(int i=pos+1;i<n;i++){
        if(a[pos]>a[i]){
            swap(a[pos],a[i]);
        }
    }
}

void swap(int &a,int &b){
    int temp=a;
    a=b;
    b=temp;
}