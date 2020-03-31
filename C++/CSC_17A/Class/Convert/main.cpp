/*
* Created on September 24, 2018, 12:38 PM
*/

#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace std;

int main(int argc, char** argv) {
    string s;
    cin >> s;
    stringstream ss;
    ss << s;
    float num1; // needs to be int
    ss >> num1;
    cout<<num1<<endl;
    ss.clear();
    ss << s;
    float num2; // float
    ss >> num2;
    cout<<num2<<endl;
    return 0;
}