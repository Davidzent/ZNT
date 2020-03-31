/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on OCT  11th, 2018, 2:00 PM
 * Purpose:  project
 */

//System Libraries Here
#include <iostream>   //x
#include <cmath>      //x
#include <cstdlib>    //x
#include <iomanip>    //x
#include <ctime>      //x
#include <fstream>
using namespace std;

//User Libraries Here
#include "Map.h"
//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
void rules();//output information if needed
void menu(); //output menu
char **CrtMap(int,int);            //create maps
Map *filstrc(char**,int,int);      //fill structure
void destroy(Map *);               //clean memory
void fillmap(Map *,int);           //fill map with mines and non-mines
void shuffle(Map *,int);               //move mines to random places
void around(Map *); //give the number of mines around each number
void prntmap(Map *); //output map after win or lost
void hidemap(char **,int,int); //hided map

void ablties(Map *,char **,float,char,string);//abilities
void reveal(Map *,char **,char,char); //reveal 
                                                           //coordinates given
float point(int,int);
//Program Execution Begins Here
int main(int argc, char** argv) {
    //declare random seed
    srand(static_cast<unsigned int>(time(0)));
    //initialize stream
    ifstream in;
    ofstream out;
    in.open("save.dat");
    out.open("save.dat");
    //Declare and all Variables Here
    const int ROW=10,COL=10;    //size of array 2D array
    const int shfl=7;           //times to randomize mines
    char **map;                 //hided Map 2D array
    char x,y,                   //input coordinate
         ability;               //ability
    int mode,                   //difficulty mode
        move,                   //number of moves
        cntn=1,                 //continue playing
        nMines;                 //number of mines
    string winlose="Normal",YN,pts;   //win or lost
    float points;               //abilities points
    bool save=false;            // save argument
    //create maps
    map=CrtMap(ROW,COL);
    //fill structure
    Map *minemap=filstrc(map,ROW,COL);
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
        //create type of map
            case 1: {
                nMines=20;
                fillmap(minemap,nMines);break;
            }
            case 2: {
                nMines=40;
                fillmap(minemap,nMines);break;
            }
            case 3: {
                nMines=40;
                fillmap(minemap,nMines);break;
            }
        }
        //count number of moves before ending the game
        move=ROW*COL-nMines;
        //move again mines to random places map
        shuffle(minemap,shfl);
        //number of mines around a non-mine
        around(minemap);
        //hided map
        hidemap(map,ROW,COL);
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
                        if(minemap->map[y][x]==map[y][x])cout<<"Input a new "
                                "coordinate"<<endl;
                }while(minemap->map[y][x]==map[y][x]||x<0||x>9||y<0||y>9);
                reveal(minemap,map,x,y);//reveal the coordinate inputed
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
    return 0;
}
char **CrtMap(int row,int col){
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
Map *filstrc(char **a,int n,int col){
    Map *d2=new Map;
    d2->row=n;
    d2->col=col;
    (*d2).map=a;
    return d2;
}
void fillmap(Map *strct,int mines){
    int cnt=0;
    for(int i=0;i<strct->row;i++){
        for(int j=0;j<strct->col;j++){
            if(cnt<=mines)strct->map[i][j]='X';
            else strct->map[i][j]='0';
        }
    }
}
/*void destroy(Map *d2){
    for(int i=0;i<d2->row;i++){
        delete []d2->array;
    }
    delete []d2->array;
    delete d2;
}*/
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
            if(a->map[i][j]=='X'&&i!=0&&j!=0&&i!=9&&j!=9){  //if the numbers are not
                if(a->map[i+1][j+1]!='X')a->map[i+1][j+1]++;     //in the corner lines
                if(a->map[i+1][j]!='X')a->map[i+1][j]++;
                if(a->map[i+1][j-1]!='X')a->map[i+1][j-1]++;
                if(a->map[i][j+1]!='X')a->map[i][j+1]++;
                if(a->map[i-1][j-1]!='X')a->map[i-1][j-1]++;
                if(a->map[i-1][j]!='X')a->map[i-1][j]++;
                if(a->map[i-1][j+1]!='X')a->map[i-1][j+1]++;
                if(a->map[i][j-1]!='X')a->map[i][j-1]++;
            }
            else if(a->map[i][j]=='X'&&i==0&&j==0){        //non-mine counter for
                if(a->map[i+1][j+1]!='X')a->map[i+1][j+1]++;    //the top left corner
                if(a->map[i+1][j]!='X')a->map[i+1][j]++;
                if(a->map[i][j+1]!='X')a->map[i][j+1]++;
            }
            else if(a->map[i][j]=='X'&&i==9&&j==9){        //non-mine counter for the
                if(a->map[i-1][j-1]!='X')a->map[i-1][j-1]++;    //the bottom right corner
                if(a->map[i-1][j]!='X')a->map[i-1][j]++;
                if(a->map[i][j-1]!='X')a->map[i][j-1]++;
            }
            else if(a->map[i][j]=='X'&&i==0&&j==9){       //non-mine counter for 
                if(a->map[i+1][j-1]!='X')a->map[i+1][j-1]++;   //the bottom left corner
                if(a->map[i-1][j]!='X')a->map[i-1][j]++;
                if(a->map[i][j-1]!='X')a->map[i][j-1]++;
            }
            else if(a->map[i][j]=='X'&&i==9&&j==0){       //non-mine counter for 
                if(a->map[i-1][j+1]!='X')a->map[i-1][j+1]++;   //the top right corner
                if(a->map[i-1][j]!='X')a->map[i-1][j]++;
                if(a->map[i][j-1]!='X')a->map[i][j-1]++;
            }
            else if(a->map[i][j]=='X'&&i==0&&j>0&&j<9){   //non-mine counter for
                if(a->map[i+1][j+1]!='X')a->map[i+1][j+1]++;   //up corner line
                if(a->map[i+1][j]!='X')a->map[i+1][j]++;     
                if(a->map[i+1][j-1]!='X')a->map[i+1][j-1]++;
                if(a->map[i][j+1]!='X')a->map[i][j+1]++;
                if(a->map[i][j-1]!='X')a->map[i][j-1]++;
            }
            else if(a->map[i][j]=='X'&&i==9&&j>0&&j<9){   //non-mine counter for
                if(a->map[i-1][j+1]!='X')a->map[i+1][j+1]++;   //the right corner line
                if(a->map[i-1][j]!='X')a->map[i+1][j]++;      
                if(a->map[i-1][j-1]!='X')a->map[i+1][j-1]++;
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
void reveal(Map *strct,char **hide,char x,char y){
    hide[y][x]=strct->map[y][x];                //reveal the coordinates inputed 
    cout<<"#  A B C D E F G H I J"<<endl;//re-output the map
    cout<<"  ____________________"<<endl;
    for(int i=0;i<strct->row;i++){
        cout<<i<<"| ";
        for(int j=0;j<strct->col;j++){
            cout<<hide[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl; 
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