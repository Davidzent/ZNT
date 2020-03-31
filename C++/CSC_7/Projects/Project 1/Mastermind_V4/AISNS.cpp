#include "AI_SNS.h"
#include <cmath>
void AISNS::play(){
    crtans();
    while(status){
        cout<<"\nAttempt number   : "<<nInput+1<<endl;
        crtinpt();
        cout<<psbltr<<endl;
        for(int i=0;i<nLetter;i++)if(stats[i]!=0)cout<<letters[i];
        cout<<"\nEnter your guess : ";
        for(int i=0;i<CodeSz;i++)cout<<Plyinpt[nInput][i];
        cout<<endl;
        chkinpt();
        nInput++;
    }

}
char* AISNS::ctNinpt(const int N){
    char *temp=new char[CodeSz];
    int n=nInput-1;
    static int cnt=0,cnt2=0,cnt3=0;
    if(cnt>nLetter)cnt=1;
    for(int i=0;i<CodeSz;i++){
        if(i%N==0&&N>1)cnt3=N-1;
        while(stats[cnt]==0){
            cnt++;
            if(cnt>nLetter){
                cnt2=1;
                cnt%=(nLetter+1);
            }
        }
        temp[i]=letters[cnt];
        if(cnt3>0)cnt3--;
        else cnt++;
    }
    if(cnt2==1)cnt=cnt+nLetter*cnt2,cnt2--;
    if(N!=1)cnt+=N-(CodeSz-1);
    else cnt-=(CodeSz-1);
    if(cnt<0)cnt=0;
    return temp;
}

void AISNS::crtinpt(){
    if(nInput==0)Plyinpt[nInput]=ctNinpt(2);
    else{
        chkprev();
        int min;
        for(int i=0;i<row;i++){
            if(!ckntuniq(pslet[i])){
                
            }
        }
    }
    
}
 int AISNS::posibl(char*temp){
    int cnt=0;
    int n=nInput-1;
    for(int i=0;i<CodeSz;i++){
        for(int j=0;j<row;j++){
            if(temp[i]!=pslet[i][j])cnt++;
        }
    }
    return cnt;
 } 

void AISNS::chkprev(){
    int n=nInput-1;
    for(int i=0;i<CodeSz;i++){
        for(int j=0;j<row;j++){
            if(Plyinpt[n][i]!=pslet[i][j]&&pslet[CodeSz][j]!='1')pslet[CodeSz][j]='1';
        }
    }
    
}
int AISNS::nDifer(const int n){
    int cnt=0;
    for(int i=0;i<CodeSz-1;i++){
        for(int j=i+1;j<CodeSz;j++){
            if(Plyinpt[n][i]==Plyinpt[n][j])cnt++;
        }
    }
    return CodeSz-cnt;
}

void AISNS::kpcorct(const char *correct){
    psbltr=0;
    for(int i=0;i<CodeSz;i++){
        for(int j=0;j<nLetter;j++){
            if(letters[j]==correct[i])stats[j]=100,psbltr++;
            if(stats[j]!=100)stats[j]=0;
        }
    }
}
bool AISNS::ckntuniq(const char *input){
    int cnt;
    for(int i=0;i<nInput;i++){
        cnt=0;
        for(int j=0;j<CodeSz;j++){
            if(input[j]==Plyinpt[i][j])cnt++;
        }
        if(cnt==CodeSz)return true;     //return if true if it is not unique
    }
    return false;
}
void AISNS::psltter(const char lettr){
    for(int i=0;i<nLetter;i++){
        if(lettr==letters[i]){
            if(stats[i]!=0)psbltr--,stats[i]=0;
        }
    }
    
}
AISNS::~AISNS(){
    delete stats;
}
void AISNS::start(){
    ofstream file;
    file.open("check.txt");
    stats=new int [nLetter];
    row=pow(nLetter,CodeSz);
    pslet=new char*[row];
    for(int i=0;i<row;i++){
        pslet[i]=new char[CodeSz+1];
    }
    int *cnt=new int[CodeSz];
    for(int i=0;i<CodeSz;i++){
        cnt[i]=0;
    }
    int k=-1,j=0,x=0,n=0;
    for(int j=0;j<row;j++){
        for(int i=0;i<CodeSz;i++){
            if(i==CodeSz)pslet[j][i]='\0';
            switch(i){
                case 3:n==nLetter?n=0:n;pslet[j][0]='A'+n;break;
                case 2:x==nLetter?x=0,n++:x;pslet[j][1]='A'+x;break;
                case 1:j==nLetter?j=0,x++:j;pslet[j][2]='A'+j;break;
                case 0:k==nLetter-1?k=0,j++:k++;pslet[j][3]='A'+k;break;
            }
        }
        file<<pslet[j];
        file<<endl;
    }
    file.close();
    for(int i=0;i<nLetter;i++)stats[i]=(CodeSz*100)/nLetter;
    psbltr=nLetter;
}