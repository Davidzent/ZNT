//This code counts the number of characters in the string.


// Adli Garniwan
// CIS 5 49258
// 11/28/2020

#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

int numChar(char[],int);

int main()
{
    char answer[50];
    
    
    cout<<"Please enter a c-string no longer than 50 characters." << endl;
    cin.getline(answer,50);
    
    
    
    cout<<"The string you entered has " << (numChar(answer,50))<< " words!" << endl;
    
    return 0;
    
}

int numChar(char ptr[],int size)
{
    int cnt=1;
    for(int i=0;i<size-1;i++){
        if(ptr[i]==' '&&((ptr[i+1]<='z'&&ptr[i+1]>='a')||(ptr[i+1]<='Z'&&ptr[i+1]>='A'))){
            cnt++;
        }
    }
    return cnt;
}
