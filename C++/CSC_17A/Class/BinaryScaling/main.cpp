/*
 * Dr. Mark E. Lehr
 * Created on September 24, 2018, 12:38 PM
 * Purpose:  Scaling
*/

//System Libraries
#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace std;

//User Libraries

//Global Constants  Never use unless Physical/Mathematical/Conversion

//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    //Normal Calculation
    int xn=19;
    float mn=5.0f/9.0f;
    float resultn=xn*mn;
    cout<<resultn<<endl;
    
    //Scaling 
    unsigned char x=xn;//1 Byte number
    unsigned char m=0x8E;//5/9 X 16^-2
    unsigned short result=m*x;
    result>>=8;
    cout<<result<<endl;
    
    //Scaling 
    x=xn;//1 Byte number
    m=043;//5/9 x 8^-2
    result=m*x;
    result>>=6;
    cout<<result<<endl;
    
    //Scaling 
    x=xn;//1 Byte number
    m=0b10001110;//5/9 x 8^-2
    result=m*x;
    bool rndup=(1&(result>>7))?1:0;
    cout<<rndup<<endl;
    result>>=8;
    cout<<result+rndup<<endl;
    
    
    return 0;
}