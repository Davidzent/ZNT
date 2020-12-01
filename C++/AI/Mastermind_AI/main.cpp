
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <ctime>
using namespace std;


//Creates a random answer
vector<int> crtAns(const int &, const int &);

//Checks user guess to the answer
string ChckAns(vector<int>, vector<int>, const int &);

//Creates the set of possible answers
void crtSet(vector<vector<int>> &, const int &, const int &);

//Creates the possible Master recursively
void crtComb(vector<vector<int>> &,vector<int> &, vector<int> &, const int &, int);

//Removes from the possible Master the code that was used as a guess 
void RmvCode(vector<vector<int>> &, vector<int>);

//Remove from candidateSolutions,
//any code that would not give the same response if it were the code
void PrnCode(vector<vector<int>> &, vector<int>, string, const int &);      //PruneCodes

//Calculate min and max scores
vector<vector<int>> minmax(vector<vector<int>>&, vector<vector<int>>&, const int &);

//Generates next guess based on the minmax
vector<int> getNxGuess(vector<vector<int>> &, vector<vector<int>>, vector<vector<int>>&);

//Get the Maximum score
int getMaxS(map<string, int>);

//Get the Minimum score
int getMinS(map<vector<int>, int>);

int main() {
    //Random seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Variables
    const int CodeSz = 4;           //Size of the Code to solve
    const int nColour = 6;          //Number of variants to choose from 
    vector<int> code;               //Code to solve
    vector<vector<int>> PosAns;     //Array of possible answers
    vector<vector<int>> Master;     //Master set of Combinations
    vector<vector<int>> nxGuess;    //Next Guess
    vector<int> Guess;              //Current Guess
    string Pegs;                    //Response to the guess
    int turn = 1;                   //Current turn
    bool won = false;               //Is the game still playing

    //Create Random Code
    code = crtAns(nColour,CodeSz);  
    Guess = {1, 1, 2, 2};           //Generic Start

    //Create the set of nColour^CodeSz possible codes
    crtSet(Master,nColour,CodeSz);
    PosAns.insert(PosAns.end(), Master.begin(), Master.end());

    cout << "Code: ";
    for (int i = 0; i < CodeSz; ++i) {
        cout << code[i] << " ";
    }
    cout << endl;

    while (!won) {

        //Remove Guess from possible solutions
        RmvCode(Master, Guess);
        RmvCode(PosAns, Guess);

        //Play the guess to get a response of colored and white pegs
        Pegs = ChckAns(Guess, code,CodeSz);

        cout << "Turn: " << turn << endl;
        cout << "Guess: ";
        for (int i = 0; i < CodeSz; ++i) {
            cout << Guess[i] << " ";
        }
        cout << "= " << Pegs << endl;

        //If the response is four colored pegs, the game is won
        if (Pegs == "BBBB") {
            won = true;
            cout << "Game Won!" << endl;
            return 0;
        }

        //Remove from candidateSolutions,
        //any code that would not give the same response if it were the code
        PrnCode(PosAns, Guess,Pegs,CodeSz);

        //Calculate Minmax scores
        nxGuess = minmax(Master,PosAns,CodeSz);

        //Select next guess
        Guess = getNxGuess(Master,nxGuess,PosAns);

        turn++;
    }//End while
    
    return 0;
}

vector<int> crtAns(const int &nColour, const int &CodeSz) {
    vector<int> code;
    for (int i = 0; i < CodeSz; ++i) {
        code.push_back(rand()%nColour);
    }
    return code;
}

void crtSet(vector<vector<int>> &Master, const int &nColour, const int &CodeSz) {
    vector<int> current(CodeSz, 0);     //Current possible solution
    vector<int> elements;               //Possible elements
    
    //fills the possible elements
    for (int i = 0; i < nColour; ++i) {
        elements.push_back(i);
    }

    //creates all the possible combinations
    crtComb(Master,current,elements,CodeSz,0);
    
}

