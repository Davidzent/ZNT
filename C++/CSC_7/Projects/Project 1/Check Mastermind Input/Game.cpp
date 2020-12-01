#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <fstream>

Game::Game(int nLetter,int codesz,int atempts,bool duplica){
    file.open("output.txt");
    this->nLetter=nLetter;
    this->atempts=atempts;
    nInput=0;
    CodeSz=codesz;
    duplict=duplica;
    status=true;
    letters=new char[nLetter];
    Plyinpt=new char*[atempts];
    answer=new char[CodeSz];
    nCorrct=new int[atempts];            
    nPerfc=new  int[atempts];
    for(int i=0;i<atempts;i++){
        Plyinpt[i]=new char[CodeSz];
    }
    for(int i=0;i<nLetter;i++){
        letters[i]='0'+i;
    }
}
void Game::instans(char *answer){
    for(int i=0;i<CodeSz;i++){
        if(answer[i]<'0'||answer[i]>'9')cout<<"the input was out of the range\n"<<"Leaving the Game",exit(0);
        this->answer[i]=answer[i];
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
    bool temp[CodeSz];
    bool temp2[CodeSz];
    for(int i=0;i<CodeSz;i++){
        temp[i]=0;
        temp2[i]=0;
        if(answer[i]==Plyinpt[nInput][i]){
            nPerfc[nInput]++;
            temp[i]=1;
            temp2[i]=1;
        }
    }
    for(int i=0;i<CodeSz;i++){
        for(int j=0;j<CodeSz;j++){
            if(!temp[i]&&!temp2[j]&&answer[i]==Plyinpt[nInput][j]){
                temp[i]=1;
                temp2[j]=1;
                nCorrct[nInput]++;
            }
        }
    }
    file<<"answer -> "<<answer<<endl;
    file<<"You Find "<<nCorrct[nInput]<<" correct letters in the wrong spot and "
            <<nPerfc[nInput]<<" letters in the right spot"<<" the sum = "<<nCorrct[nInput]+nPerfc[nInput]<<endl;
    //if(nPerfc[nInput]==CodeSz)status=false,cout<<"You Won the Game\n";
    if(atempts==nInput+1){
            status=false;
            file<<"\nyou lose the game\n"<<"the correct answer was: "<<answer<<endl;
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
    delete nCorrct;            
    delete nPerfc;
    file.close();
    cout<<"good bye"<<endl;
}