/* 
 * File:   player.h
 * Author: David guijosa
 *
 * Created on November 23, 2018, 2:24 PM
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "Maps.h"
using namespace std;

MAP::MAP(){
    row=0;
    col=0;
}
MAP::MAP(int row,int col){
    this->row=row;
    this->col=col;
}
void MAP::setrow(int row){
    this->row=row;
}
void MAP::setcol(int col){
    this->col=col;
}
void MAP::setnmin(int nmines){
    this->nmines=nmines;
}
int MAP::getcol()const{
    return col;
}
int MAP::getrow()const{
    return row;
}
int MAP::getnmin() const{
    return nmines;
}
char MAP::getcord(int y, char x)const{
    return map[y][x];
}
int MAP::gtmoves() const{
    return moves;
}
void MAP::shufle(){
    srand(static_cast<unsigned int>(time(0)));
    for(int nShuf=0;nShuf<=7;nShuf++){
        for(int i=0;i<row;i++){
            for (int j=0;j<col;j++){
                int random=rand()%row;
                int random2=rand()%col;
                char temp=map[i][j];
                map[i][j]=map[random][random2];
                map[random][random2]=temp;
            }        
        }
    }
}
void MAP::cntmine(){
    for(int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            if(map[i][j]=='X'&&i!=0&&j!=0&&i!=9&&j!=9){
                for(int y=i-1;y<=i+1;y++){
                    for(int x=j-1;x<=j+1;x++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }  
            }
            else if(map[i][j]=='X'&&i==0&&j==0){ //non-mine counter for the
                for(int y=i;y<=i+1;y++){
                    for(int x=j;x<=j+1;x++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&i==9&&j==9){ //non-mine counter for the
                for(int y=i-1;y<=i;y++){
                    for(int x=j-1;x<=j;x++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&i==0&&j==9){   //non-mine counter for 
                for(int y=i;y<=i+1;y++){
                    for(int x=j-1;x<=j;x++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&i==9&&j==0){  //non-mine counter for 
                for(int y=i-1;y<=i;y++){
                    for(int x=j;x<=j+1;x++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&i==0&&j>0&&j<9){   //non-mine counter for
                for(int y=i;y<=i+1;y++){
                    for(int x=j-1;x<=j;x++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&i==9&&j>0&&j<9){//non-mine counter for the
                for(int y=i-1;y<=i;y++){
                    for(int x=j-1;x<=j+1;x++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&j==0&&i>0&&i<9){   //non-mine counter for 
                for(int y=i-1;y<=i+1;y++){
                    for(int x=j;x<=j+1;x++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&j==9&&i>0&&i<9){   //bottom corner line
                for(int y=i-1;y<=i+1;y++){
                    for(int x=j-1;x<=j;x++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
        }
    }
}
void MAP::crtmaps(){
    map=new char*[row];
    index=new char*[row];
    for(int i=0;i<row;i++){
        map[i]=new char[col];
        index[i]=new char[col];
    }
    for(int i=0,x=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(x<nmines)map[i][j]='X',x++;
            else map[i][j]='0';
            index[i][j]='?';
        }
    }
    shufle();
    cntmine();
    prntmap();
    moves=(row*col)-nmines;
}
void MAP::reveal(int y,char x){
    moves--;
    index[y][x]=map[y][x];
}
void MAP::reveal0(int y, char x){
    if(!aredy(y,x)){
        reveal(y,x);
        //left upper
        if(map[y][x]=='0'&&x==0&&y==0){
            for(int i=y;i<=y+1;i++){
                for(int j=x;j<=x+1;j++){
                    if(map[i][j]=='0'&&!aredy(i,j))reveal0(i,j);
                    else if(map[i][j]!='X'&&!aredy(i,j))reveal(i,j);
                }
            }
        }
        //right bottom
        else if(map[y][x]=='0'&&x==9&&y==9){
            for(int i=y-1;i<=y;i++){
                for(int j=x-1;j<=x;j++){
                    if(map[i][j]=='0'&&!aredy(i,j))reveal0(i,j);
                    else if(map[i][j]!='X'&&!aredy(i,j))reveal(i,j);
                }
            }
        }
        //right upper
        else if(map[y][x]=='0'&&x==0&&y==9){
            for(int i=y-1;i<=y;i++){
                for(int j=x;j<=x+1;j++){
                    if(map[i][j]=='0'&&!aredy(i,j))reveal0(i,j);
                    else if(map[i][j]!='X'&&!aredy(i,j))reveal(i,j);
                }
            }
        }
        //left bottom
        else if(map[y][x]=='0'&&x==9&&y==0){
            for(int i=y;i<=y+1;i++){
                for(int j=x-1;j<=x;j++){
                    if(map[i][j]=='0'&&!aredy(i,j))reveal0(i,j);
                    else if(map[i][j]!='X'&&!aredy(i,j))reveal(i,j);
                }
            }
        }
        //center
        else if(map[y][x]=='0'&&x>0&&y>0&&x<9&&y<9){
            for(int i=y-1;i<=y+1;i++){
                for(int j=x-1;j<=x+1;j++){
                    if(map[i][j]=='0'&&!aredy(i,j))reveal0(i,j);
                    else if(map[i][j]!='X'&&!aredy(i,j))reveal(i,j);
                }
            }
        }
        //upper center row
        else if(map[y][x]=='0'&&x>0&&x<9&&y==0){
            for(int i=y;i<=y+1;i++){
                for(int j=x-1;j<=x+1;j++){
                    if(map[i][j]=='0'&&!aredy(i,j))reveal0(i,j);
                    else if(map[i][j]!='X'&&!aredy(i,j))reveal(i,j);
                }
            }
        }
        //bottom center row
        else if(map[y][x]=='0'&&x>0&&x<9&&y==9){
            for(int i=y-1;i<=y;i++){
                for(int j=x-1;j<=x+1;j++){
                    if(map[i][j]=='0'&&!aredy(i,j))reveal0(i,j);
                    else if(map[i][j]!='X'&&!aredy(i,j))reveal(i,j);
                }
            }
        }
        //left center column
        else if(map[y][x]=='0'&&y>0&&y<9&&x==0){
            for(int i=y-1;i<=y+1;i++){
                for(int j=x;j<=x+1;j++){
                    if(map[i][j]=='0'&&!aredy(i,j))reveal0(i,j);
                    else if(map[i][j]!='X'&&!aredy(i,j))reveal(i,j);
                }
            }
        }
        //right center column
        else if(map[y][x]=='0'&&y>0&&y<9&&x==9){
            for(int i=y-1;i<=y+1;i++){
                for(int j=x-1;j<=x;j++){
                    if(map[i][j]=='0'&&!aredy(i,j))reveal0(i,j);
                    else if(map[i][j]!='X'&&!aredy(i,j))reveal(i,j);
                }
            }
        }
    }
}

void MAP::prntmap(){
    cout<<"#  A B C D E F G H I J"<<endl;
    cout<<"  ____________________"<<endl;
    for(int i=0;i<row;i++){
        cout<<i<<"|";
        for(int j=0;j<col;j++){
            cout<<setw(2)<<map[i][j];
        }
        cout<<endl;
    }
}
void MAP::prtindx(){
    cout<<"#  A B C D E F G H I J"<<endl; 
    cout<<"  ____________________"<<endl;
    for(int i=0;i<row;i++){
        cout<<i<<"|";
        for(int j=0;j<col;j++){
            cout<<setw(2)<<index[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}
bool MAP::aredy(int y,char x){
    if(map[y][x]==index[y][x])return true;
    return false;
}
MAP::~MAP(){
    for(int i=0;i<row;i++){
        delete map[i];
        delete index[i];
    }
    delete []map;
    delete []index;
}