/* 
 * File:   Class Map.h
 * Author: David Guijosa
 *
 * Created on November 15, 2018, 11:19 AM
 */

#include "Class Map.h"
#include <iomanip>
#include "Show Map.h"
MAP::MAP(){
    row=0;
    col=0;
}
MAP::MAP(int row,int col){
    this->row=row;
    this->col=col;
    crtmap();
}
void MAP::crtmap(){
    ctmap=true;
    map=new char*[row];
    for(int i=0;i<col;i++){
        map[i]=new char[col];
    }
}
int MAP::getcol(){
    return col;
}
int MAP::getrow(){
    return row;
}
void MAP::setcol(int col){
    this->col=col;
}
void MAP::setrow(int row){
    this->row=row;
}
void MAP::getcord(int y,char x){
    HIDE hide;
    do{
        cout<<"input the coordinate you want to reveal"
                <<endl;
        cin>>x>>y;
        if(x>=65&&x<=74)x-=65;
        else if(x>=97&&x<=106)x-=97;
        if(map[y][x]==hide.getval(y,x))cout<<"Input a new "
                "coordinate"<<endl;
        }while(map[y][x]==hide.getval(y,x)||x<0||x>9||y<0||y>9);
}

void MAP::flmap(int nmines){
    if(ctmap=false)crtmap();
    int cnt=1;
    int shfl=7;
    for(int i=0;i<row;i++,cnt++){
        for(int j=0;j<col;j++,cnt++){
            if(cnt<=nmines){map[i][j]='X';}
            else {map[i][j]='0';}
        }
    }
    //move mines to random places map
    shufle();
    //number of mines around a non-mine
    cntmine();
}
void MAP::cntmine(){
    for(int j=0;j<row;j++){
        for (int i=0;i<col;i++){
            if(map[i][j]=='X'&&i!=0&&j!=0&&i!=9&&j!=9){
                for(int x=i-1;x<i+1;x++){
                    for(int y=j-1;y<=j+1;y++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }  
            }
            else if(map[i][j]=='X'&&i==0&&j==0){ //non-mine counter for the
                for(int x=i;x<i+1;x++){
                    for(int y=j;y<=j+1;y++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&i==9&&j==9){ //non-mine counter for the
                for(int x=i-1;x<i;x++){
                    for(int y=j-1;y<=j;y++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&i==0&&j==9){   //non-mine counter for 
                for(int x=i;x<i+1;x++){
                    for(int y=j-1;y<=j;y++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&i==9&&j==0){  //non-mine counter for 
                for(int x=i-1;x<i;x++){
                    for(int y=j;y<=j+1;y++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&i==0&&j>0&&j<9){   //non-mine counter for
                for(int x=i;x<i+1;x++){
                    for(int y=j-1;y<=j;y++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&i==9&&j>0&&j<9){//non-mine counter for the
                for(int x=i-1;x<i;x++){
                    for(int y=j-1;y<=j+1;y++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&j==0&&i>0&&i<9){   //non-mine counter for 
                for(int x=i-1;x<i+1;x++){
                    for(int y=j;y<=j+1;y++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
            else if(map[i][j]=='X'&&j==9&&i>0&&i<9){   //bottom corner line
                for(int x=i-1;x<i+1;x++){
                    for(int y=j-1;y<=j;y++){
                        if(map[y][x]!='X')map[y][x]++;
                    }
                }
            }
        }
    }
}
void MAP::shufle(){
    for(int shfl=1;shfl<7;shfl++){
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
MAP::~MAP(){
    for(int i=0;i<col;i++){
        delete map[i];
    }
    delete []map;
}
char MAP::getval(int y,char x){
    return map[y][x];
}
istream &operator >>(istream&strm,MAP&obj){
    cout<<"Number of rows"<<endl;
    strm>>obj.row;
    cout<<"Number of colum"<<endl;
    strm>>obj.col;
    obj.crtmap();
    obj.ctmap=true;
}
ostream &operator <<(ostream&strm, MAP&obj){
    strm<<"#  A B C D E F G H I J"<<endl;
    strm<<"  ____________________"<<endl;
    for(int i=0;i<obj.row;i++){
        strm<<i<<"|";
        for(int j=0;j<obj.col;j++){
            strm<<setw(2)<<obj.map[i][j];
        }
        strm<<endl;
    }
}
