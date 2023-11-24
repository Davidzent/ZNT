#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

int main(int argc, char const *argv[])
{
    fstream fin, fout;
    int contador;


    fin.open("File.txt", ios::in);    
    if(fin){
        fin>>contador;
        fin.close();
    }else{
        contador=1;
    }

    double a,b;
    cin >> a >> b;
    a+=b;

    if(contador==3){
        cout<<"Case #"<<contador<<": "<<setprecision(2) << fixed << a;
    }
    else{
        cout<<setprecision(2) << fixed << a;
    }

    contador++;
    fout.open("File.txt", ios::out);
    fout<<contador;
    fout.close();

    return 0;
}