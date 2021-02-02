/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on April 1, 2018, 11:00 AM
 * Purpose:  This is a modification of the math tutor Programming Challenge problem in Chapter 3.
             Write a program that can be used as a math tutor for a young student . The program
             should display two random numbers between 10 and 50 that are to be added, such as:
             24
           + 12
             The program should then wait for the student to enter the answer. If the answer is
             correct, a message of congratulat ions should be printed. If the answer is incorrect, a
             message should be printed showing the correct answer.
 */

//System Libraries Here
#include <iostream> 
#include <cstdlib>
#include <ctime>    //time to set random number
#include <iomanip>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here

//Program Execution Begins Here
int main(int argc, char** argv) {
    //set the random number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare all Variables Here
    float op1, op2, stuAns, Correct;

    //Input or initialize values Here
    op1=rand()%40+10; //[10,50]
    op2=rand()%40+10; //[10,50]
    cout<<"This is a simple Math tutor Program"<<endl;
    cout<<"input the Answer to the following edition problem"<<endl;
    cout<<setw(5)<<op1<<endl;
    cout<<"+"<<setw(4)<<op2<<endl;
    cout<<"-----"<<endl;

    //Calculate the answer
    Correct=op1+op2;
    cout<<((Correct>=100)?" ":"   ");
    cin>>stuAns;

    //Output Located Here
    cout<<endl<<(stuAns==Correct?"Correct Answer":"Wrong Answer")<<endl;
    if(stuAns!=Correct)cout<<"The correct answer is "<<Correct<<endl;
    
    //Exit
    return 0;
}

