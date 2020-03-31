/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on FEbruary 13, 2019, 11:00 AM
 * Purpose: 
 */

//System Libraries Here
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Data.h"
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
Data *fill(int);
int *fillAry(Data*);
int partit (int*,int,int); 
void shellS(int*,int);
void print(int*,int,int);
void heapify(int*,int,int);
void heapS(int*,int);
void merge(Data *,int,int,int);
void mrgSort(Data *,int,int);
void destroy(Data *);
void print(Data *,int);
void swap(int*,int*);
void quickS(int*,int,int); 

//Program Execution Begins Here
int main(int argc, char** argv) {
    //initialize random seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Allocate the arrays
    int n=21000000,perLine=10;
    Data *a=fill(n);
    int *b=fillAry(a);
    int *c=fillAry(a);
    int *d=fillAry(a);
    
    //declare variables for timing analysis
    int beg,end;
    int mergeT,quickT,shellT,heapT;
    
    /*//Print the arrays
    print(a,perLine);
    print(b,n,perLine);
    print(c,n,perLine);
    print(d,n,perLine);*/
    
    //Sort the arrays
    
    beg=time(0);
    mrgSort(a,0,a->size);
    end=time(0);
    mergeT=end-beg;
    
    beg=time(0);
    mrgSort(a,0,n-1);
    end=time(0);
    quickT=end-beg;
    
    beg=time(0);
    heapS(c,n);
    end=time(0);
    heapT=end-beg;
    
    beg=time(0);
    shellS(c,n);
    end=time(0);
    shellT=end-beg;
    
    //print array
    cout<<endl<<endl<<"Merge Sort : "<<mergeT<<" sec";
    //print(a,perLine);
    
    cout<<endl<<endl<<"Quick Sort : "<<quickT<<" sec";
    //print(b,n,perLine);
    
    cout<<endl<<endl<<"heap Sort  : "<<heapT<<" sec";
    //print(c,n,perLine);
    
    cout<<endl<<endl<<"Shell Sort : "<<shellT<<" sec";
    //print(d,n,perLine);
    
    //Deallocate data
    destroy(a);
    delete b;
    delete c;
    delete d;
    
    //Exit stage right
    return 0;
}
//9519418408

void print(int *arr,int n,int PerLine){ 
    for (int i=0;i<n;i++){
        if(i%PerLine==0)cout<<endl;
        cout<<arr[i]<<" ";
    }
    cout<<endl;
} 
void shellS(int *arr, int n){ 
    // Start with a big gap, then reduce the gap 
    for (int gap=n/2;gap>0;gap/=2) 
    { 
        // Do a gapped insertion sort for this gap size. 
        // The first gap elements a[0..gap-1] are already in gapped order 
        // keep adding one more element until the entire array is 
        // gap sorted  
        for (int i=gap;i<n;i+=1) 
        { 
            // add a[i] to the elements that have been gap sorted 
            // save a[i] in temp and make a hole at position i 
            int temp=arr[i]; 
  
            // shift earlier gap-sorted elements up until the correct  
            // location for a[i] is found 
            int j;             
            for (j=i;j>=gap&&arr[j-gap]>temp;j-=gap) 
                arr[j]=arr[j-gap]; 
              
            //  put temp (the original a[i]) in its correct location 
            arr[j]=temp; 
        } 
    } 
} 
void heapify(int *arr,int n,int i){ 
    int largest=i; // Initialize largest as root 
    int l=2*i+1; // left = 2*i + 1 
    int r=2*i+2; // right = 2*i + 2 
  
    // If left child is larger than root 
    if (l<n&&arr[l]>arr[largest]) 
        largest=l; 
  
    // If right child is larger than largest so far 
    if (r<n&&arr[r]>arr[largest]) 
        largest=r; 
  
    // If largest is not root 
    if (largest!=i) 
    { 
        swap(&arr[i],&arr[largest]); 
  
        // Recursively heapify the affected sub-tree 
        heapify(arr,n,largest); 
    } 
} 
  
// main function to do heap sort 
void heapS(int *arr,int n){ 
    // Build heap (rearrange array) 
    for (int i=n/2-1;i>=0;i--) 
        heapify(arr,n,i); 
  
    // One by one extract an element from heap 
    for (int i=n-1;i>=0;i--) 
    { 
        // Move current root to end 
        swap(&arr[0],&arr[i]); 
  
        // call max heapify on the reduced heap 
        heapify(arr,i,0); 
    } 
} 

void swap(int*a,int*b){ 
    int t=*a; 
    *a=*b; 
    *b=t; 
} 

void destroy(Data *a){
    //Deallocate data elements
    delete []a->hilow;
    delete []a->c;
    delete a;
}

void mrgSort(Data *a,int beg,int end){
    int center=(beg+end)/2;
    if((center-beg)>1)mrgSort(a,beg,center);
    if((end-center)>1)mrgSort(a,center,end);
    merge(a,beg,center,end);
}

void merge(Data *a,int beg,int nlow,int nhigh){
    //Create a merged array
    int span=nhigh-beg;    //Span the range to merge
    int cntl=beg,cnth=nlow;//Independent counters to merge
    //Fill the array
    for(int i=0;i<span;i++){
        if(cntl==nlow){
            a->c[i]=a->hilow[cnth++];
        }else if(cnth==nhigh){
            a->c[i]=a->hilow[cntl++];
        }else if(a->hilow[cntl]<a->hilow[cnth]){
            a->c[i]=a->hilow[cntl++];
        }else{
            a->c[i]=a->hilow[cnth++];
        }
    }
    //Copy back
    for(int i=0;i<span;i++){
        a->hilow[beg+i]=a->c[i];
    }
}

void print(Data *a,int perLine){
    //First print the unsorted array
    cout<<endl;
    for(int i=0;i<a->size;i++){
        cout<<a->hilow[i]<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}

Data *fill(int n){
    //Allocate memory
    Data *data=new Data;
    data->size=n;
    data->hilow=new int[n];
    data->c=new int[n];
    for(int i=0;i<n;i++){
        data->hilow[i]=rand()%9000000+1;
        data->c[i]=0;
    }
    return data;
}

int *fillAry(Data *data){
    //Allocate memory
    int *ary=new int[data->size];
    for(int i=0;i<data->size;i++){
        ary[i]=data->hilow[i];
    }
    return ary;
}

int partit (int *arr, int low, int high){ 
    int pivot=arr[high];    // pivot 
    int i=(low-1);  // Index of smaller element  
    for(int j=low;j<=high-1;j++){ 
        // If current element is smaller than or 
        // equal to pivot 
        if(arr[j]<=pivot){ 
            i++;    // increment index of smaller element 
            swap(&arr[i],&arr[j]); 
        } 
    } 
    swap(&arr[i+1],&arr[high]); 
    return (i+1); 
} 
  
/* The main function that implements QuickSort 
 arr[] --> Array to be sorted, 
  low  --> Starting index, 
  high  --> Ending index */
void quickS(int *arr,int low,int high){ 
    if (low<high){ 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi=partit(arr,low,high); 
        // Separately sort elements before 
        // partition and after partition 
        quickS(arr,low,pi-1); 
        quickS(arr,pi+1,high); 
    } 
} 
