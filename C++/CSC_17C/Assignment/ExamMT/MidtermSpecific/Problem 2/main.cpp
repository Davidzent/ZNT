
/* 
 * File:   main.cpp
 * Author: david guijosa
 *
 * Created on April 24, 2019, 10:08 AM
 */

//Libraries
#include <ctime>//Speed
#include <iostream>//I/O
#include <iomanip>
using namespace std;

//No Global Constants

//Function Prototypes
void prnt(int*,const int);
void Sesort(int *,const int,long long int&);
void Busort(int *,const int,long long int&);
//Execution begins here
int main(int argc, char** argv) {
    //set random seed
    srand(static_cast<unsigned int>(time(0)));
    //declare variables
    const int size=10000;
    int *ary=new int[size];
    int *ary2=new int[size];
    int Bsort,Ssort;
    int beg,end;
    float timeB,timeS;
    long long int oPB,oPS;
    
    //initialize variables
    for(int i=0;i<size;i++){
        ary[i]=rand()%size;
        ary2[i]=ary[i];
    }
    cout<<"size = "<<size<<endl;
    oPB=0;
    beg=time(0);
    Busort(ary,size,oPB);
    end=time(0);
    timeB=end-beg;
    oPS=0;
    beg=time(0);
    Sesort(ary2,size,oPS);
    end=time(0);
    timeS=end-beg;
    //output allocated here
    //prnt(ary,size);
    //prnt(ary2,size);
    cout<<"Selection sort:"<<endl;
    cout<<"Time : "<<timeS<<endl;
    cout<<"Average number of operations = "<<oPS<<endl;
    cout<<"Bubble sort:"<<endl;
    cout<<"Time : "<<timeB<<endl;
    cout<<"Average number of operations = "<<oPB<<endl;
    //Exit
    delete ary2;
    delete ary;
    return 0;
}
void prnt(int *a,const int size){
    for(int i=0;i<size;i++){
        cout<<a[i]<<"  ";
        if(i%10==9)cout<<endl;
    }
}

void Busort(int *a ,const int size,long long int &op){
    op++;
    for(int i=0;i<size-1;i++){
        op+=6;
        for(int j=i+1;j<size;j++){
            if(a[i]>a[j]){
                int temp=a[i];
                a[i]=a[j];
                a[j]=temp;
                op+=7;
            }
            op+=5;
        }
    }
}
void Sesort(int *a ,const int size,long long int &op){
    int min=0;
    op+=2;
    for(int i=0;i<size-1;i++){
        for(int j=i;j<size;j++){
            if(a[j]>a[j+1])min=j+1,op+=2;
            op+=5;
        }
        int temp=a[i];
        a[i]=a[min];
        a[min]=temp;
        op+=10;
        }
}
