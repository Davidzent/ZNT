/* 
 * File:   Show Map.cpp
 * Author: David Guijosa
 *
 * Created on November 15, 2018, 11:41 AM
 */
#include "Show Map.h"
HIDE::HIDE(){
    row=0;
    col=0;
}
HIDE::HIDE(int row, int col){
    this->row=row;
    this->col=col;
}
void HIDE::fillmap(){
    crtmap();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            map[i][j]='?';
        }
    }
}
void HIDE::reveal(int y,char x){
    MAP val;
    map[y][x]=val.getval(y,x);
}
void HIDE::reveal0(int x,char y){
    //left upper
    if(map[x][y]=='0'&&x==0&&y==0){
        for(int i=y;i<=y+1;i++){
            for(int j=x;j<=x+1;j++){
                if(map[i][j]!='X')reveal(j,i);
            }
        }
    }
    //right bottom
    else if(map[x][y]=='0'&&x==9&&y==9){
        for(int i=y-1;i<=y;i++){
            for(int j=x-1;j<=x;j++){
                if(map[i][j]!='X')reveal(j,i);
            }
        }
    }
    //right upper
    else if(map[x][y]=='0'&&x==0&&y==9){
        for(int i=y-1;i<=y;i++){
            for(int j=x;j<=x+1;j++){
                if(map[i][j]!='X')reveal(j,i);
            }
        }
    }
    //left bottom
    else if(map[x][y]=='0'&&x==9&&y==0){
        for(int i=y;i<=y+1;i++){
            for(int j=x-1;j<=x;j++){
                if(map[i][j]!='X')reveal(j,i);
            }
        }
    }
    //center
    else if(map[x][y]=='0'&&x>0&&y>0&&x<9&&y<9){
        for(int i=y-1;i<=y+1;i++){
            for(int j=x-1;j<=x+1;j++){
                if(map[i][j]!='X')reveal(j,i);
            }
        }
    }
    //upper center row
    else if(map[x][y]=='0'&&x>0&&x<9&&y==0){
        for(int i=y;i<=y+1;i++){
            for(int j=x-1;j<=x+1;j++){
                if(map[i][j]!='X')reveal(j,i);
            }
        }
    }
    //bottom center row
    else if(map[x][y]=='0'&&x>0&&x<9&&y==9){
        for(int i=y-1;i<=y;i++){
            for(int j=x-1;j<=x+1;j++){
                if(map[i][j]!='X')reveal(j,i);
            }
        }
    }
    //left center column
    else if(map[x][y]=='0'&&y>0&&y<9&&x==0){
        for(int i=y-1;i<=y+1;i++){
            for(int j=x;j<=x+1;j++){
                if(map[i][j]!='X')reveal(j,i);
            }
        }
    }
    //right center column
    else if(map[x][y]=='0'&&y>0&&y<9&&x==9){
        for(int i=y-1;i<=y+1;i++){
            for(int j=x-1;j<=x;j++){
                if(map[i][j]!='X')reveal(j,i);
            }
        }
    }
}