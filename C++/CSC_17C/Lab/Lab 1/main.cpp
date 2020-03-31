/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on February 13, 2019, 7:40 PM
 * Purpose: Least Squares Technique
 */

//System Libraries Here
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>

using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //random seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare all Variables Here
    int size=181;       //number of data
    float fahr=0;       //Temperature in Fahrenheit
    float Cels=0;       //Temperature in Celsius
    float error=0;      //Margin of Error
    float valwerr=0;    //value of Celsius + Error
    float XX=0;         //F Temperature * F Temperature
    float XY=0;         //F Temperature * C Temperature
    float SumX=0;       //Sum of all temperature in Fahrenheit
    float SumY=0;       //Sum of all Temperature in Celsius
    float SumXY=0;      //Sum of all C Temperature * F Temperature
    float SumXX=0;      //Sum of all F Temperature * F Temperature
    float SumX2=0;      //Sum of all F Temperature squared
    float slope=0;      
    float B=0;          
    
    //output table format
    cout<<setprecision(2)<<showpoint<<fixed;
    cout<<setw(15)<<"Fahrenheit |"<<setw(15)<<"Celsius |"<<setw(15)<<"Error |"
            <<setw(21)<<"Celsius with error |"<<setw(15)<<"X*Y |"<<setw(15)
            <<"X*X |"<<endl;
    
    //Process/Calculations Here
    for(int i=32;i<size+32;i++){
        fahr=i;
        //Celsius=5/9*(Fahrenheit-32)  
        Cels=5/static_cast<float>(9)*(fahr-32);     
        //Random number from -10 to 10 with decimal
        error=rand()%20-10+(rand()%101/static_cast<float>(100)); 
        //Other calculations
        valwerr=error+Cels;       
        XY=fahr*valwerr;
        XX=fahr*fahr;
        //Sums of all values
        SumX+=fahr;
        SumY+=valwerr;
        SumXY+=XY;
        SumXX+=XX;
        //Output for table
        cout<<setw(13)<<fahr<<" |"<<setw(13)<<Cels<<" |"<<setw(13)<<error<<" |"
                <<setw(19)<<valwerr<<" |"<<setw(13)<<XY<<" |"<<setw(13)
                <<XX<<" |"<<endl;
    }
    //(SumX)^2, slope and B
    SumX2=SumX*SumX;
    slope=(SumY*SumX-size*SumXY)/(SumX2-size*SumXX);
    B=(SumY-slope*SumX)/size;
    //Final Output
    cout<<endl;
    cout<<"SumX     ="<<setw(15)<<SumX<<endl;
    cout<<"SumY     ="<<setw(15)<<SumY<<endl;
    cout<<"SumXY    ="<<setw(15)<<SumXY<<endl;
    cout<<"SumXX    ="<<setw(15)<<SumXX<<endl;
    cout<<"(SumX)^2 ="<<setw(15)<<SumX2<<endl;
    cout<<"Slope    ="<<setw(15)<<slope<<endl;
    cout<<"B        ="<<setw(15)<<B<<endl;
    //Exit
    return 0;
}