void crtComb(vector<vector<int>> &Master, vector<int> &current, vector<int> &elements, const int &CodeSz, int position) {
    if (position >= CodeSz) {
        Master.push_back(current);  //sends current possible solution to an array that will contain all the solutions 
        return;
    }
    for (int j = 0; j < elements.size(); ++j) {
        current[position] = elements[j];
        crtComb(Master,current,elements,CodeSz,position+1);
    }
    return;
}

string ChckAns(vector<int> guess, vector<int> code, const int &CodeSz) {
    string result;
    //Get black/coloured    - correct in the correct possition
    for (int i=0; i<CodeSz; i++) {
        if (guess[i] == code[i]) {
            result.append("B");
            guess[i] = -1;
            code[i] = -1;
        }
    }

    //Get white             - correct in the wrong spot
    for (int i=0;i<CodeSz;i++) {
        if (code[i] >= 0) {
            vector<int>::iterator it = find(guess.begin(), guess.end(), code[i]);
            int index;
            if (it != guess.end()) {
                index = distance(guess.begin(), it);
                result.append("W");
                guess[index] = -1;
            }
        }
    }
    return result;
}

void RmvCode(vector<vector<int>> &set, vector<int> currentCode) {
    int index;
    for (vector<vector<int>>::iterator it = set.begin(); it != set.end(); it++) {
        index = distance(set.begin(), it);
        if (set[index] == currentCode) {
            set.erase(set.begin() + index);
            return;
        }
    }
}

void PrnCode(vector<vector<int>> &set, vector<int> currentCode, string currentResponse, const int &CodeSz) {
    int index;
    vector<vector<int>>::iterator it = set.begin();
    while (it != set.end()) {
        index = distance(set.begin(), it);
        if (currentResponse != ChckAns(currentCode, set[index],CodeSz)) {
            it = set.erase(set.begin() + index);
        } else {
            it++;
        }
    }
}

vector<vector<int>> minmax(vector<vector<int>> &Master,vector<vector<int>> &PosAns, const int &CodeSz) {

    map<string, int> scoreCount;
    map<vector<int>, int> score;
    vector<vector<int>> nxGuess;
    int max, min;
    for (int i = 0; i < Master.size(); ++i) {
        for (int j = 0; j < PosAns.size(); ++j) {
            string pegScore = ChckAns(Master[i], PosAns[j], CodeSz);
            if (scoreCount.count(pegScore) > 0) {
                scoreCount.at(pegScore)++;
            } else {
                scoreCount.emplace(pegScore,1);
            }
        }

        max = getMaxS(scoreCount);
        score.emplace(Master[i], max);
        scoreCount.clear();
    }

    min = getMinS(score);

    for (pair<vector<int>,int> elem : score) {
        if (elem.second == min) {
            nxGuess.push_back(elem.first);
        }
    }

    return nxGuess;
}

int getMaxS(map<string, int> inputMap) {

    int max = 0;
    for (pair<string,int> elem : inputMap) {
        if (elem.second > max) {
            max = elem.second;
        }
    }

    return max;
}

int getMinS(map<vector<int>, int> inputMap) {

    int min = numeric_limits<int>::max();
    for (pair<vector<int>,int> elem : inputMap) {
        if (elem.second < min) {
            min = elem.second;
        }
    }

    return min;
}

vector<int> getNxGuess(vector<vector<int>> &Master,vector<vector<int>> nxGuess, vector<vector<int>> &PosAns) {

    vector<int> nextGuess;

    for (int i = 0; i < nxGuess.size(); ++i) {
        if (find(PosAns.begin(), PosAns.end(), nxGuess[i]) != PosAns.end()) {
            return nxGuess[i];
        }
    }
    for (int j = 0; j < nxGuess.size(); ++j) {
        if (find(Master.begin(), Master.end(), nxGuess[j]) != Master.end()) {
            return nxGuess[j];
        }
    }

    return nextGuess;
}

