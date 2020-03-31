/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Merkle_tree.h
 * Author: david
 *
 * Created on December 6, 2019, 7:00 PM
 */


#ifndef MERKLE_TREE_H
#define MERKLE_TREE_H

#include <fstream>
#include <iostream>
using namespace std;

class Merkle{
    private:
        string data;             //base root
        Merkle *Sroot;      //hash root
        Merkle *Broot;      //hash root
    public:
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
        int height(Merkle *);         //Merkle height
        int diff(Merkle *);       //Difference of right/left subtrees
        Merkle *gtSRoot(){return Sroot;}
        Merkle *gtBRoot(){return Broot;}
        string   gtData(){return data;} 
        void display(Merkle *, int);       //Funky display root left to right
        Merkle(){Sroot = NULL; Broot=NULL;}
        Merkle(const char[]);                              //Constructor   
        ~Merkle(){delete Sroot;delete Broot;}
};
//                              Constructor

Merkle::Merkle(const char name[]){
    int h;
    fstream file;
    file.open(name);
    file>>h;
    string s[h];
    int n=1;
    while(n<h)n*=2;
    n--;
    string temp[h+n];
    int temp2=0;
    for( std::string line; getline( file, line ); ){
        if(temp2!=0){
        temp[(temp2++)-1]=to_string(RSHash(line));
        }
        else temp2++;
    }
    file.close();
    temp2--;
    for(int x=0;x<2;x++){
        for(int j=0+(x*2);j<2+(x*2);j++){
            for(int i=0;i<(temp[j].size()/2);i++){
                temp[temp2]+=temp[j][i];
            }
        }
        temp2++;
    }
    for(int j=0;j<h;j++){
        for(int i=0;i<(temp[j].size()/h);i++){
            temp[temp2]+=temp[j][i];
        }
    }
    //*************************************************************************
    //To Be Worked
    data=temp[n+3];
    Sroot=new Merkle;
    Sroot->data=temp[n+1];
    Sroot->Sroot=new Merkle;
    Sroot->Sroot->data=temp[0];
    Sroot->Broot=new Merkle;
    Sroot->Broot->data=temp[1];
    Broot=new Merkle;
    Broot->data=temp[n+1];
    Broot->Sroot=new Merkle;
    Broot->Sroot->data=temp[0];
    Broot->Broot=new Merkle;
    Broot->Broot->data=temp[1];
    //*************************************************************************
}

//                            Height of Merkles


int Merkle::height(Merkle *temp){
    int h = 0;
    if (temp != NULL){
        int l_height = height (temp->Sroot);
        int r_height = height (temp->Broot);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}

//                      Height Difference of AVL Sub Merkles

int Merkle::diff(Merkle *temp){
    int l_height = height (temp->Sroot);
    int r_height = height (temp->Broot);
    int b_factor= l_height - r_height;
    return b_factor;
}

//                         Display all Sub Merkles

void Merkle::display(Merkle *ptr,int level){
    if (ptr!=NULL){
        display(ptr->Broot, level + 1);
        cout<<endl;
        if (ptr == this)
        cout<<"R -> ";
        for(int i=0;i<level&&ptr!=this;i++)
            cout<<"     ";
        cout<<ptr->data;
        display(ptr->Sroot, level + 1);
    }
}
//*****************************************************************************
//*                              Hashes                                       *
//*****************************************************************************

unsigned int Merkle::RSHash(const string& str){
   unsigned int b    = 378551;
   unsigned int a    = 63689;
   unsigned int hash = 0;

   for(size_t i=0;i<str.length();i++){
      hash=hash*a+str[i];
      a=a*b;
   }
   return hash;
}


unsigned int Merkle::JSHash(const string& str){
   unsigned int hash = 1315423911;
   for(size_t i = 0; i < str.length(); i++){
      hash^=((hash << 5)+str[i]+(hash>>2));
   }
   return hash;
}


unsigned int Merkle::PJWHash(const string& str){
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


unsigned int Merkle::ELFHash(const string& str){
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


unsigned int Merkle::BKDRHash(const string&str){
   unsigned int seed=131; // 31 131 1313 13131 131313 etc..
   unsigned int hash=0;
   for(size_t i = 0; i < str.length(); i++){
      hash=(hash*seed)+str[i];
   }
   return hash;
}


unsigned int Merkle::SDBMHash(const string& str){
   unsigned int hash = 0;
   for(size_t i=0;i<str.length();i++){
      hash=str[i]+(hash<<6)+(hash<<16)-hash;
   }
   return hash;
}


unsigned int Merkle::DJBHash(const string& str){
   unsigned int hash=5381;
   for(size_t i=0;i<str.length();i++){
      hash=((hash<<5)+hash)+str[i];
   }
   return hash;
}


unsigned int Merkle::DEKHash(const string& str){
   unsigned int hash=static_cast<unsigned int>(str.length());
   for(size_t i=0;i<str.length();i++){
      hash=((hash<<5)^(hash>>27))^str[i];
   }
   return hash;
}


unsigned int Merkle::BPHash(const string& str){
   unsigned int hash=0;
   for(size_t i=0;i<str.length();i++){
      hash=hash<<7^str[i];
   }
   return hash;
}

unsigned int Merkle::FNVHash(const string& str){
   const unsigned int fnv_prime=0x811C9DC5;
   unsigned int hash=0;
   for(size_t i=0;i<str.length();i++){
      hash*=fnv_prime;
      hash^=str[i];
   }
   return hash;
}

unsigned int Merkle::APHash(const string& str){
   unsigned int hash=0xAAAAAAAA;
   for(size_t i=0;i<str.length();i++){
      hash^=((i & 1)==0)?((hash<<7)^str[i]*(hash>>3)):
                               (~((hash << 11) + (str[i] ^ (hash >> 5))));
   }
   return hash;
}

#endif /* MERKLE_TREE_H */

