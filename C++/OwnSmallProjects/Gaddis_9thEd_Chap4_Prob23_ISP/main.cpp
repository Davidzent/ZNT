/* 
 * File:   main.cpp
 * Author: David Guijosa
 * Created on July 20, 2019, 12:36 PM
 * Instructions:  
    * An Internet service provider has three different subscription packages for its customers:
    * Package A: For $9.95 per month 10 hours of access are provided. Additional hour
    * are $2.00 per hour.
    * Package B: For $14.95 per month 20 hours of access are provided. Additional hours
    * are $1.00 per hour.
    * Package C: For $19.95 per month unlimited access is provided.
    * Write a program that calculates a customer’s monthly bill. It should ask which package
    * the customer has purchased and how many hours were used. It should then display
    * the total amount due.
    * Input Validation: Be sure the user only selects package A, B, or C. Also, the number
    * of hours used in a month cannot exceed 744.
 * -*- = possible changes
 */

//System Libraries
#include <iostream>  //Input/Output Library
using namespace std;

//User Libraries

//Global Constants, no Global Variables are allowed
//Math/Physics/Conversions/Higher Dimensions - i.e. PI, e, etc...

//Function Prototypes
float calbill(float,float,float,float);

//Execution Begins Here!
int main(int argc, char** argv) {
    //Set the random number seed
    
    //Declare Variables
    float baseA=9.95f,      //Plan A base cost
          baseB=14.95f,     //Plan B base cost
          baseC=19.95f,     //Plan C base cost
          extraA=2.00f,     //Plan A extra cost per hour
          extraB=1.00f;     //Plan B extra cost per hour
          
    float bill=0;       //bill cost
    float hrs;          //inputed hours
    char type;          //Plan Type
    
    //Initialize or input i.e. set variable values
    cout<<"ISP Bill\n";
    cout<<"Input Package and Hours\n";
    cin>>type>>hrs;
    
    //Map inputs -> outputs
    type>='a'?type-=32:type;    //Convert input to uppercase
    
    // -*- there is no input validation test case for either the hours exceeding 744 or the package being other than A, B or C
    
    if(hrs<=744){                               // -*- Input Validation for hours (You get full credit even if you don't have this)
        if(type=='A'){                          
            bill=calbill(hrs,10,baseA,extraA);  
        }else if(type=='B'){                    
            bill=calbill(hrs,20,baseB,extraB);  
        }
        else if(type=='C'){                     // -*- there should be an extra test case to check for Input Validation (it works even if there is an else not an else if).                  
            bill=baseC;                         
        }
    }
    
    //Display the outputs
    cout<<"Bill = $ "<<bill;
    
    //Exit stage right or left!
    return 0;
}

float calbill(float inhrs,float hrs,float base,float extra){
    float bill=0;
    bill+=base;
    if(inhrs>hrs){
        int temp;
        temp = inhrs-=hrs;
        bill+=temp*extra;   
        inhrs-=temp;        
        if(inhrs>0){        // -*- count partial hours like full hours 
            bill+=extra;    // -*- (There is no test case to check this Neither the instructions say it
                            // -*- but I thought it would be interesting)
        }
        
    }
    return bill;
}