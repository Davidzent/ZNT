#include "AI_SNS.h"
void AISNS::play(){
    
    int n4=0,n3=0,n2=0,n1=0,n0=0;
    char inpt;
    cout<<"Do you want to input an answer to find?(Y/N)\n";
    cin>>inpt;
    if(inpt=='y'||inpt=='Y'){
        cout<<"Input the answer you want to test for\n"<<"It will only take the first "<<CodeSz<<" Numbers"<<endl;
        char s[CodeSz];
        cin>>s;
        instans(s);
    }
    else crtans();
     file<<"Code\tGuess\t#Right\tRight in wrong spot\tsum"<<endl;
    while(nInput<atempts){
        //cout<<"Attempt number   : "<<nInput+1<<endl;
        crtinpt();
        //cout<<psbltr<<endl;
        //for(int i=0;i<nLetter;i++)if(stats[i]!=0)cout<<letters[i];
        //for(int i=0;i<CodeSz;i++)file<<Plyinpt[nInput][i];
        //file<<endl;
        chkinpt();
        nInput++;
    }
    
    for(int i=0;i<nInput;i++){
        int sum=nCorrct[i]+nPerfc[i];
        switch (sum){
            case 1:n1++;break;
            case 2:n2++;break;
            case 3:n3++;break;
            case 4:n4++;break;
            case 0:n0++;break;
        }
    }
    file.close();
    file.open("Correct inputs.txt");
    file<<"\nYou get the sum = 4 correct letters :"<<n4<<" Times"<<endl;
    file<<"You get the sum = 3 correct letters :"<<n3<<" Times"<<endl;
    file<<"You get the sum = 2 correct letters :"<<n2<<" Times"<<endl;
    file<<"You get the sum = 1 correct letters :"<<n1<<" Times"<<endl;
    file<<"You get the sum = 0 correct letters :"<<n0<<" Times"<<endl;
    file<<"Total :"<<n0+n1+n2+n3+n4<<" Times"<<endl;
    n4=0;n3=0;n2=0;n1=0;n0=0;
    for(int i=0;i<nInput;i++){
        int sum=nCorrct[i];
        switch (sum){
            case 1:n1++;break;
            case 2:n2++;break;
            case 3:n3++;break;
            case 4:n4++;break;
            case 0:n0++;break;
        }
    }
    file<<"\nYou get "<<n4<<" time/s the correct but in the wrong spot = 4 \n";
    file<<"You get "<<n3<<" time/s the correct but in the wrong spot = 3 \n";
    file<<"You get "<<n2<<" time/s the correct but in the wrong spot = 2 \n";
    file<<"You get "<<n1<<" time/s the correct but in the wrong spot = 1 \n";
    file<<"You get "<<n0<<" time/s the correct but in the wrong spot = 0 \n";
    file<<"Total :"<<n0+n1+n2+n3+n4<<" Times"<<endl;
    n4=0;n3=0;n2=0;n1=0;n0=0;
    for(int i=0;i<nInput;i++){
        int sum=nPerfc[i];
        switch (sum){
            case 1:n1++;break;
            case 2:n2++;break;
            case 3:n3++;break;
            case 4:n4++;break;
            case 0:n0++;break;
        }
    }
    file<<"\nYou get "<<n4<<" time/s the correct and in the correct spot = 4 \n";
    file<<"You get "<<n3<<" time/s the correct and in the correct spot = 3 \n";
    file<<"You get "<<n2<<" time/s the correct and in the correct spot = 2 \n";
    file<<"You get "<<n1<<" time/s the correct and in the correct spot = 1 \n";
    file<<"You get "<<n0<<" time/s the correct and in the correct spot = 0 \n";
    file<<"Total :"<<n0+n1+n2+n3+n4<<" Times"<<endl;
}
char* AISNS::ctNinpt(const int N){
    char *temp=new char[CodeSz];
    static int k=-1,j=0,x=0,n=0;
    for(int i=0;i<CodeSz;i++){
        switch(i){
            case 3:n==nLetter?n=0:n;temp[0]='0'+n;break;
            case 2:x==nLetter?x=0,n++:x;temp[1]='0'+x;break;
            case 1:j==nLetter?j=0,x++:j;temp[2]='0'+j;break;
            case 0:k==nLetter-1?k=0,j++:k++;temp[3]='0'+k;break;
        }    
    }
    return temp;
}
char *AISNS::ctRinpt(){
    char *temp=new char[CodeSz];
    if(nInput==0){
        for(int i=0;i<CodeSz;i++){
            temp[i]=rand()%nLetter+65;
        }
    }
    else {
        int pos;
        do{
            for(int i=0;i<CodeSz;i++){  
                if(!duplict){
                    do{
                        do{
                            pos=rand()%nLetter;
                        }while(stats[pos]==0);
                        temp[i]=letters[pos];                
                    }while(chkdupl(temp,i));
                }
                else{
                    do{
                            pos=rand()%nLetter;
                        }while(stats[pos]==0);
                     temp[i]=letters[pos];
                }           
            }
        }while(ckntuniq(temp));
    }
    return temp;
}
void AISNS::crtinpt(){
    //if(nInput>0)chkprev();
    Plyinpt[nInput]=ctNinpt(1);
    //else Plyinpt[nInput]=ctRinpt();
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
void AISNS::chkprev(){
    static bool posible=false;
    int n=nInput-1;
    int dif=nDifer(n);
    if(!duplict&&dif==CodeSz){
        for(int i=0;i<CodeSz;i++){
            Plyinpt[n][i];
        }
    }
    if(nCorrct[n]==0){
        for(int i=0;i<CodeSz;i++){
            psltter(Plyinpt[n][i]);
        }
    }
    if(nCorrct[n]==CodeSz&&!posible){
            kpcorct(Plyinpt[n]);
            posible=true;
    }
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
        if(cnt==CodeSz)return true;     //return true if it is not unique
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
    stats=new int [nLetter];
    for(int i=0;i<nLetter;i++)stats[i]=(CodeSz*100)/nLetter;
    psbltr=nLetter;
}