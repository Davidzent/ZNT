/*
Guijosa David
Mastermind AI
November 11th, 2019
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
    int cnt=0;
    //Initialize Values
    nGuess=0;
    code=set();
    rr=rw=0;
    //code="7038";
    //Loop until solved and count to find solution
    do{
       nGuess++;
       guess=AI(rr,rw);
    }while(eval(code,guess,rr,rw)&&++cnt<10);
    //Check evaluation
    cout<<nGuess<<" "<<code<<" "<<guess<<endl;
    guess=AI(rr,rw);
    //cout<<code<<endl;
    /*for(int i=0;i<10000;i++){
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
     bool (*duplic)(int[],int,int)=
        [] (int data[],int size,int number){ 
            for(int i=0;i<=size;i++){
                if(data[i]==number)return true;
            }
            return false;
    };
    bool (*cont)(string[],int guess)=
        [] (string check[],int guess){ 
            if(guess<1)return false;
            if(check[guess-1][2]==check[guess][0])return true;
            return false;
    };
    //Save the historical values of guesses and results
    static const int SIZE=10000;//How many guesses to save
    static string aGuess[SIZE]; //Save the guesses
    static char grr[SIZE];      //Save right guess in right spot
    static char grw[SIZE];      //Save right guess in wrong spot
    static int guess=0;         //Increment the guess number
    static const int CodeV=10;
    static const int CodeSz=4;
    static int stats[CodeV];
    string sGuess="0011";       //Size the guest string
    //Test the helper function
    if(guess==10){
        print(aGuess,grr,grw,guess-10>0?guess-10:0,guess);
    }
    //Store the results from the last guess
    grr[guess]=rr;
    grw[guess]=rw;
    if(guess!=0){
        if(rw+rr==4){
            
        }
        else{
                    for(int i=0;i<CodeV;i++){
            cout<<stats[i]<<" ";
        }
                    cout<<endl;
            if(rr+rw>0){
                for(int i=0;i<CodeSz;i++){
                    stats[aGuess[guess][i]-'0']+=(2*(rw+rr));
                }
                for(int i=0;i<CodeV;i++){
                    if(stats[i]>0)stats[i]-=(rw+rr);
                }
            }
            else {    
                for(int i=0;i<CodeV;i++){
                    stats[aGuess[guess][i]-'0']=0;
                }
            }
            int temp=0;
            bool t=false;
            sGuess='\0';
            for(int i=0;i<CodeV;i++){
                t=false;
                if(temp>1){
                    for(int j=0;j<CodeV;j++){
                        if(stats[j]==stats[sGuess[temp]-'0']&&j!=sGuess[temp]-'0'){
                            t=true;
                        }
                    }
                }
                
                if(!t&&stats[i]!=0&&temp<4){
                    for(int k=1;k<=guess;k++){
                        cout<<"here: "<<aGuess[k]<<" guess: "<<guess<<" | "<<aGuess[k][temp]<<" "<<i;
                            if(aGuess[k][temp]==(i+'0')){
                                cout<<" yes";
                                t=true;
                            }
                        cout<<endl;
                    }
                    if(!t){
                        sGuess+=i+'0';
                        temp++;
                    }
                }
            }
            int temp3=0;
            cout<<sGuess<<endl;
            while(temp<4){
                temp3++;
                for(int i=0;i<CodeV;i++){
                    t=false;
                    for(int k=1;k<=guess;k++){
                        //cout<<"here: "<<aGuess[k]<<" guess: "<<guess<<endl;
                            if(aGuess[k][temp]==(i+'0')){
                                t=true;
                            }
                    }
                    if(!t&&stats[i]!=0&&temp<4){
                        sGuess+=i+'0';
                        temp++;
                    }
                } 
                if(temp3>11){
                     print(aGuess,grr,grw,guess-10>0?guess-10:0,guess);
                    exit(0);
                }
            }
            //cout<<sGuess<<endl;
        }
    }
    else{
        for(int i=0;i<CodeV;i++){
            stats[i]=(100/CodeV);
        }
    }
    
    
    aGuess[++guess]=sGuess;//Save the result
    //Return the result
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