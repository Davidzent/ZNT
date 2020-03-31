/* 
 * File:   main.cpp
 * Author: YOUR NAME HERE
 * Created on DATE AND TIME HERE
 * Purpose:  Sorting a 2-D array of characters if row and columns match
 * Note:  This time you create the strcmp() function that takes into
 * account the new sort order.
 */

//System Libraries Here
#include <iostream>//cin,cout
#include <cstring> //strlen(),strcmp(),strcpy()
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Allowed like PI, e, Gravity, conversions, array dimensions necessary
const int COLMAX=80;//Only 20 required, and 1 for null terminator

//Function Prototypes Here
int  read(char [][COLMAX],int &);//Outputs row and columns detected from input
void sort(char [][COLMAX],int,int,const char[],const char[]);//Sort by row using strcmp();
void print(const char [][COLMAX],int,int);//Print the sorted 2-D array
//int strcmp(char a[],char b[],char replace[],char with[]){
int strcmp(const string,const string);//Replace sort order

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int ROW=30;             //Only 20 required
    char array[ROW][COLMAX];      //Bigger than necessary 
    int colIn,colDet,rowIn,rowDet;//Row, Col input and detected
    char replace[COLMAX],with[COLMAX];//New sort order
    
    //Input the new sort order then sort
    cout<<"Modify the sort order by swapping these characters."<<endl;
    cin>>replace;
    cout<<"With the following characters"<<endl;
    cin>>with;
    cout<<"Read in a 2 dimensional array of characters and sort by Row"<<endl;
    cout<<"Input the number of rows <= 20"<<endl;
    cin>>rowIn;
    cout<<"Input the maximum number of columns <=20"<<endl;
    cin>>colIn;
    
    //Now read in the array of characters and determine it's size
    rowDet=rowIn;
    cout<<"Now input the array."<<endl;
    colDet=read(array,rowDet);
    
    //Compare the size input vs. size detected and sort if same
    //Else output different size
    if(rowDet==rowIn&&colDet==colIn){
        sort(array,rowIn,colIn,replace,with);
        cout<<"The Sorted Array"<<endl;
        print(array,rowIn,colIn);
    }else{
        if(rowDet!=rowIn)
        cout<<(rowDet<rowIn?"Row Input size less than specified.":
            "Row Input size greater than specified.")<<endl;
        if(colDet!=colIn)
        cout<<(colDet<colIn?"Column Input size less than specified.":
            "Column Input size greater than specified.")<<endl;
    }
    
    //Exit
    return 0;
}
int strcmp(const string str,const string str2){
    int cntstr=0,cntstr2=0;
    for(int i=0;str.size();i++){
        cntstr+=(static_cast<int>(str[i]))*10*str.size()-i;
    }
    for(int i=0;str2.size();i++){
        cntstr2+=static_cast<int>(str2[i])*10*str.size()-i;
    }
    return cntstr-cntstr2;
}
int  read(char a[][COLMAX],int &b){
    string c=a[0];
    int x,z;
    for(int i=0;i<b;i++){
        cin>>a[i]; 
    }
    for(int i=0;i<b;i++){
        x=0;z=0;
        c=a[i];
        x=c.size();
        x>z?z=x:x;
    }
    return z;
}
void sort(char a[][COLMAX],int row,int col,const char replace[],const char with[]){
    string str=replace;
    string str2=with;
    int size=str.size();
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            for(int x=0;x<size;x++)
            if(a[i][j]==replace[x])a[i][j]=with[x],x=size;
        }
    }
    int ret=0;
    for(int i=0;i<row-1;i++){
        ret=strcmp(a[i],a[i+1]);
        if(ret<0){
            string temp=a[i];
            string temp2=a[i+1];
            for(int j=0;j<col;j++){
                a[i][j]=temp2[j];
                a[i+1][j]=temp[j];
            }
            i=0;
        }
    }
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            for(int x=0;x<size;x++)
            if(a[i][j]==with[x])a[i][j]=replace[x],x=size;
        }
    }
}
void print(const char a[][COLMAX],int row,int col){
    string str[row];
    for(int i=row-1;i>=0;i--){
        str[i]=a[i];
        cout<<str[i]<<endl;
    }
}




