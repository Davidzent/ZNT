#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <fstream>

Game::Game(int nLetter,int codesz,int atempts,bool duplica,char nmfile[]){
    this->nLetter=nLetter;
    this->atempts=atempts;
    CodeSz=codesz;
    duplict=duplica;
    letters=new char[nLetter];
    /*ifstream file;
    file.open(nmfile);
    for(int i=0;i<nLetter;i++){
        file>>letters[i];
    }
    file.close();*/
    status=true;
}
void Game::crtans(){
    answer=new char[CodeSz];
    for(int i=0;i<CodeSz;i++){
        
        if(!duplict){
            do{
            answer[i]=rand()%26+65;
            }while(chkdupl(i));}
        else answer[i]=rand()%26+65;
        cout<<answer[i]<<" ";
    }
    cout<<endl;
}
bool Game::chkdupl(int max){
    for(int i=0;i<max-1;i++){
        for(int j=i+1;j<max;j++){
            if(answer[i]==answer[j])return true;
        }
    }
    return false;
}
bool Game::chkletr(){
    int cnt=0;
    for(int i=0;i<CodeSz;i++){
        if(Plyinpt[i]>='a'&&Plyinpt[i]<='z')Plyinpt[i]-=32;
        if(Plyinpt[i]>='A'&&Plyinpt[i]<='Z')cnt++;
    }
    if(cnt==CodeSz)return true;
    return false;
}
void Game::chcinpt(){
    int correct=0;
    int Perfect=0;
    for(int i=0;i<CodeSz;i++){
        if(Plyinpt[i]==answer[i])Perfect++;
        for(int j=0;j<CodeSz;j++){
            if(Plyinpt[i]==answer[j])correct++;
        }
    }
    cout<<endl;
    cout<<"You Find "<<correct<<" correct letters and "
            <<Perfect<<" are in the right spot\n";
    if(Perfect==CodeSz)status=false,cout<<"You Won the Game\n";
    
}
void Game::play(){
    crtans();
    while(status){
        cout<<"Enter your guess : ";
        do{
            for(int i=0;i<CodeSz;i++){
                cin>>Plyinpt[i];
            }
            if(!chkletr())cout<<"You enter an invalid input, try again"<<endl;
        }while(!(chkletr()));
        chcinpt();
        if(--atempts>0)status=true;
        else status=false;
    }
}

Game::~Game(){
        delete answer;       
        delete Plyinpt;    
        delete letters;
}
/*friend iostream &operator >>(iostream in,Game game){
    char letter[game.CodeSz];
    cout<<"Enter your guess :\n";
    do{
        in>>letter;
        
    }while(!(game.chkcolr(letter)));
    for(int i=0;i<game.CodeSz;i++){
        game.letters[i]=letter[i];
    }
}*/