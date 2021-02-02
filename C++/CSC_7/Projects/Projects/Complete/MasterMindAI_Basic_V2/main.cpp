/*
    Guijosa I, David
    CSC 7 Template for Mastermind AI
    May 15th, 2019
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

//Function Prototypes
string AI(char,char);
bool eval(string,string,char &,char &);
string set();

int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare variables
    string code,guess;  //code to break, and current guess
    char rr,rw;         //right digit in right place vs. wrong place
    int nGuess;         //number of guesses
    
    //Initialize Values
    nGuess=0;
    code=set();
    rr=rw=0;
    //Loop until solved and count to find solution
    do{
       nGuess++;
       guess=AI(rr,rw);
    }while(eval(code,guess,rr,rw));
    //Check evaluation
    cout<<nGuess<<" "<<code<<" "<<guess<<endl;
    /*cout<<code<<endl;
    for(int i=0;i<10000;i++){
        guess=AI(0,0);
        eval(code,guess,rr,rw);
        cout<<setw(5)<<code<<setw(5)<<guess
                <<setw(2)<<static_cast<int>(rr)
                <<setw(2)<<static_cast<int>(rw)<<endl;
    }*/
    
    //Exit the program
    return 0;
}

string AI(char rr,char rw){
    static string code;     //4 characters in Code
    static char comb[4]; //24 Possible combinations of Code
    static int nrr=0;     //the possition of one of the 24 combinations
    static bool st=false;   //if the comvinations have been created
    static int CodeSz=4;    //lenght of code
    static int guess=0;     //guess number
    static string sGuess="0000";    //Guess to be return
    
    if(guess++!=0){
        if(code.size()<CodeSz){
            for(int i=0;i<rr;i++)code+=sGuess[0];    //adds an amount of character to the code
            for(int i=0;i<CodeSz;i++)sGuess[i]++;       //creates the next guess by increasing the last Guess
        }
        if(code.size()==CodeSz){              
            if(!st){
                for(int i=0;i<CodeSz;i++){
                    comb[i]=code[i];
                }
                st=true;
            }
            sGuess=comb[ncomb++];
        }
    }
    cout<<sGuess<<endl;                             //shows guesses
    return sGuess;

}

bool eval(string code,string guess,char &rr,char &rw){
    string check="    ";
    rr=0,rw=0;
    //Check how many are right place
    for(int i=0;i<code.length();i++){
        if(code[i]==guess[i]){
            rr++;
            check[i]='x';
            guess[i]='x';
        }
    }
    //Check how many are wrong place
    for(int j=0;j<code.length();j++){
        for(int i=0;i<code.length();i++){
            if((i!=j)&&(code[i]==guess[j])&&(check[i]==' ')){
                rw++;
                check[i]='x';
                break;
            }
        }
    }
    
    //Found or not
    if(rr==4)return false;
    return true;
}

string set(){
    string code="0000";
    for(int i=0;i<code.length();i++){
        code[i]=rand()%10+'0';
    }
    return code;
}