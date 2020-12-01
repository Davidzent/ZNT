
/* 
 * File:   main.cpp
 * Author: david guijosa
 *
 * Created on April 24, 2019, 10:08 AM
 */

//Libraries
#include <ctime>//Speed
#include <iostream>//I/O
using namespace std;

//No Global Constants

//Function Prototypes
void prnt(int*,const int);
int binSrc(int*,int,const int,int,long long int&);
int linSrc(int*,const int,int,long long int&);
void sort(int *,const int,long long int);
//Execution begins here
int main(int argc, char** argv) {
    //set random seed
    srand(static_cast<unsigned int>(time(0)));
    //declare variables
    const int size=350;
    int *ary=new int[size];
    int n;
    int bins,lins;
    int beg,end;
    float timbin,timlin;
    long long int oPlin,oPbin;
    int looplin=100000;
    int loopbin=15000;
    //initialize variables
    for(int i=0;i<size;i++){
        ary[i]=rand()%90+10;
    }
    sort(ary,size,oPbin);
    cout<<"size = "<<size<<endl;
    //cin>>n;
    n=100;
    oPlin=0;
    beg=time(0);
    for(int i=0;i<looplin;i++){
        lins=linSrc(ary,size,n,oPlin);
    }
    end=time(0);
    timlin=end-beg;
    oPbin=0;
    beg=time(0);
    for(int i=0;i<loopbin;i++){
        //sort(ary,size,oPbin);
        //bins=binSrc(ary,0,size,n,oPbin);
        
    }
    end=time(0);
    timbin=end-beg;
    //output allocated here
    //prnt(ary,size);
    cout<<"Binary search: number "<<n<<" is located in this position :"<<bins<<endl;
    cout<<"Time : "<<timbin/loopbin<<endl;
    cout<<"Average number of operations = "<<oPbin/loopbin<<endl;
    cout<<"Linear search: number "<<n<<" is located in this position :"<<lins<<endl;
    cout<<"Time : "<<timlin/looplin<<endl;
    cout<<"Average number of operations = "<<oPlin/looplin<<endl;
    //Exit
    delete ary;
    return 0;
}
void prnt(int *a,const int size){
    for(int i=0;i<size;i++){
        cout<<a[i]<<"  ";
        if(i%10==9)cout<<endl;
    }
}
int binSrc(int *arr,int pos,const int size,int n,long long int&op) {
    if (size>=pos){
        int mid=pos+(size-pos)/2;
        if (arr[mid]==n){
            op+=2;      //finds arr[mid] then checks if they are equal
            return mid+1; 
        }
        if (arr[mid]>n){
            op+=5;      //finds arr[mid] + check + previous operations + the one in the return    
            return binSrc(arr,pos,mid-1,n,op);
        }
        op+=11;         //check + declare  + initialize + sub + div + sum + 
                        //previous - 1 of the last return that was not called + one in return 
        return binSrc(arr,mid+1,size,n,op); 
    } 
    return -1; 
}

int linSrc(int *arr,const int size,int n,long long int&op){
    for(int i=0;i<size;i++){
        op+=2;          //in the first run it declares and checks if i is less than size
                        //in the following it just check if is is less than size
                        //and increases
        if(n==arr[i]){
            op+=2;      //finds arr[i[ and then check if it is equal
            return i+1;
        }
    }
    return -1;
}

void sort(int *a ,const int size,long long int op){
    op++;
    for(int i=0;i<size-1;i++){
        op+=3;
        for(int j=i+1;j<size;j++){
            if(a[i]>a[j]){
                a[i]=a[i]^a[j];
                a[j]=a[i]^a[j];
                a[i]=a[i]^a[j];
                op+=18;
            }
            op+=4;
        }
    }
}
