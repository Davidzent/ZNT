#include <cstdlib>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    //declare and initialize
    ifstream cin;
    ofstream cout;
    cin.open("input.txt");
    cout.open("output.txt");
    float n;
    
    //calculations and output
    cout<<"Enter an angle in radiants\n";
    cin>>n;
    cout<<fixed<<showpoint<<setprecision(4);
    cout<<"Sin("<<n<<") = "<<sin(n)<<endl;
    cout<<"cos("<<n<<") = "<<cos(n)<<endl;
    cout<<"tan("<<n<<") = "<<tan(n)<<endl;
    
    //exit
    return 0;
}

