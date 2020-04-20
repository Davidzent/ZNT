/* 
 * File:   player.h
 * Author: David guijosa
 *
 * Created on November 23, 2018, 2:24 PM
 */

#include <cstdlib>
#include <ctime>
#include "Maps.h"
#include "painter.hpp"
#include <iostream>
#include <iomanip>
using namespace std;

MAP::MAP(){ 
    //set all values to 0
    row=40;
    col=40;
    nmines=10;
}
MAP::MAP(int row,int col){ 
    // set values to corresponding row and columns
    this->row=row;
    this->col=col;
}
void MAP::setrow(int row){
    //set the value of the rows in the map
    this->row=row;
}
void MAP::setcol(int col){
    //set the value of columns in the map
    this->col=col;
}
void MAP::setnmin(int nmines){
    //set the number of mines in the map
    this->nmines=nmines;
}
int MAP::getcol()const{
    //returns the number of columns in the game
    return col;
}
int MAP::getrow()const{
    //returns the number of rows in the map
    return row;
}
int MAP::getnmin() const{
    //returns the number of mines in the map
    return nmines;
}
/*Cell MAP::getcord(int y, int x){
    //returns a value in a certain coordinate
    return field_[y][x];
}*/
int MAP::gtmoves() const{
    //returns the number moves
    return moves;
}
void MAP::prntmap(){
    cout<<"#  A B C D E F G H I J"<<endl;
    cout<<"  ____________________"<<endl;
    for(int i=0;i<row;i++){
        cout<<i<<"|";
        for(int j=0;j<col;j++){
            cout<<setw(2)<<field_[j][i].value;
        }
        cout<<endl;
    }
    cout<<"#  A B C D E F G H I J"<<endl;
    cout<<"  ____________________"<<endl;
    for(int i=0;i<row;i++){
        cout<<i<<"|";
        for(int j=0;j<col;j++){
            cout<<setw(2)<<field_[j][i].state;
        }
        cout<<endl;
    }
}
void MAP::shufle(){ 
    for(int nShuf=0;nShuf<=7;nShuf++){
        for(int i=0;i<row;i++){
            for (int j=0;j<col;j++){
                int random=rand()%row;
                int random2=rand()%col;
                Cell temp=field_[i][j];
                field_[i][j]=field_[random][random2];
                field_[random][random2]=temp;
            }        
        }
    }
}
void MAP::cntmine(){
    for(int i=0;i<row;i++){
        for (int j=0;j<col;j++){
            if(field_[i][j].hasMine){
                for(int y=i-1;y<=i+1;y++){
                    for(int x=j-1;x<=j+1;x++){
                        if((x>=0&&y>=0)&&(x<row&&y<col)&&!(field_[y][x].hasMine)){
                            field_[y][x].value++;
                        }
                    }
                }
            }
        }
    }
}

void MAP::crtmap(){   
    //dynamically creates field_s
    field_=new Cell*[row];
    for(int i=0;i<row;i++){
        field_[i]=new Cell[col];
    }
    for(int i=0,x=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(x<nmines){
                field_[i][j].value='X';
                field_[i][j].hasMine=true;
                x++;
            }
            else {
                field_[i][j].value='0';
                field_[i][j].hasMine=false;
            }
        }
    }
    //shuffle field_ mines
    shufle();
    
    //count surrounding mines for non-mines
    cntmine();
    prntmap();
    moves=(row*col)-nmines;
}
void MAP::draw(){
    Painter p;
    for (int y = 0; y < row; ++y){
        for (int x = 0; x < col; ++x){
            switch (field_[y][x].state){
                case CLOSED:
                    p.drawClosedField(y, x);
                    break;
                case OPENED:
                    if (!field_[y][x].hasMine){
                        p.drawOpenedField(y, x, field_[y][x].value);
                    }
                    else
                        p.drawMine(y, x);
                    break;
                case FLAG:
                    p.drawFlag(y, x);
                    break;
            }
        }
    }
}
void MAP::open(int y, int x){
    if(field_[y][x].value=='0'&&field_[y][x].state==CLOSED){
        field_[y][x].state = OPENED;
        for(int i=y-1;i<=y+1;i++){
            for(int j=x-1;j<=x+1;j++){
                if((j>=0&&i>=0)&&(i<row&&j<col)&&!field_[i][j].hasMine){
                    open(i,j);
                }
            }
        }
    }
    else field_[y][x].state = OPENED;
    moves--;
}
void MAP::mark(int x, int y){
    switch (field_[x][y].state){
        case OPENED:
            break;
        case CLOSED:
            field_[x][y].state = FLAG;
            break;
        case FLAG:
            field_[x][y].state = CLOSED;
            break;
    }
}
MAP::~MAP(){
    for(int i=0;i<row;i++)delete field_[i];
    delete []field_;
}