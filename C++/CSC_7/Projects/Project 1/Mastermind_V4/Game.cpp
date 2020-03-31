#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <fstream>

Game::Game(int nLetter,int codesz,int atempts,bool duplica){
    this->nLetter=nLetter;
    this->atempts=atempts;
    nInput=0;
    CodeSz=codesz;
    duplict=duplica;
    status=true;
    letters=new char[nLetter];
    Plyinpt=new char*[atempts];
    inptchk=new bool[CodeSz];
    answer=new char[CodeSz];
    nCorrct=new int[atempts];            
    nPerfc=new  int[atempts];
    for(int i=0;i<atempts;i++){
        Plyinpt[i]=new char[CodeSz];
    }
    for(int i=0;i<nLetter;i++){
        letters[i]='A'+i;
    }
}
void Game::crtans(){
    int temp=0;
    for(int i=0;i<CodeSz;i++){
        if(!duplict){
            do{
                temp=rand()%nLetter;
                answer[i]=letters[temp];
            }while(chkdupl(answer,i));}
        else {
            temp=rand()%nLetter;
            answer[i]=letters[temp];
        }
        
    }
}
bool Game::chkdupl(const char*check,const int max){
    for(int i=0;i<max;i++){
        for(int j=i+1;j<max+1;j++){
            if(check[i]==check[j])return true;
        }
    }
    return false;
}
bool Game::chkletr(){
    int cnt=0;
    for(int i=0;i<CodeSz;i++){
        if(Plyinpt[nInput][i]>='a'&&Plyinpt[nInput][i]<='z')Plyinpt[i]-=32;
        if(Plyinpt[nInput][i]>=letters[0]&&Plyinpt[nInput][i]<=letters[nLetter])cnt++;
    }
    if(cnt==CodeSz)return true;
    return false;
}
bool Game::chkletr(char let){
    for(int i=0;i<CodeSz;i++){
        if(let==answer[i])return true;
    }
    return false;
}
void Game::chkinpt(){
    nCorrct[nInput]=0;
    nPerfc[nInput]=0;
    for(int i=0;i<CodeSz;i++){
        inptchk[i]=true;
    }
    int cnt,cnt2,cnt3;
    for(int i=0;i<nLetter;i++){
        if(chkletr(letters[i])){
            cout<<"here "<<letters[i]<<endl;
            cnt=0;
            cnt2=0;
            cnt3=0;
            for(int j=0;j<CodeSz;j++)if(letters[i]==Plyinpt[nInput][j])cnt++;
            for(int j=0;j<CodeSz;j++)if(letters[i]==answer[j])cnt2++;
            for(int j=0;j<CodeSz;j++)if(Plyinpt[nInput][j]==answer[j]&&letters[i]==answer[j]){
                nPerfc[nInput]++,cnt3++;
            }
            cout<<cnt<<" "<<cnt2<<endl;
            cnt-=cnt3;
            cnt2-=cnt3;
            cout<<cnt<<" "<<cnt2<<endl;
            
            if(cnt2>0&&cnt>0){
                for(int k=0;k<CodeSz;k++){
                    for(int j=0;j<CodeSz;j++){
                        if(Plyinpt[nInput][k]==answer[j]&&inptchk[k]&&j!=k&&cnt2>0&&cnt>0)nCorrct[nInput]++,inptchk[j]=false,cnt2--,cnt--;
                    }
                }
            }
        }
    }
    cout<<"answer -> "<<answer<<endl;
    cout<<"You Find "<<nCorrct[nInput]<<" correct letters that are not in the right spot and "
            <<nPerfc[nInput]<<" are in the right spot\n";
    if(nPerfc[nInput]==CodeSz)status=false,cout<<"\nYou Won the Game\n";
    else if(atempts==nInput+1){
            status=false;
            cout<<"\nyou lose the game\n"<<"the correct answer was: "<<answer<<endl;
        }   
}

void Game::play(){
    crtans();
    while(status){
        cout<<"Enter your guess : ";
        do{
            for(int i=0;i<CodeSz;i++){
                cin>>Plyinpt[nInput][i];
            }
            if(!chkletr())cout<<"You enter an invalid input, try again"<<endl;
        }while(!(chkletr()));
        chkinpt();
        nInput++;
    }
}
Game::~Game(){
    for(int i=0;i<atempts;i++){
        delete Plyinpt[i];
    }
    delete letters;
    delete answer;       
    delete Plyinpt; 
    delete inptchk;
    delete nCorrct;            
    delete nPerfc;
    cout<<"good bye"<<endl;
}