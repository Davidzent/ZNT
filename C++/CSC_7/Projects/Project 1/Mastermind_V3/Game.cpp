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
void Game::chcinpt(){
    nCorrct=0;
    nPerfc=0;
    for(int i=0;i<CodeSz;i++){
        inptchk[i]=true;
    }
    for(int i=0;i<CodeSz;i++){
        if(Plyinpt[nInput][i]==answer[i])nPerfc++;
        for(int j=0;j<CodeSz;j++){
            if(Plyinpt[nInput][i]==answer[j]&&inptchk[j])nCorrct++,inptchk[j]=false;
        }
    }
    cout<<"answer -> "<<answer<<endl;
    cout<<endl<<"You Find "<<nCorrct<<" correct letters and "
            <<nPerfc<<" are in the right spot\n";
    if(nPerfc==CodeSz)status=false,cout<<"You Won the Game\n";
    else if(atempts==nInput+1){
            status=false;
            cout<<"you lose the game\n"<<"the correct answer was: "<<answer<<endl;
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
        chcinpt();
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
    cout<<"good bye"<<endl;
}