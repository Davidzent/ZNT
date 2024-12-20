/* 
 * File:   main.cpp
 * Author: David Guijosa
 * Purpose:
 * Created on September 14, 2019, 11:55 AM
 */

#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

//Functions
bool* AND(bool[],bool[],const int);
bool* OR(bool[],bool[],const int);
bool* NOT(bool[],const int);
bool* XOR(bool[],bool[],const int);
bool* XOR2(bool[],bool[],const int);
void prntbol(bool[],const int);
int main(int argc, char** argv) {
    //declare variables
    const int size=4;    
    bool p[4]={true,true,false,false};      //P = T T F F
    bool q[4]={true,false,true,false};      //Q = T F T F
    bool* PandQ=AND(p,q,size);
    bool* NPandQ=NOT(PandQ,size);
    bool* PorQ=OR(p,q,size);
    bool* NotPorQ=NOT(PorQ,size);
    bool* NotP=NOT(p,size);
    bool* NotQ=NOT(q,size);
    bool* PXORQ=XOR(p,q,size);
    bool* PQrNPrQ=OR(PandQ,NotPorQ,size);
    bool* PrQnNPQ=AND(PorQ,NPandQ,size);
    //output/display
    cout<<"~p              = ";     //Not P
    prntbol(NotP,size);
    cout<<"~q              = ";     //Not Q
    prntbol(NotQ,size);
    cout<<"p               = ";     //P
    prntbol(p,size);
    cout<<"q               = ";     //Q
    prntbol(q,size);
    cout<<"p&&q            = ";     //P and Q
    prntbol(PandQ,size);
    cout<<"p||q            = ";     //P or Q
    prntbol(PorQ,size);
    cout<<"p^q             = ";     //P XOR Q
    prntbol(PXORQ,size);
    cout<<"p^q             = ";     //P XOR Q
    prntbol(XOR2(p,q,size),size);
    cout<<"(p&&q)||~(p||q) = ";     //(P and Q) or Not (P or Q)
    prntbol(PQrNPrQ,size);
    cout<<"(p||q)&&~(p&&q) = ";     //(P or Q) and Not(P and Q)
    prntbol(PrQnNPQ,size);
    //exit
    delete PandQ;
    delete PorQ;
    delete NPandQ;
    delete PrQnNPQ;
    delete NotPorQ;
    delete NotP;
    delete NotQ;
    delete PXORQ;
    delete PQrNPrQ;

    return 0;
}
bool* AND(bool one[],bool two[],const int size){
    bool* Oneand2;
    Oneand2=new bool[size];
    for(int i=0;i<size;i++){
        if(one[i]&&two[i])Oneand2[i]=true;
        else Oneand2[i]=false;
    }
    return Oneand2;
}
bool* OR(bool one[],bool two[],const int size){
    bool* Oneor2;
    Oneor2=new bool[size];
    for(int i=0;i<size;i++){
        if(one[i]||two[i])Oneor2[i]=true;
        else Oneor2[i]=false;
    }
    return Oneor2;
}
bool* NOT(bool one[],const int size){
    bool* Not;
    Not=new bool[size];
    for(int i=0;i<size;i++){
        Not[i]=!one[i];
    }
    return Not;
}
bool* XOR(bool one[],bool two[],const int size){
    bool* OneXor2;
    OneXor2=new bool[size];
    for(int i=0;i<size;i++){
        if(one[i]||two[i])
            if(!one[i]&&two[i]||one[i]&&!two[i])OneXor2[i]=true;
        else OneXor2[i]=false;
    }
    return OneXor2;
}
bool* XOR2(bool one[],bool two[],const int size){
    bool* OneXor2;
    OneXor2=new bool[size];
    for(int i=0;i<size;i++){
        OneXor2[i]=one[i]^two[i];
    }
    return OneXor2;
}
void prntbol(bool one[],const int size){
    for(int i=0;i<size;i++){
        cout<<(one[i]?"T ":"F ");
    }
    cout<<endl;
}