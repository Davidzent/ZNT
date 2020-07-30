/* 
 * File:   
 * Author: David Guijosa
 * Created on 
 * Instructions: 
     * A liter is 0.264179 gallons. 
     * Write a program that will read in the number of liters of gasoline consumed by the user’s car 
     * and the number of miles traveled by the car and will then output the number of miles per gallon the car delivered. 
     * Your program should allow the user to repeat this calculation as often as the user wishes. 
     * Define a function to compute the number of miles per gallon. 
     * Your program should use a globally defined constant for the number of liters per gallon.
     * Modify your program from Sav9EdC4P1 so that it will take input data for two cars
     * and output the number of miles per gallon delivered by each car. 
     * Your program will also announce which car has the best fuel efficiency (highest number of miles per gallon).
 */

//System Libraries
#include <iostream>  //Input/Output Library
#include <iomanip>
using namespace std;

//User Libraries

//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...
float LitTGal = 0.264179;   //Litter to gallon

//Function Prototypes

//Execution Begins Here!
int main(int argc, char** argv) {
    //Set the random number seed
    
    //Declare Variables
    float litter,       //number of liters of gasoline consumed by the car
          miles,        //number of miles traveled by the car
          mlPgal,       //number of miles per gallon for car1
          mlPgal2;      //number of miler per gallon for car2
    
    char  again;        
    
    
    //Manipulate output
    cout<<fixed<<showpoint<<setprecision(2);
    do{
        //Initialize or input i.e. set variable values
        cout<<"Car 1"<<endl;
        cout<<"Enter number of liters of gasoline:\n";
        cin>>litter;
        cout<<"Enter number of miles traveled:\n";
        cin>>miles;
        
        //Calculations
        mlPgal = miles/(litter*LitTGal);
        
        //Display the outputs
        cout<<"miles per gallon: "<<mlPgal<<endl<<endl;  
        
        //Initialize or input i.e. set variable values
        cout<<"Car 2"<<endl;
        cout<<"Enter number of liters of gasoline:\n";
        cin>>litter;
        cout<<"Enter number of miles traveled:\n";
        cin>>miles;
        
        //Calculations
        mlPgal2 = miles/(litter*LitTGal);
        
        //Display the outputs
        cout<<"miles per gallon: "<<mlPgal2<<endl<<endl;  
        cout<<"Car "<<(mlPgal>mlPgal2?1:2)<<" is more fuel efficient\n\n";
        cout<<"Again:\n";           
        cin>>again;                 
        again>='a'?again-=32:again; //to uppercase 
    }while(again=='Y'&&cout<<endl); //Extra end of the line if the user wants to continue
    
    //Exit stage right or left!
    return 0;
}