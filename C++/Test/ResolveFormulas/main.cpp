/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on September 24, 2020, 1:55 PM
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <valarray>
#include "Formula.h"
using namespace std;

/*
 * 
 */

vector<string> solve(vector<string>,int,int);
string rvStr(string,int);
int endofP(string,int);
Formula crt(string,string);
void prntF(Formula);
//A+B+C*(D*E+F*(G*H*+X(A*B*D)-F+A)+I)+A-F=0


int main(int argc, char** argv) {
    Formula f;
    ifstream in;
    in.open("formulas.txt");
    string formula;
    string knows;
    string equal;
    string val;
    cout<<"Getting The formulas from the file formulas.txt"<<endl;
    getline(in,formula);
    cout<<"Input The Known Values from the file Values.txt"<<endl;

    string delimiter = "=";
    equal = formula.substr(0, formula.find(delimiter));
    val = formula.substr(formula.find(delimiter)+1,formula.size());
    f=crt(equal,val);
    prntF(f);
    //cout<<f.Equal<<" = "<<f.Values<<endl;
    //cout<<solve(f.Equal,0,f.Equal.size())<<"\n\n";
    in.close();
    return 0;
}
vector<string> solve(string str,int beg,int end){
    static int M=0;
    string SADMEP = "-+/*^(";
    string f="";
    for(int i=beg;i<end;i++){
        f+=str[i];
    }
    while(f.find('(')!=string::npos){
    for(int i=0;i<SADMEP.size();i++){
            //for(int j=beg;j<end;j++){
        if(SADMEP[i]=='*'&&f.find(SADMEP[i])!=string::npos){
            f.erase(std::remove(f.begin(), f.end(), '*'), f.end());
        }
        if(SADMEP[i]=='('&&f.find(SADMEP[i])!=string::npos){
            int beg2 = f.find('(');
            int end2 = endofP(f,beg2+1);
            string st="";
            string s="";
            bool inside=true;
            while(f[end2+1]=='('){
                cout<<f<<endl;
                st="";
                s="";
                int chc=0;
                int end3 = endofP(f,end2+2);
                for(int x=end2+1;x<=end3;x++){
                    s+=f[x];
                }
                //cout<<s<<endl;
                f.erase(end2,end3-end2);
                //cout<<f[beg2+1]<<" "<<f[end2-1]<<endl;
                inside = true;
                for(int x=beg2+1;x<end2;x++){
                    if(f[x]=='(')inside=false;
                    else if(f[x]==')')inside=true;
                    if(f[x]=='+'&&inside){
                        chc+=s.size();
                        st="";
                        st+="+";
                        for(int j=0;j<s.size();j++)st+=s[j];
                        cout<<st<<endl;
                        cout<<f<<endl;
                        f.replace(x,1,st);
                        cout<<f<<endl;
                        cout<<x<<endl;
                        x+=st.size()-2;
                        cout<<x<<endl;
                        beg2 = f.find('(');
                        end2 = endofP(f,beg2+1);
                        
                    }
                    else if(f[x]=='-'&&inside){
                        chc+=s.size();
                        st="";
                        st+="-";
                        for(int j=0;j<s.size();j++)st+=s[j];
                        f.replace(x,1,st);
                        x+=st.size()-2;
                        beg2 = f.find('(');
                        end2 = endofP(f,beg2+1);
                    }
                }
                beg2 = f.find('(',beg2);
                end2 = endofP(f,beg2+1);
            }
            
            //LEL
            cout<<"out"<<endl;
            //cout<<f<<endl;
            beg2 = f.find('(');
            end2 = endofP(f,beg2+1);
            size_t pos=f.find_first_of(SADMEP,end2);
            while(pos!=end2+1&&pos!=string::npos){
                string temp="";
                for(int x=pos-1;x>=beg2&&x>=0;x--){
                    temp+=f[x];
                    
                }
                
                for(int x=beg2;x<pos&&x<f.size();x++){
                    if(temp[x-beg2]=='(')f[x]=')';
                    else if(temp[x-beg2]==')')f[x]='(';
                    else f[x]=temp[x-beg2];
                }
                beg2 = f.find('(',end2);
                if(beg2!=-1){
                    end2 = endofP(f,beg2+1);
                    pos=f.find_first_of(SADMEP,end2);
                    if(pos==string::npos)pos=f.size();
                }else{
                    pos=string::npos;
                }
                
            }
            beg2 = f.find('(');
            end2 = endofP(f,beg2+1);
            s=rvStr(f,beg2);
            pos=s.find_first_of(SADMEP);
            //f.replace(beg2+1,end2-beg2-1,solve(f, beg2+1, end2));
            if(pos!=string::npos){
                //cout<<"StartIf"<<endl;
                string st="";
                //cout<<"Start"<<endl;
                beg2 = f.find('(');
                end2 = endofP(f,end2);
                //cout<<beg2<<" "<<end2<<endl;
                for(int x=beg2+1;x<=end2;x++){
                    if(f[x]=='+'){
                        st="";
                        st+='+';
                        for(int j=pos-1;j>=0;j--)st+=s[j];
                        f.replace(x,1,st);
                        x+=s.size();
                        end2 = endofP(f,beg2+1);
                    }
                    else if(f[x]=='-'){
                        st="";
                        st+=f[x];
                        for(int j=pos-1;j>=0;j--)st+=s[j];
                        f.replace(x,1,st);
                        x+=s.size();
                        end2 = endofP(f,beg2+1);
                    }
                }
                
                //cout<<f<<endl;
                beg2 = f.find('(');
                //cout<<"erasing"<<endl;
                f.erase(beg2,1);
                
                //cout<<"Changing "<<endl;
                
                f.erase(endofP(f,beg2),1);
                
                //cout<<"Done"<<endl;
                //cout<<f<<endl;
                //cout<<"EndIf"<<endl;
            }
            else{
                beg2 = f.find('(');
                f.erase(beg2,1);
                f.erase(endofP(f,beg2),1);
            }
            
        }
    }
    }
    //cout<<f<<endl;
    return f;
}
Formula crt(string equal, string val){
    Formula f;
    f.Equal.n=0;
    f.Values.n=0;
    equal.erase(remove(equal.begin(), equal.end(), ' '), equal.end());
    equal.erase(remove(equal.begin(), equal.end(), '*'), equal.end());
    val.erase(remove(val.begin(), val.end(), ' '), val.end());
    val.erase(remove(val.begin(), val.end(), '*'), val.end());
    int size=count(equal.begin(),equal.end(),'(');
    int err=count(equal.begin(),equal.end(),')');
    if(size!=err)exit(0);
    string temp="";
    
    for(int i=0;i<equal.size();i++){
        if(equal[i]=='('){
            int end=endofP(equal,i);
            temp="";
            if(i-1>=0&&equal[i-1]!=')'&&equal[i-1]!='(')temp+=equal[i-1];
            for(int j=i;j<=end;j++){
                temp+=equal[j];
            }
            f.Equal.var.push_back(temp);
            f.Equal.n++;
        }
    }
    size=count(val.begin(),val.end(),'(');
    err=count(val.begin(),val.end(),')');
    if(size!=err)exit(0);
    for(int i=0;i<val.size();i++){
        if(val[i]=='('){
            int end=endofP(val,i);
            temp="";
            if(i-1>=0&&val[i-1]!=')'&&val[i-1]!='(')temp+=val[i-1];
            for(int j=i;j<=end;j++){
                temp+=val[j];
            }
            f.Values.var.push_back(temp);
            f.Values.n++;
        }
    }
    return f;
}
void prntF(Formula f){
    cout<<"In the equal part: "<<endl;
    for(int i=0;i<f.Equal.n;i++){
        cout<<f.Equal.var[i]<<endl;
    }
    cout<<"In the values part: "<<endl;
    for(int i=0;i<f.Values.n;i++){
        cout<<f.Values.var[i]<<endl;
    }
}

string rvStr(const string str,int end){
    string s="";
    for(int i=end-1;i>=0;i--){
        s+=str[i];
    }
    return s;
} 
int endofP(string f,int end){
    int temp=0;
    do{
        end=f.find_first_of("()",end);
        if(f[end]=='(')temp++;
        else if(f[end]==')')temp--;
        if(temp!=0)end++;
    }while(temp!=0&&end<f.size());
    return end;
}