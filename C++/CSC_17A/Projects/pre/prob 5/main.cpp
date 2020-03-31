/* 
 * File:   main.cpp
 * Author: Guijosa David
 * Created on 06/07/2018
 * Purpose:  Even, Odd Vectors and Array Columns Even, Odd
 * Note:  Check out content of Sample conditions in Hacker Rank
 * Input size of integer array, then array, output columns of Even, Odd
 * Vectors then Even, Odd 2-D Array
 */

//System Libraries Here
#include <iostream>//cin,cout
#include <vector>  //vectors<>
#include <iomanip> //Format setw(),right
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Allowed like PI, e, Gravity, conversions, array dimensions necessary
const int COLMAX=2;//Only 2 columns needed, even and odd

//Function Prototypes Here
void read(vector<int> &, vector<int> &);
void copy(vector<int>, vector<int>,int [][COLMAX]);
void prntVec(vector<int>, vector<int>,int);//int n is the format setw(n)
void prntAry(const int [][COLMAX],int,int,int);

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int ROW=80;           //No more than 80 rows
    int array[ROW][COLMAX];     //Really, just an 80x2 array, even vs. odd
    vector<int> even(0),odd(0); //Declare even,odd vectors
    
    //Input data and place even in one vector odd in the other
    read(even,odd);
    
    //Now output the content of the vectors
    //          setw(10)
    prntVec(even,odd,10);//Input even, odd vectors with setw(10);
    
    //Copy the vectors into the 2 dimensional array
    copy(even,odd,array);
    
    //Now output the content of the array
    //                              setw(10)
    prntAry(array,even.size(),odd.size(),10);//Same format as even/odd vectors
    
    //Exit
    return 0;
}
void read(vector<int> &even, vector<int> &odd){
    int SIZE;
    cout<<"Input the number of integers to input."<<endl;
    cin>>SIZE;
    cout<<"Input each number."<<endl;
    int arr[SIZE];
    for(int i=0;i<SIZE;i++){
        cin>>arr[i];
        if(arr[i]%2==0)even.push_back(arr[i]);
        else odd.push_back(arr[i]);
    }
}
void prntVec(vector<int> even, vector<int> odd,int c){
    int a=even.size(),
        b=odd.size();
    cout<<setw(c)<<"Vector"<<setw(c)<<"Even"<<setw(c)<<"Odd"<<endl;
    for (int i=0;i<a||i<b;i++){
        if(i<a&&i<b)cout<<setw(2*c)<<even[i]<<setw(c)<<odd[i]<<endl;
        else if(i>=a&&i<b)cout<<setw(3*c)<<odd[i]<<endl;
        else if(i>=b&&i<a)cout<<setw(2*c)<<even[i]<<endl;
    }
}
void copy(vector<int> even, vector<int> odd,int arr[][COLMAX]){
    for (int j=0;j<odd.size();j++){
        arr[j][1]=odd[j];
    }
    for (int j=0;j<even.size();j++){
        arr[j][0]=even[j];
    }
}
void prntAry(const int arr[][COLMAX],int a,int b,int c){
    cout<<setw(c)<<"Array"<<setw(c)<<"Even"<<setw(c)<<"Odd"<<endl;
    
    for(int j=0;j<a||j<b;j++){
        if(j<a&&j<b)cout<<setw(2*c)<<arr[j][0]<<setw(c)<<arr[j][1]<<endl;
        else if(j>=a&&j<b)cout<<setw(3*c)<<arr[j][1]<<endl;
        else if(j>=b&&j<a)cout<<setw(2*c)<<arr[j][0]<<endl;
    }
}
