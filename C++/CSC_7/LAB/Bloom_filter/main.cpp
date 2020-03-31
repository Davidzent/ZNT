/*
 * File:   main.cpp
 * Author: David  Guijosa
 *
 * Created on October 29, 2019, 9:36 AM
 */

//System Libraries
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
//user libraries
#include "NODE.h"
//Functions
typedef unsigned int (*HashFunction)(const string&);

unsigned int RSHash  (const string&);  
unsigned int JSHash  (const string&);
unsigned int PJWHash (const string&);
unsigned int ELFHash (const string&);
unsigned int BKDRHash(const string&);
unsigned int SDBMHash(const string&);
unsigned int DJBHash (const string&);
unsigned int DEKHash (const string&);
unsigned int BPHash  (const string&);
unsigned int FNVHash (const string&);
unsigned int APHash  (const string&);

int main(int argc, char** argv) {
    //declare variables
    const int SIZE=10;
    const char name[20]="ToHash.txt";
    ifstream file;
    string s;
    Node<string> **data;
    data=new Node<string>*[SIZE];
    bool insert=true;
    int hash;
    //Fill the string to hash
    file.open(name);
    int i=1;
    while(file>>s){
        hash=RSHash(s)%SIZE;
        if(data[hash]==NULL)data[hash]=new Node<string>(s);
        else if(!data[hash]->duplict(s))data[hash]->push_back(s);
        hash=JSHash(s)%SIZE;
        if(data[hash]==NULL)data[hash]=new Node<string>(s);
        else if(!data[hash]->duplict(s))data[hash]->push_back(s);
    }
    file.close();
    //output the spots that are filled
    for(int i=0;i<SIZE;i++){
        if(data[i]!=NULL)cout<<"1 ";
        else cout<<"0 ";
    }
    cout<<endl;
    for(int i=0;i<SIZE;i++)cout<<i+1<<" : "<<data[i];
    //clean memory
    delete data;
    return 0;
}

unsigned int RSHash(const string& str){
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;

   for(size_t i=0;i<str.length();i++){
      hash=hash*a+str[i];
      a=a*b;
   }
   return hash;
}

unsigned int JSHash(const string& str){
   unsigned int hash = 1315423911;
   for(size_t i = 0; i < str.length(); i++){
      hash^=((hash << 5)+str[i]+(hash>>2));
   }
   return hash;
}

unsigned int PJWHash(const string& str){
   unsigned int BitsInUnsignedInt=(unsigned int)(sizeof(unsigned int)*8);
   unsigned int ThreeQuarters=(unsigned int)((BitsInUnsignedInt*3)/4);
   unsigned int OneEighth=(unsigned int)(BitsInUnsignedInt/8);
   unsigned int HighBits=(unsigned int)(0xFFFFFFFF)<<(BitsInUnsignedInt-OneEighth);
   unsigned int hash=0;
   unsigned int test=0;
   for(size_t i=0;i<str.length();i++){
      hash=(hash<<OneEighth)+str[i];
      if((test=hash&HighBits)!= 0){
         hash=((hash^(test>>ThreeQuarters))&(~HighBits));
      }
   }
   return hash;
}

unsigned int ELFHash(const string& str){
   unsigned int hash=0;
   unsigned int x=0;
   for(size_t i=0;i<str.length();i++){
      hash=(hash<<4)+str[i];
      if((x=hash&0xF0000000L)!=0){
         hash^=(x>>24);
      }
      hash&=~x;
   }
   return hash;
}

unsigned int BKDRHash(const string&str){
   unsigned int seed=131; // 31 131 1313 13131 131313 etc..
   unsigned int hash=0;
   for(size_t i = 0; i < str.length(); i++){
      hash=(hash*seed)+str[i];
   }
   return hash;
}

unsigned int SDBMHash(const string& str){
   unsigned int hash = 0;
   for(size_t i=0;i<str.length();i++){
      hash=str[i]+(hash<<6)+(hash<<16)-hash;
   }
   return hash;
}

unsigned int DJBHash(const string& str){
   unsigned int hash=5381;
   for(size_t i=0;i<str.length();i++){
      hash=((hash<<5)+hash)+str[i];
   }
   return hash;
}

unsigned int DEKHash(const string& str){
   unsigned int hash=static_cast<unsigned int>(str.length());
   for(size_t i=0;i<str.length();i++){
      hash=((hash<<5)^(hash>>27))^str[i];
   }
   return hash;
}

unsigned int BPHash(const string& str){
   unsigned int hash=0;
   for(size_t i=0;i<str.length();i++){
      hash=hash<<7^str[i];
   }
   return hash;
}

unsigned int FNVHash(const string& str){
   const unsigned int fnv_prime=0x811C9DC5;
   unsigned int hash=0;
   for(size_t i=0;i<str.length();i++){
      hash*=fnv_prime;
      hash^=str[i];
   }
   return hash;
}

unsigned int APHash(const string& str){
   unsigned int hash=0xAAAAAAAA;
   for(size_t i=0;i<str.length();i++){
      hash^=((i & 1)==0)?((hash<<7)^str[i]*(hash>>3)):
                               (~((hash << 11) + (str[i] ^ (hash >> 5))));
   }
   return hash;
}