/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on Oct 16th, 2018, 2:00 PM
 * Purpose:  project
 */

//System Libraries Here
#include <iostream>   //
#include <cmath>      //
#include <cstdlib>    //
#include <iomanip>    //
#include <ctime>      //
#include <fstream>    //
#include <cstring>    //
using namespace std;

//User Libraries Here
#include "Map.h"
//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
void reveal0(Map *,char**,char,int);      //if 0 reveal all numbers around
Map *filstrc(char**,const int,const int,int);     //create map
void rules();                      //output information if needed
void menu();                       //output menu
char **CrtMap(const int,const int);//create maps
void destroy(Map *);               //clean memory
void shuffle(Map *,int);           //move mines to random places
void around(Map *);                //give the number of mines around each number
void prntmap(Map *);               //print map after game ends
void prntmap(char**,const int,const int);     //print map
void hidemap(char **,const int, const int);   //hided map
void ablties(Map *,char **,float,char,string);//abilities
void reveal(Map *,char **,char,int);         //reveal coordinates given
void destroy(Map *);                          //clean memory
void destroy(char**,const int,const int);     //clean memory
//Program Execution Begins Here
int main(int argc, char** argv) {
    //declare random seed
    srand(static_cast<unsigned int>(time(0)));
    //initialize stream
    fstream in;
    fstream out;
    in.open("save.txt",ios::binary);
    out.open("save.txt",ios::binary);
    //Declare and all Variables Here
    const int ROW=10,COL=10;    //size of array 2D array
    char **hide;                //hided Map 2D array
    char **map;
    char x,                     //input coordinate
         ability;               //ability
    int mode,                   //difficulty mode
        y,                      //row coordinates 
        move,                   //number of moves
        cntn=1,                 //continue playing
        nMines=20;                 //number of mines
    string winlose="Normal",YN;   //win or lost
    float points;               //abilities points
    bool save=false;            // save argument
    //create maps
    map=CrtMap(ROW,COL);
    hide=CrtMap(ROW,COL);
    //fill structure
    Map *minemap;
    //load points
    in>>points;
    //output menu
    do {
        menu();
        cin>>mode;
        if(mode==4)rules();
        else if(mode>4||mode<0)cout<<"Input a valid number"<<endl;
    }while(mode>3||mode<0);
    //create game map
    if(mode>0&&mode<4){
        switch (mode){
        //mines in map map
            case 1: {nMines=1;break;}
            case 2: {nMines=40;break;}
            case 3: {nMines=40;break;}  
        }
        //create map
        minemap=filstrc(map,ROW,COL,nMines);
        //number of non-mines
        move=(ROW*COL)-nMines;
        //hided map
        hidemap(hide,ROW,COL);
        //moves or inputed coordinates
        while(winlose=="Normal"&&move>0){
            cout<<"Do you want to use an ability Y/N -->";
            cin>>YN;
            if(YN=="Y"||YN=="y"){
                    do {
                        cout<<"Points "<<points<<endl;
                        cout<<"if you want to reveal the first non-mine "
                                "input x --> cost 0.1 point"<<endl;
                        cout<<"if you want to reveal the first non-mine "
                                "input v --> cost 0.1 point"<<endl;
                        cout<<"if you want to skip the level input z --> "
                                "cost 1 point"<<endl;
                        cin>>ability;
                        ability='x'?ability='X':ability;
                        ability='v'?ability='V':ability;
                        ability='z'?ability='Z':ability;
                    }while(ability!='X'&&ability!='Z'&&ability!='V');
                    ablties(minemap,map,points,ability,winlose);
                }
            else if(YN=="N"||YN=="n"){   
                    do{
                        cout<<"input the coordinate you want to reveal"
                                <<endl;
                        cin>>x>>y;
                        if(x>=65&&x<=74)x-=65;
                        else if(x>=97&&x<=106)x-=97;
                        if(minemap->map[y][x]==hide[y][x])cout<<"Input a new "
                                "coordinate"<<endl;
                }while(minemap->map[y][x]==hide[y][x]||x<0||x>9||y<0||y>9);
                reveal(minemap,hide,x,y);//give to "hide" the value of inputed coordinates 
                if(minemap->map[y][x]=='0'){reveal0(minemap,hide,x,y);}
                prntmap(hide,ROW,COL);//reveal map;
                move--;                  //moves left to win
                }    
        if(move==0){winlose="Win";points+=sqrt(0.2)/mode;}//if you find 
                                                         //all the mines
        else if(map[y][x]=='X')winlose="Lost";//if the coordinate has a mine
        else points+=0.01/mode;
        }
        //output if winner or loser
        cout<<"you have "<<winlose<<" the game"<<endl;
        //print map after win or lose
        prntmap(minemap);
        if(winlose=="Win"){
            cout<<"do you want to save?Y/N -->";
            cin>>YN;
            YN="y"?YN="Y":YN="Y";
            if(YN=="Y")save=true;}
        if(save==true)out<<points;
    }
    //Exit
    else cout<<"Thanks for playing"<<endl; 
    in.close();
    out.close();
    //clean memory
    destroy(minemap);
    destroy(hide,ROW,COL);
    return 0;
}
char **CrtMap(const int row,const int col){
    char **a=new char*[row];
    for(int i=0;i<row;i++){
        a[i]=new char [col];
    }
    for(int j=0;j<row;j++){
        for(int i=0;i<col;i++){
        a[j][i]=rand()%90+10;
        }
    }
    return a;
}
Map *filstrc(char **a,const int row, const int col,int mines){
    int cnt=1;
    int shfl=7;
    Map *strct=new Map;
    strct->row=row;
    strct->col=col;
    (*strct).map=a;
    for(int i=0;i<strct->row;i++,cnt++){
        for(int j=0;j<strct->col;j++,cnt++){
            if(cnt<=mines){strct->map[i][j]='X';}
            else {strct->map[i][j]='0';}
        }
    }
    //move mines to random places map
    shuffle(strct,shfl);
    //number of mines around a non-mine
    around(strct);
    return strct;
}
void shuffle(Map *strct,int nShfl){
    for(int shfl=1;shfl<nShfl;shfl++){
        for(int i=0;i<strct->row;i++){
            for (int j=0;j<strct->col;j++){
                int random=rand()%strct->row;
                int random2=rand()%strct->col;
                char temp=strct->map[i][j];
                strct->map[i][j]=strct->map[random][random2];
                strct->map[random][random2]=temp;
            }        
        }
    }
}
void around(Map *a){ //count number of mines around a non-mine
    for(int i=0;i<a->row;i++){
        for (int j=0;j<a->col;j++){
            if(a->map[i][j]=='X'&&i!=0&&j!=0&&i!=9&&j!=9){//if the numbers are not
                if(a->map[i+1][j+1]!='X')a->map[i+1][j+1]++;//in the corner rows
                if(a->map[i+1][j]!='X')a->map[i+1][j]++;    //or column
                if(a->map[i+1][j-1]!='X')a->map[i+1][j-1]++;
                if(a->map[i][j+1]!='X')a->map[i][j+1]++;
                if(a->map[i-1][j-1]!='X')a->map[i-1][j-1]++;
                if(a->map[i-1][j]!='X')a->map[i-1][j]++;
                if(a->map[i-1][j+1]!='X')a->map[i-1][j+1]++;
                if(a->map[i][j-1]!='X')a->map[i][j-1]++;
            }
            else if(a->map[i][j]=='X'&&i==0&&j==0){ //non-mine counter for the
                if(a->map[i+1][j+1]!='X')a->map[i+1][j+1]++;   //top left corner
                if(a->map[i+1][j]!='X')a->map[i+1][j]++;
                if(a->map[i][j+1]!='X')a->map[i][j+1]++;
            }
            else if(a->map[i][j]=='X'&&i==9&&j==9){ //non-mine counter for the
                if(a->map[i-1][j-1]!='X')a->map[i-1][j-1]++;//the bottom right corner
                if(a->map[i-1][j]!='X')a->map[i-1][j]++;
                if(a->map[i][j-1]!='X')a->map[i][j-1]++;
            }
            else if(a->map[i][j]=='X'&&i==0&&j==9){   //non-mine counter for 
                if(a->map[i+1][j-1]!='X')a->map[i+1][j-1]++;//the top right corner
                if(a->map[i+1][j]!='X')a->map[i+1][j]++;
                if(a->map[i][j-1]!='X')a->map[i][j-1]++;
            }
            else if(a->map[i][j]=='X'&&i==9&&j==0){  //non-mine counter for 
                if(a->map[i-1][j+1]!='X')a->map[i-1][j+1]++;//the bottom left corner
                if(a->map[i-1][j]!='X')a->map[i-1][j]++;
                if(a->map[i][j+1]!='X')a->map[i][j+1]++;
            }
            else if(a->map[i][j]=='X'&&i==0&&j>0&&j<9){   //non-mine counter for
                if(a->map[i+1][j+1]!='X')a->map[i+1][j+1]++;//up non-corner line
                if(a->map[i+1][j]!='X')a->map[i+1][j]++;     
                if(a->map[i+1][j-1]!='X')a->map[i+1][j-1]++;
                if(a->map[i][j+1]!='X')a->map[i][j+1]++;
                if(a->map[i][j-1]!='X')a->map[i][j-1]++;
            }
            else if(a->map[i][j]=='X'&&i==9&&j>0&&j<9){//non-mine counter for the
                if(a->map[i-1][j+1]!='X')a->map[i-1][j+1]++;//bottom non-corner line
                if(a->map[i-1][j]!='X')a->map[i-1][j]++;      
                if(a->map[i-1][j-1]!='X')a->map[i-1][j-1]++;
                if(a->map[i][j+1]!='X')a->map[i][j+1]++;
                if(a->map[i][j-1]!='X')a->map[i][j-1]++;
            }
            else if(a->map[i][j]=='X'&&j==0&&i>0&&i<9){   //non-mine counter for 
                if(a->map[i+1][j+1]!='X')a->map[i+1][j+1]++;   //left corner line
                if(a->map[i+1][j]!='X')a->map[i+1][j]++;
                if(a->map[i][j+1]!='X')a->map[i][j+1]++;
                if(a->map[i-1][j]!='X')a->map[i-1][j]++;
                if(a->map[i-1][j+1]!='X')a->map[i-1][j+1]++;
            }
            else if(a->map[i][j]=='X'&&j==9&&i>0&&i<9){   //bottom corner line
                if(a->map[i+1][j-1]!='X')a->map[i+1][j-1]++;
                if(a->map[i+1][j]!='X')a->map[i+1][j]++;
                if(a->map[i][j-1]!='X')a->map[i][j-1]++;
                if(a->map[i-1][j]!='X')a->map[i-1][j]++;
                if(a->map[i-1][j-1]!='X')a->map[i-1][j-1]++;
            }
        }
    }
}
void prntmap(Map *strct){
    cout<<"#  A B C D E F G H I J"<<endl;
    cout<<"  ____________________"<<endl;
    for(int i=0;i<strct->row;i++){
        cout<<i<<"|";
        for(int j=0;j<strct->col;j++){
            cout<<setw(2)<<strct->map[i][j];
        }
        cout<<endl;
    }
}
void prntmap(char **hide,const int row,const int col){
    cout<<"#  A B C D E F G H I J"<<endl;
    cout<<"  ____________________"<<endl;
    for(int i=0;i<row;i++){
        cout<<i<<"|";
        for(int j=0;j<col;j++){
            cout<<setw(2)<<hide[i][j];
        }
        cout<<endl;
    }
}
void hidemap(char **hide,const int row,const int col){     //hided map
    cout<<"#  A B C D E F G H I J"<<endl; 
    cout<<"  ____________________"<<endl;
    for(int i=0;i<row;i++){
        cout<<i<<"|";
        for(int j=0;j<col;j++){
            hide[i][j]='?';
            cout<<setw(2)<<hide[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}
void ablties(Map *strct,char **hide,float point,char type,string winlose){
    char x;
    int y;
    if (type=='x'&&point>=0.1||type=='X'&&point>=0.1){
        x=-1;
        y=0;
        do{
            if(x==10)y++;x-=10;
            x++;
            point-=0.1;
        }while(strct->map[y][x]=='X');
        reveal(strct,hide,x,y);
    }
    else if(type=='v'&&point>=0.1||type=='V'&&point>=0.1){
        x=10;
        y=9;
        do{
            if(x==-1)y--;x+=10;
            x--;
        }while(strct->map[y][x]=='X');
        reveal(strct,hide,x,y);
        point-=0.1;
    }
    else if(type=='z'&&point>=1||type=='Z'&&point>=1){
        winlose="Win";
        point--;
    }
    else cout<<"You do not have enough points or you do not input a correct"
            " letter"<<endl;
}
void reveal(Map *strct,char **hide,char x,int y){
    hide[y][x]=strct->map[y][x];//reveal the coordinates inputed
}
void reveal0(Map *strct,char **hide,char x,int y){
    int cntx=x;
    int cnty=y;
    if(x==0){
        cntx=x;
        while(strct->map[y][cntx]=='0'&&cntx<strct->col){
            reveal(strct,hide,cntx,y); 
            cntx++; 
        }
        cntx=x;
        cnty=y;
        while(strct->map[cnty][cntx]=='0'&&cntx<strct->col-1&&cnty<strct->row-1){
            cntx++;
            cnty++;
            reveal(strct,hide,cntx,cnty);  
        }
    }
    if(x==9){
        cntx=x;
        while(strct->map[y][cntx]=='0'&&cntx>=0){
            reveal(strct,hide,cntx,y); 
            cntx--;  
        }
        cntx=x;
        cnty=y;
        while(strct->map[cnty][cntx]=='0'&&cntx>=1&&cnty<strct->row-1){
            cntx--;
            cnty++;
            reveal(strct,hide,cntx,cnty);  
            
        }
    }
    if(x>0&&x<9){
        cntx=x;
        while(strct->map[y][cntx]=='0'&&cntx<strct->col){
            reveal(strct,hide,cntx,y); 
            cntx++; 
        }
        cntx=x;
        while(strct->map[y][cntx]=='0'&&cntx>=0){
            reveal(strct,hide,cntx,y); 
            cntx--;
        }
        cntx=x;
        cnty=y;
        while(strct->map[cnty][cntx]=='0'&&cntx<strct->col-1&&cnty<strct->row-1){
            cntx++;
            cnty++;
            reveal(strct,hide,cntx,cnty);  
        }
        cntx=x;
        cnty=y;
        while(strct->map[cnty][cntx]=='0'&&cntx>=1&&cnty<strct->row-1){
            cntx--;
            cnty++;
            reveal(strct,hide,cntx,cnty);   
        }
    }
    if(y==0){
        cnty=y;
        while(strct->map[cnty][x]=='0'&&cnty<strct->row-1){
            cnty++; 
            reveal(strct,hide,x,cnty); 
        }
    }
    if(y==9){
        cnty=y;
        while(strct->map[cnty][x]=='0'&&cnty>=1){
            cnty--; 
            reveal(strct,hide,x,cnty);  
        } 
    }
    if(y>0&&y<9){
        cnty=y;
        while(strct->map[cnty][x]=='0'&&cnty<strct->row-1){
            cnty++; 
            reveal(strct,hide,x,cnty);     
        } 
        cnty=y;
        while(strct->map[cnty][x]=='0'&&cnty>=1){
            cnty--; 
            reveal(strct,hide,x,cnty);  
        }
        cntx=x;
        cnty=y;
        while(strct->map[cnty][cntx]=='0'&&cntx>=1&&cnty>=1){
            cntx--;
            cnty--;
            reveal(strct,hide,cntx,cnty);  
        }
        cntx=x;
        cnty=y;
        while(strct->map[cnty][cntx]=='0'&&cnty>=1&&cntx<strct->col-1){
            cntx++;
            cnty--;
            reveal(strct,hide,cntx,cnty);   
        }
    }
}
void destroy(Map *d2){
    for(int i=0;i<d2->row;i++){
        delete []d2->map[i];
    }
    delete []d2->map;
    delete d2;
}
void destroy(char **map,const int row,const int col){
    for(int i=0;i<row;i++){
            delete []map[i];}
    delete map;
}

void rules(){
    cout<<"In order to win the game, you must reveal all the squares that "
          "DO NOT contain a mine, whether you flag them or not is a matter"
          " of personal preference."<<endl<<"If a mine is revealed,"
          " the player loses"<<endl;
    cout<<"to reveal a location you must enter the coordinates of it, as X "
            "coordinates represented by a letter and Y coordinates as numbers"
            <<endl<<"EX: A9, to flag a coordinate you must enter an Z before"
            "the coordinate EX: ZA9"<<endl;
    cout<<"The number that you reveal represent the number of mines around them"
            <<endl;
    cout<<"Mines are represented as X"<<endl;
    cout<<"easy mode has a maximum of 20 mines at the beginning"<<endl;
    cout<<"Normal mode has a maximum of 40 mines at the beginning"<<endl;
    cout<<"Hard mode has a maximum of 60 mines at the beginning"<<endl;
    cout<<"you are able to use abilities"<<endl;
    cout<<"if input x ability work to reveal the first non-number"<<endl;
    cout<<"if input v ability work to reveal the last non-number"<<endl;
    cout<<"if input z ability you will skip the level but you wont get win"
            " points"<<endl;
}
void menu(){
        cout<<"Welcome to Minesweeper"<<endl;
        cout<<"To get into easy mode press 1"<<endl;
        cout<<"To get into normal mode input 2"<<endl;
        cout<<"To get into hard mode input 3"<<endl;
        cout<<"To know information of the game press 4"<<endl;
        cout<<"To Exit input 0"<<endl;
}