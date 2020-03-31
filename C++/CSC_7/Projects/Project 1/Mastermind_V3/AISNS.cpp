#include "AI_SNS.h"
void AISNS::play(){
    crtans();
    while(status){
        cout<<"Attempt number   : "<<nInput+1<<endl;
        crtRinpt();
        cout<<psbltr<<endl;
        for(int i=0;i<psbltr;i++){
            cout<<letters[i];
        }    
        cout<<"\nEnter your guess : "<<Plyinpt[nInput]<<endl;
        chcinpt();
        nInput++;
    }
    /*cout<<"inputs\n";
    for(int i=0;i<nInput;i++){
        cout<<Plyinpt[i]<<endl;
    }*/
}
void AISNS::crtRinpt(){
    static bool posible=false;
    if(nInput==0){
        for(int i=0;i<CodeSz;i++){
            Plyinpt[nInput][i]=rand()%nLetter+65;
        }
    }
    else {
        int pos;
        if(nCorrct==0){
            for(int i=0;i<CodeSz;i++){
                psltter(Plyinpt[nInput-1][i]);
            }
        }
        if(nCorrct==CodeSz&&!posible){
            kpcorct(Plyinpt[nInput-1]);
            posible=true;
        }
        do{
            //cout<<"atempting "<<endl;
            for(int i=0;i<CodeSz;i++){  
                if(!duplict){
                    do{
                        //cout<<"creating "<<endl;
                        pos=rand()%psbltr;
                        Plyinpt[nInput][i]=letters[pos];
                        psleter[pos]++;                   
                    }while(chkdupl(Plyinpt[nInput],i));
                }
                else{
                     pos=rand()%psbltr;
                     Plyinpt[nInput][i]=letters[pos];
                     psleter[pos]++;
                }           
                if(psleter[pos]==CodeSz){              
                }
            }
        }while(ckntuniq(Plyinpt[nInput]));
    }
}
void AISNS::kpcorct(const char *correct){
    char temp;
    int cnt=0;
    delete letters;
    letters = new char[CodeSz];
    for(int i=0;i<CodeSz;i++){
        temp=correct[i];
        if(!checknt(temp))letters[i-cnt]=temp;
        else cnt++;
    }
    psbltr=CodeSz-cnt;
}
bool AISNS::ckntuniq(const char *input){
    //cout<<"Checking if it is unique"<<endl;
    int cnt;
    for(int i=0;i<nInput;i++){
        //cout<<input<<" =? "<<Plyinpt[i]<<endl;
        cnt=0;
        for(int j=0;j<CodeSz;j++){
            if(input[j]==Plyinpt[i][j])cnt++;
        }
        if(cnt==CodeSz)return true;
    }
    return false;
}
bool AISNS::checknt(const char lett){
    for(int i=0;i<psbltr;i++){
        if(lett==letters[i])return true;
    }
    return false;
}
void AISNS::psltter(const char lettr){
    if(checknt(lettr)){
        char *temp=new char[psbltr-1];
        int cnt=0;
        for(int i=0;i<psbltr;i++){
            char templt=letters[i];
            if(lettr!=templt)temp[i-cnt]=templt;
            else cnt++;
        }
        delete letters;
        letters=temp;
        psbltr--;
    }
}
AISNS::~AISNS(){
    delete pnts;
    delete psleter;
}
void AISNS::start(){
    psleter=new int [nLetter];
    pnts=new int [atempts];
    psbltr=nLetter;
}