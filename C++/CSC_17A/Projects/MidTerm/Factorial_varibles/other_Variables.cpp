/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on Oct 27, 2018, 11:00 AM
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
using namespace std;

//User Libraries Here
#include "ArrayOfvariables.h"
//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
aray *crtary(int *,float *,char *,short *,long *,double *,
    unsigned int *,unsigned char *,unsigned long*,unsigned short*,
long long *,long double *,unsigned long long *,int);
void factorial(aray*);
void posible(aray*);
void print(int*);
int *big(aray*);
void destroy(aray*);
void stop(aray*);
//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    int *aryint;
    float *aryflt;
    char *arychr;
    unsigned short *aryushr;
    short *aryshrt;
    long *arylong;
    double *arydbl;
    unsigned int *aryuint;
    unsigned char *aryuchr;
    unsigned long *aryulng;
    long long *lnglng;
    long double *lngdbl;
    unsigned long long *ulnglng;
    int size=1000;
    int *max;
    string type;
    //create arrays
    aray *info=crtary(aryint,aryflt,arychr,aryshrt,arylong,arydbl,aryuint,aryuchr,aryulng,
            aryushr,lnglng,lngdbl,ulnglng,size);
    //Try for possible answers
    posible(info);
    //find the bigger factorial possible
    max=big(info);
    //output data
    print(max);
    //Exit
    destroy(info);
    return 0;
}
void stop(aray*arrays){
    for(int val=1;val<arrays->size;val++){
        if(arrays->ulnglng[val]==arrays->ulnglng[val-1]*(val+1))max[0]=val+1;
        else val=arrays->size;
    }
}
aray *crtary(int *nt,float *flt,char *chr,short *shrt,long *lng,
        double *dlbl,unsigned int *unt,unsigned char *uchr,unsigned long*ulng,
        unsigned short *ushrt,long long *lnglng,long double *lngdbl,
        unsigned long long *ulnglng,int size){
    aray *arrays;
    arrays->aryint=nt=new int[size];
    arrays->aryflt=flt=new float[size];
    arrays->arychr=chr=new char[size];
    arrays->aryshrt=shrt=new short[size];
    arrays->arylong=lng=new long[size];
    arrays->arydbl=dlbl=new double[size];
    arrays->aryuint=unt=new unsigned int[size];
    arrays->aryuchr=uchr=new unsigned char[size];
    arrays->aryulng=ulng=new unsigned long[size];
    arrays->aryushr=ushrt=new unsigned short[size];
    arrays->arylgdb=lngdbl=new long double[size];
    arrays->arylnglg=lnglng=new long long[size];
    arrays->ulnglng=ulnglng=new unsigned long long[size];
    arrays->size=size;
    return arrays;
}
void factorial(aray *arrays,int val){
    if(val==0){
        arrays->ulnglng[val]=val+1;
        arrays->arychr[val]=val+1;
        arrays->arydbl[val]=val+1;
        arrays->aryflt[val]=val+1;
        arrays->aryint[val]=val+1;
        arrays->arylgdb[val]=val+1;
        arrays->arylnglg[val]=val+1;
        arrays->arylong[val]=val+1;
        arrays->aryshrt[val]=val+1;
        arrays->aryuchr[val]=val+1;
        arrays->aryuint[val]=val+1;
        arrays->aryulng[val]=val+1;
        arrays->aryushr[val]=val+1;
    }
    else {
        arrays->ulnglng[val]=arrays->ulnglng[val-1]*(val+1);
        arrays->arychr[val]=arrays->arychr[val-1]*(val+1);
        arrays->arydbl[val]=arrays->arydbl[val-1]*(val+1);
        arrays->aryflt[val]=arrays->aryflt[val-1]*(val+1);
        arrays->aryint[val]=arrays->aryint[val-1]*(val+1);
        arrays->arylgdb[val]=arrays->arylgdb[val-1]*(val+1);
        arrays->arylnglg[val]=arrays->arylnglg[val-1]*(val+1);
        arrays->arylong[val]=arrays->arylong[val-1]*(val+1);
        arrays->aryshrt[val]=arrays->aryshrt[val-1]*(val+1);
        arrays->aryuchr[val]=arrays->aryuchr[val-1]*(val+1);
        arrays->aryuint[val]=arrays->aryuint[val-1]*(val+1);
        arrays->aryulng[val]=arrays->aryulng[val-1]*(val+1);
        arrays->aryushr[val]=arrays->aryushr[val-1]*(val+1);
    }
}
void posible(aray *info){
    for(int i=0;i<info->size;i++){
        factorial(info,i);
    }
}
void print(int *max){
    cout<<"the biggest factorial of unsigned long long is = "<<max[0]<<endl;
    cout<<"the biggest factorial of char  is = "<<max[1]<<endl;
    cout<<"the biggest factorial of double is = "<<max[2]<<endl;
    cout<<"the biggest factorial of float is = "<<max[3]<<endl;
    cout<<"the biggest factorial of int is = "<<max[4]<<endl;
    cout<<"the biggest factorial of long double is = "<<max[5]<<endl;
    cout<<"the biggest factorial of long long is = "<<max[6]<<endl;
    cout<<"the biggest factorial of long is = "<<max[7]<<endl;
    cout<<"the biggest factorial of short is = "<<max[8]<<endl;
    cout<<"the biggest factorial of unsigned char is = "<<max[9]<<endl;
    cout<<"the biggest factorial of unsigned int is = "<<max[10]<<endl;
    cout<<"the biggest factorial of unsigned long is = "<<max[11]<<endl;
    cout<<"the biggest factorial of unsigned short is = "<<max[12]<<endl;
    
}
int *big(aray* arrays){
    int nVrbls=13;
    int *max=new int[nVrbls];
    for(int val=1;val<arrays->size;val++){
        if(arrays->ulnglng[val]==arrays->ulnglng[val-1]*(val+1))max[0]=val+1;
        else val=arrays->size;
    }
    for(int val=1;val<arrays->size;val++){
        if(arrays->arychr[val]==arrays->arychr[val-1]*(val+1))max[1]=val+1;
        else val=arrays->size;
    }
    for(int val=1;val<arrays->size;val++){
        if(arrays->arydbl[val]==arrays->arydbl[val-1]*(val+1))max[2]=val+1;
        else val=arrays->size;
    }
    for(int val=1;val<arrays->size;val++){
        if(arrays->aryflt[val]==arrays->aryflt[val-1]*(val+1))max[3]=val+1;
        else val=arrays->size;
    }
    for(int val=1;val<arrays->size;val++){
        if(arrays->aryint[val]==arrays->aryint[val-1]*(val+1))max[4]=val+1;
        else val=arrays->size;
    }
    for(int val=1;val<arrays->size;val++){
        if(arrays->arylgdb[val]==arrays->arylgdb[val-1]*(val+1))max[5]=val+1;
        else val=arrays->size;
    }
    for(int val=1;val<arrays->size;val++){
        if(arrays->arylnglg[val]==arrays->arylnglg[val-1]*(val+1))max[6]=val+1;
        else val=arrays->size;
    }
    for(int val=1;val<arrays->size;val++){
        if(arrays->arylong[val]==arrays->arylong[val-1]*(val+1))max[7]=val+1;
        else val=arrays->size;
    }
    for(int val=1;val<arrays->size;val++){
        if(arrays->aryshrt[val]==arrays->aryshrt[val-1]*(val+1))max[8]=val+1;
        else val=arrays->size;
    }
    for(int val=1;val<arrays->size;val++){
        if(arrays->aryuchr[val]==arrays->aryuchr[val-1]*(val+1))max[9]=val+1;
        else val=arrays->size;
    }
    for(int val=1;val<arrays->size;val++){
        if(arrays->aryuint[val]==arrays->aryuint[val-1]*(val+1))max[10]=val+1;
        else val=arrays->size;
    }
    for(int val=1;val<arrays->size;val++){
        if(arrays->aryulng[val]==arrays->aryulng[val-1]*(val+1))max[11]=val+1;
        else val=arrays->size;
    }
    for(int val=1;val<arrays->size;val++){
        if(arrays->aryushr[val]==arrays->aryushr[val-1]*(val+1))max[12]=val+1;
        else val=arrays->size;
    }
    return max;
}
void destroy(aray *info){
    delete []info->arychr;
    delete []info->arydbl;
    delete []info->aryflt;
    delete []info->aryint;
    delete []info->arylgdb;
    delete []info->arylnglg;
    delete []info->arylong;
    delete []info->aryshrt;
    delete []info->aryuchr;
    delete []info->aryuint;
    delete []info->aryulng;
    delete []info->aryushr;
    delete []info->ulnglng;    
}