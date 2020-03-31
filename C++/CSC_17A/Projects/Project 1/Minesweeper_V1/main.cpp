/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on May  20th, 2018, 7:00 PM
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

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions
const char COLUMN=10;// 2 dimensional size array
//Function Prototypes Here
void rules();//output information if needed
void menu(); //output menu
void shuffle(char[][COLUMN],char);  //move mines to random places again
void nonmine(char[][COLUMN],char); //make 0 all non mines
int moves(char[][COLUMN],char);
void around(char [][COLUMN],char); //give the number of mines around each number
void mapEz(char [][COLUMN],char);  //easy mode    20 mines
void mapNm(char [][COLUMN],char);  //normal mode  40 mines
void mapHd(char [][COLUMN],char);  //hard mode    60 mines
void prntmap(char[][COLUMN],char); //output map after win or lost
void hidemap(char[][COLUMN],char); //hided map
void ablties(char[][COLUMN],char[][COLUMN],char,float,char,string);//abilities
void reveal(char[][COLUMN],char[][COLUMN],char,char,char); //reveal 
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
    //Declare all Variables Here
    const char SIZE=10;        //size of array
    char map[SIZE][COLUMN],x,  //map array & input coordinate
         hide[SIZE][COLUMN],   //hided map
         ability;            //ability
    int y,mode,                //input coordinate and mode
        cntn=1,                  //continue playing
        move;                 //moves=number of non-mines
    string winlose="Normal",YN,pts;   //if win or lost
    float points;              //abilities points
    bool save=false;
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
            case 1: mapEz(map,SIZE);break;
            case 2: mapNm(map,SIZE);break;
            case 3: mapHd(map,SIZE);break;
        }
        //move again mines to random places map
        shuffle(map,SIZE);
        //count number of non-mines
        move=moves(map,SIZE);
        //make numbers all non-mines
        nonmine(map,SIZE);
        //number of mines around a non-mine
        around(map,SIZE);
        //hided map
        hidemap(hide,SIZE);
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
                    ablties(map,hide,SIZE,points,ability,winlose);
                }
            else if(YN=="N"||YN=="n"){   
                    do{
                        cout<<"input the coordinate you want to reveal"
                                <<endl;
                        cin>>x>>y;
                        if(x>=65&&x<=74)x-=65;
                        else if(x>=97&&x<=106)x-=97;
                        if(map[y][x]==hide[y][x])cout<<"Input a new "
                                "coordinate"<<endl;
                }while(map[y][x]==hide[y][x]||x<0||x>9||y<0||y>9);
                reveal(hide,map,SIZE,x,y);//reveal the coordinate inputed
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
        prntmap(map,SIZE);
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
void shuffle (char c[][COLUMN],char n){
    for(int shfl=1;shfl<7;shfl++){
        for(int i=0;i<n;i++){
            for (int j=0;j<COLUMN;j++){
                int random=rand()%n,random2=rand()%COLUMN;
                char temp=c[i][j];
                c[i][j]=c[random][random2];
                c[random][random2]=temp;
            }        
        }
    }
}
void nonmine(char a[][COLUMN],char n){
    for(int i=0;i<n;i++){
        for (int j=0;j<COLUMN;j++){
            if(a[i][j]!='X')a[i][j]='0'; //make all non-mines a 0
        }
    }
}
int moves(char a[][COLUMN],char n){
    int move=0;
    for(int i=0;i<n;i++){
        for (int j=0;j<COLUMN;j++){
            if(a[i][j]!='X')move++; //make all non-mines a 0
        }
    }
    return move;
}
void around(char a[][COLUMN],char n){ //count number of mines around a non-mine
    for(int i=0;i<n;i++){
        for (int j=0;j<COLUMN;j++){
            if(a[i][j]=='X'&&i!=0&&j!=0&&i!=9&&j!=9){  //if the numbers are not
                if(a[i+1][j+1]!='X')a[i+1][j+1]++;     //in the corner lines
                if(a[i+1][j]!='X')a[i+1][j]++;
                if(a[i+1][j-1]!='X')a[i+1][j-1]++;
                if(a[i][j+1]!='X')a[i][j+1]++;
                if(a[i-1][j-1]!='X')a[i-1][j-1]++;
                if(a[i-1][j]!='X')a[i-1][j]++;
                if(a[i-1][j+1]!='X')a[i-1][j+1]++;
                if(a[i][j-1]!='X')a[i][j-1]++;
            }
            else if(a[i][j]=='X'&&i==0&&j==0){        //non-mine counter for
                if(a[i+1][j+1]!='X')a[i+1][j+1]++;    //the top left corner
                if(a[i+1][j]!='X')a[i+1][j]++;
                if(a[i][j+1]!='X')a[i][j+1]++;
            }
            else if(a[i][j]=='X'&&i==9&&j==9){        //non-mine counter for the
                if(a[i-1][j-1]!='X')a[i-1][j-1]++;    //the bottom right corner
                if(a[i-1][j]!='X')a[i-1][j]++;
                if(a[i][j-1]!='X')a[i][j-1]++;
            }
            else if(a[i][j]=='X'&&i==0&&j==9){       //non-mine counter for 
                if(a[i+1][j-1]!='X')a[i+1][j-1]++;   //the bottom left corner
                if(a[i-1][j]!='X')a[i-1][j]++;
                if(a[i][j-1]!='X')a[i][j-1]++;
            }
            else if(a[i][j]=='X'&&i==9&&j==0){       //non-mine counter for 
                if(a[i-1][j+1]!='X')a[i-1][j+1]++;   //the top right corner
                if(a[i-1][j]!='X')a[i-1][j]++;
                if(a[i][j-1]!='X')a[i][j-1]++;
            }
            else if(a[i][j]=='X'&&i==0&&j>0&&j<9){   //non-mine counter for
                if(a[i+1][j+1]!='X')a[i+1][j+1]++;   //up corner line
                if(a[i+1][j]!='X')a[i+1][j]++;     
                if(a[i+1][j-1]!='X')a[i+1][j-1]++;
                if(a[i][j+1]!='X')a[i][j+1]++;
                if(a[i][j-1]!='X')a[i][j-1]++;
            }
            else if(a[i][j]=='X'&&i==9&&j>0&&j<9){   //non-mine counter for
                if(a[i-1][j+1]!='X')a[i+1][j+1]++;   //the right corner line
                if(a[i-1][j]!='X')a[i+1][j]++;      
                if(a[i-1][j-1]!='X')a[i+1][j-1]++;
                if(a[i][j+1]!='X')a[i][j+1]++;
                if(a[i][j-1]!='X')a[i][j-1]++;
            }
            else if(a[i][j]=='X'&&j==0&&i>0&&i<9){   //non-mine counter for 
                if(a[i+1][j+1]!='X')a[i+1][j+1]++;   //left corner line
                if(a[i+1][j]!='X')a[i+1][j]++;
                if(a[i][j+1]!='X')a[i][j+1]++;
                if(a[i-1][j]!='X')a[i-1][j]++;
                if(a[i-1][j+1]!='X')a[i-1][j+1]++;
            }
            else if(a[i][j]=='X'&&j==9&&i>0&&i<9){   //bottom corner line
                if(a[i+1][j-1]!='X')a[i+1][j-1]++;
                if(a[i+1][j]!='X')a[i+1][j]++;
                if(a[i][j-1]!='X')a[i][j-1]++;
                if(a[i-1][j]!='X')a[i-1][j]++;
                if(a[i-1][j-1]!='X')a[i-1][j-1]++;
            }
        }
    }
}
void mapEz(char a[][COLUMN],char b){
    int nMine=20,nMnCnt=0,maxmine;
    for(int i=0;i<b;i++){
        for(int j=0;j<COLUMN;j++){ 
            if(nMnCnt<nMine)a[i][j]=rand()%2+88;
            else if (nMnCnt>=nMine)a[i][j]='Y';               
            if (a[i][j]=='X')nMnCnt++;
        }
    }
}
void mapNm(char a[][COLUMN],char b){
    int nMine=40,nMnCnt=0,maxmine;
    for(int i=0;i<b;i++){
        for(int j=0;j<COLUMN;j++){ 
            if(nMnCnt<nMine)a[i][j]=rand()%2+88;
            else if (nMnCnt>=nMine)a[i][j]='Y';               
            if (a[i][j]=='X')nMnCnt++;
        }
    }
}
void mapHd(char a[][COLUMN],char b){
    int nMine=60,nMnCnt=0,maxmine;
    for(int i=0;i<b;i++){
        for(int j=0;j<COLUMN;j++){ 
            if(nMnCnt<nMine)a[i][j]=rand()%2+88;
            else if (nMnCnt>=nMine)a[i][j]='Y';               
            if (a[i][j]=='X')nMnCnt++;
        }
    }
}
void prntmap(char a[][COLUMN],char b){
    cout<<"#  A B C D E F G H I J"<<endl;
    cout<<"  ____________________"<<endl;
    for(int i=0;i<b;i++){
        cout<<i<<"|";
        for(int j=0;j<COLUMN;j++){
            cout<<setw(2)<<a[i][j];
        }
        cout<<endl;
    }
}
void hidemap(char a[][COLUMN],char n){     //hided map
    cout<<"#  A B C D E F G H I J"<<endl; 
    cout<<"  ____________________"<<endl;
    for(int i=0;i<n;i++){
        cout<<i<<"|";
        for(int j=0;j<COLUMN;j++){
            a[i][j]='?';
            cout<<setw(2)<<a[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}
void ablties(char map[][COLUMN],char hide[][COLUMN],char n,float point,
        char type,string winlose){
    char x;
    int y;
    if (type=='x'&&point>=0.1||type=='X'&&point>=0.1){
        x=-1;
        y=0;
        do{
            if(x==10)y++;x-=10;
            x++;
            point-=0.1;
        }while(map[y][x]=='X');
        reveal(hide,map,n,x,y);
    }
    else if(type=='v'&&point>=0.1||type=='V'&&point>=0.1){
        x=10;
        y=9;
        do{
            if(x==-1)y--;x+=10;
            x--;
        }while(map[y][x]=='X');
        reveal(hide,map,n,x,y);
        point-=0.1;
    }
    else if(type=='z'&&point>=1||type=='Z'&&point>=1){
        winlose="Win";
        point--;
    }
    else cout<<"You do not have enough points or you do not input a correct"
            " letter"<<endl;
}
void reveal(char hide[][COLUMN],char map[][COLUMN],char n,char x,char y){
    hide[y][x]=map[y][x];                //reveal the coordinates inputed 
    cout<<"#  A B C D E F G H I J"<<endl;//re-output the map
    cout<<"  ____________________"<<endl;
    for(int i=0;i<n;i++){
        cout<<i<<"| ";
        for(int j=0;j<COLUMN;j++){
            cout<<hide[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl; 
}