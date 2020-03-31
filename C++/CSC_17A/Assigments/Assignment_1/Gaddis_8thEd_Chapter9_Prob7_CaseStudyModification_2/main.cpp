/* 
 * File:   main.cpp
 * Author: Guijosa, David
 * Created on March 22, 2018, 11:00 AM
 * Purpose:  Hello World Template
 */

//System Libraries Here
#include <iostream>
#include <iomanip>
using namespace std;

//User Libraries Here

//Global Constants Only, No Global Variables
//Like PI, e, Gravity, or conversions

//Function Prototypes Here
void getSales(float *, int);
float totalSales(float *, int);
//Program Execution Begins Here
int main(int argc, char** argv) {
    //declare and initialize variables
    int QTRS;
    cout<<"enter the number of donations"<<endl;
    cin>>QTRS;
    float sales[QTRS];
    getSales(sales, QTRS);

    // Set the numeric output formatting.
    cout << fixed << showpoint << setprecision(2);

    // Display the total sales for the year.
    cout << "The total sales for the year are $";
    cout << totalSales(sales, QTRS) << endl;

    //Exit
    return 0;
}
float totalSales(float *arr, int size){
    float sum = 0.0;
    for (int count = 0; count < size; count++){
        sum += *arr;
        arr++;
    }
    return sum;}
void getSales(float *arr, int size){
    for (int count=size-1;count>=0;count++){
    cout << "Enter the sales figure for quarter ";
    cout << (count + 1) << ": ";
    cin >> arr[count];
    }
}