#include <iostream>
#include <fstream>
#include <string>



using namespace std;

int main() 
{

    char ch;
    string in; //string assoc. with input file name
    string out; //string assoc. with output file name
    
    //Prompt user for input file and output file
    cout << "Enter a file name that you want to use as input ";
    cin >> in;
    cout << endl;
    cout << "Enter a file name that you want to use for output ";
    cin >> out;
    
    //Declare two file stream objects for input and output.
    fstream fin,fout; //declare variables used to open and close files
    
    //Open those files
    fin.open(in, ios::in); //allows input (read operations) from a stream
    fout.open(out, ios::out); //allows output (write operations) to a stream
    if(fin)cout<<"Open"<<endl;
    //until end of file input
    while(fin) //or while((!fin.eof())
    {
    fin.get(ch); //take one char from input file at a time
    cout<<ch;
    fout.put(toupper(ch)); // change char from input
    fin.get(ch); // from input file get characters, again????
    
    
    //while the char from last picked up file ^ above is not a period
        while(ch!='.')
        {
            cout<<ch;
            //convert chars to lowercase
            fout.put(tolower(ch));// from output file change chars to lowercase
            fin.get(ch); //get the next character from input file
                
        }
        fin.get(ch); //could be for whitespace
    
    //go to next line of input file
    fout << endl;
    cout<<endl;
    }
    //close both files
    fin.close();
    fout.close();
    
    //pause system for a while to wait until enter is hit after input
    //system("pause");
    
    return 0;
}

