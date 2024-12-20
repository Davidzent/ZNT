/* 
 * File:   main.cpp
 * Author: YOUR NAME HERE
 * Created on DATE AND TIME HERE
 * Purpose:  Searching for multiple occurrence of patterns
 * Note:  cout proceeds to null terminator, cin reads to end of line
 *        for character arrays
 * 
 */

//System Libraries Here
#include <iostream>//cin,cout,getline()
#include <cstring> //strlen()
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//PI, e, Gravity, or conversions

//Function Prototypes Begins Here
//srch1 utility function Input->start position, Output->position found or not
//srch1 is a simple linear search function, repeat in srchAll till all found
//srch1 Input->sentence, pattern, start position Output-> position found
//Remember arrays start at index/position 0
//srchAll Input->sentence, pattern Output->position array
int  srch1(const char [],const char [],int);//Search for 1 occurrence
void srchAll(const char [],const char [],int []);//Search for all occurrences
void print(const char []);//Print the character arrays
void print(const int []); //Print the array of indexes where the pattern found

//Program Execution Begins Here
int main(int argc, char** argv) {
    //Declare all Variables Here
    const int LINE=81;               //Size of sentence or pattern to find
    char sntnce[LINE],pattern[LINE]; //80 + null terminator
    int match[LINE];                 //Index array where pattern was found
    for (int i=0;i<LINE;i++){
        match[i]=0;
    }
    //Input a sentence and a pattern to match
    cout<<"Match a pattern in a sentence."<<endl;
    cout<<"Input a sentence"<<endl;
    cin.getline(sntnce,LINE);
    cout<<"Input a pattern."<<endl;
    cin.getline(pattern,LINE);
    
    //Search for the pattern
    //Input the sentence and pattern, Output the matching positions
    //Remember, indexing starts at 0 for arrays.
    srchAll(sntnce,pattern,match);
    
    //Display the inputs and the Outputs
    cout<<endl<<"The sentence and the pattern"<<endl;
    print(sntnce);
    print(pattern);
    cout<<"The positions where the pattern matched"<<endl;
    print(match);
    
    //Exit
    return 0;
}
int  srch1(const char a[],const char b[],int c){
    string str=a,str2=b;
    int size=str.size();
    int size2=str2.size();
    int cnt=0;
    for(int i=0,j=c;i<size2;i++,j++){
        if(a[j]==b[i])cnt++;  
        else return 0;
    }
    return c+1;
}
void srchAll(const char a[],const char b[],int c[]){
    string str=a,str2=b;
    int size=str.size();
    int size2=str2.size();
    int repeat=size-size2+1;
    for(int i=0;i<repeat;i++){
        if(a[i]==b[0])c[i]=srch1(a,b,i);
    }
}
void print(const char a[]){
    cout<<a<<endl;
}
void print(const int a[]){
    int cnt=0;
    for(int i=0;i<81;i++){
        if(a[i]!=0)cout<<a[i]-1<<endl;
        else cnt++;
    }
    if(cnt==81)cout<<"None"<<endl;
}