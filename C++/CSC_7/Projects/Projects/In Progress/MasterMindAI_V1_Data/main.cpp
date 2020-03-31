/*
    Dr. Mark E. Lehr
    CSC 7 Template for Mastermind AI
    November 1st, 2019
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <fstream>
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
    int cnt=0;
    code="8333";
    //code=set();
    //Loop until solved and count to find solution
        do{
           nGuess++;
           guess=AI(rr,rw);
        }while(eval(code,guess,rr,rw)&&cnt++<10);
        cout<<code<<endl;
    //Check evaluation
    //cout<<nGuess<<" "<<code<<" "<<guess<<endl;
    //guess=AI(rr,rw);
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
    //Define helper functions here
    void (*print)(string [],char [],char [],int,int)=
        [] (string g[],char r[],char w[],int nb,int ne){ 
            for(int i=nb;i<=ne;i++){
                cout<<g[i]<<" "
                    <<static_cast<int>(r[i])<<" "
                    <<static_cast<int>(w[i])<<endl;
            }
    };
    bool (*duplic)(string,char)=
        [] (string check,char number){ 
            for(int i=0;i<=check.size();i++){
                if(check[i]==number)return true;
            }
            return false;
    };
    bool (*inarr)(string ,string [],int)=
        [] (string search,string from[],int size){ 
            for(int i=0;i<size;i++){
                if(from[i]==search)return true;
            }
            return false;
    };
    //Save the historical values of guesses and results
    static const int SIZE=10000;//How many guesses to save
    static const int CodeSz=4;
    static string aGuess[SIZE]; //Save the guesses
    static char grr[SIZE];      //Save right guess in right spot
    static char grw[SIZE];      //Save right guess in wrong spot
    static int guess=0;         //Increment the guess number
    static bool tf=false;
    static int temp=0;
    static int temp2=0;
    static string op[SIZE];
    static string op2[SIZE];
    string sGuess="0011";       //Size the guest string
    
    //open file in turn 1
    if(guess==0){
        ifstream file;
        file.open("ALL.txt");
        int temp=0;
        while(file>>op[temp++]);
        for(int i=0;i<SIZE;i++)op2[i]=op[i];
        file.close();
    }
    //Test the helper function
    if(guess==10)print(aGuess,grr,grw,
            guess-10>0?guess-10:0,guess);
    //Calculate the guess
    if(guess!=0){
        for(int i=0;i<SIZE;i++){
            tf=false;
            if(op[i].size()!=1){
                for(int j=0;j<CodeSz;j++){
                    tf=duplic(op[i],aGuess[guess][j]);
                    if(tf)j=CodeSz;
                }
                if(tf&&rr+rw==0){
                    op[i]='\0';
                    temp2++;
                }
                else if(!tf&&rr+rw>0){
                    op[i]='\0';
                    temp2++;
                }
            }
        }
        char max,min;
        int pos;
        string psbans[CodeSz+1];
        bool chs[CodeSz+1];
        int points[CodeSz+1]={0,0,0,0};
        for(int i=0;i<SIZE;i++){
            for(int j=0;j<SIZE;j++){
                if(op[j].size()!=1&&i!=j){
                    max=0;
                    eval(op2[i],op[j],max,min);
                    pos=max+min;
                    points[pos]++;
                    if(!chs[pos]&&psbans[pos].size()!=4){
                        psbans[pos]=op2[i];
                    }
                    if(!chs[pos]&&inarr(op2[i],op,SIZE)){
                        psbans[pos]=op2[i];
                        chs[pos]=true;
                    }
                }
            }
        }
        pos=0;
        for(int i=1;i<CodeSz;i++){
            if(points[pos]>points[i])pos=i;
        }
        sGuess=psbans[pos];
    }

    //Store the results from the last guess
    grr[guess]=rr;
    grw[guess]=rw;
    aGuess[++guess]=sGuess; //Save the guesses
    //Return the result
    //if(guess==3)delete[]op;
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