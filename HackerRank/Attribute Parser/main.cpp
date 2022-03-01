#include <vector>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void inputvec(vector <string>&,unsigned long&);
void printvec(vector <string>&,unsigned long&);
string gettags (vector <string>&,string,unsigned long&);
string getval(vector<string> &, vector <string>,unsigned long&,int,int);

ifstream in("input.txt");
int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    unsigned long codesize;
    unsigned long searchsz;
    vector <string> code;
    vector <string> search;
    string temp="here";

    in>>codesize>>searchsz;
    getline(in,temp);
    inputvec(code,codesize);
    inputvec(search,searchsz);
    
    for(int i=0;i<searchsz;i++){
        cout<<gettags(code,search[i],codesize)<<endl;
    }
    return 0;
}


string gettags (vector<string> &data,string search,unsigned long& datasz){
    vector <string> branch;
    string temp;
    size_t start=0;
    size_t end=0;
    size_t sz=search.size();
    
    while(start<sz){
        end = search.find(".",start);
        if(end==string::npos){
            end = search.find("~",start);
            if(end==string::npos){
                end=sz-1;
            }
        }
        temp = search.substr(start, (end-start));
        branch.push_back(temp);
        start = end+1;
    }
    unsigned long temp2=branch.size();
    temp = getval(data,branch,datasz,0,0);
    
    return temp;      
}

string getval(vector<string> &data, vector <string> branch,unsigned long& datasz,int check,int start){
    if(check==branch.size()-1){
        start--;
        size_t pos = data[start].find((" "+branch[check]+" "),0);
        if(pos==string::npos)return "Not Found!";
        pos=data[start].find("\"",pos)+1;
        size_t endpos = data[start].find("\"",pos);
        return data[start].substr(pos, (endpos-pos));
        
    }
    int cnt=0;
    for(int i=start;i<datasz;i++){
        if(data[i].find(("<"+branch[check]))!=string::npos&&cnt==0){
            return getval(data,branch,datasz,check+1,i+1);
        }
        else if(data[i].find(("</"+branch[check]))!=string::npos){
            return "Not Found!";
        }
        else if(data[i].find("</")) cnt--;
        else cnt++;
    }
    return "Not Found!";
}

void inputvec(vector <string> &vec,unsigned long &size){
    string temp;
    for(unsigned long i=0;i<size;i++){
        getline(in,temp);
        vec.push_back(temp);
    }
}
void printvec(vector <string> &vec,unsigned long &size){
    for(unsigned long i=0;i<size;i++){
        cout<<vec[i]<<endl;
    }
}

