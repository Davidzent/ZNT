
#include "Triangular Matrix.h"

TrgMtrx::TrgMtrx(){
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    max=0;
    min=0;
    size=0;
}
TrgMtrx::TrgMtrx(int size){
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    this->size=size;
    //Create the 2-D allocated pointer
    array=new int*[size];
    for(int row=0;row<size;row++){
        array[row]=new int[row+1];
    }
}
TrgMtrx::TrgMtrx(int size,int max,int min){
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    this->size=size;
    //Create the 2-D allocated pointer
    array=new int*[size];
    for(int row=0;row<size;row++){
        array[row]=new int[row+1];
    }
    this->max=max;
    this->min=min;
}
TrgMtrx::~TrgMtrx(){
    for(int row=0;row<size;row++){
        delete []array[row];
    }
    delete []array;
}
void TrgMtrx::prntAry(){
    cout<<endl;
    for(int row=0;row<size;row++){
        for(int col=0;col<row;col++){
            cout<<array[row][col]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;
}
void TrgMtrx::SetVal(int row,int col){
    int val;
    do{
    //input one value
    cout<<"input a value to test the range"<<endl;
    cin>>val;
    if(val<max&&val>min)array[row][col]=val;
    else cout<<"This value is out of range"<<endl;
    }while(array[row][col]!=val);
}
void TrgMtrx::SetRVal(){
    //Fill the array with values
    for(int row=0;row<size;row++){
        for(int col=0;col<row;col++){
            array[row][col]=rand()%max+min;
        }
    }
}
void TrgMtrx::setRVal(int row,int col){
     array[row][col]=rand()%max+min;
}
void TrgMtrx::SetRng(int max,int min){
    this->max=max;
    this->min=min;
}