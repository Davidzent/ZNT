/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on October 7, 2020, 10:47 AM
 */

#include <iostream>
#include <iomanip>

using namespace std;

// Prototypes of the functions
void convertMulti(float dollars, float& euros, float& pesos);
void convertMulti(float dollars, float& euros, float& pesos, float& yen);
float convertToYen(float dollars);
float convertToEuros(float dollars);
float convertToPesos(float dollars);

const float yencon = 124.35;
const float eurocon = 1.06;
const float pesoscon = 9.73;

int main(int argc, char** argv) {
    float dollars;
	float euros;
	float pesos;
	float yen;
cout << fixed << showpoint << setprecision(2);

	cout << "Please input the amount of American Dollars you want converted "
		 << endl;
	cout << "to euros and pesos" << endl;
	cin >> dollars;

	// Fill in the code to call convertMulti with parameters dollars, euros, and pesos
    convertMulti(dollars, euros, pesos);
	// Fill in the code to output the value of those dollars converted to both euros
	// and pesos
    cout <<"The amount of euros and pesos you have is " << euros <<" Euros and " << pesos <<" Pesos" << endl;
	cout << "Please input the amount of American Dollars you want converted\n";
	cout << "to euros, pesos and yen" << endl;
	cin >> dollars;

    // Fill in the code to call convertMulti with parameters dollars, euros, pesos and yen
    convertMulti(dollars, euros, pesos, yen);
	// Fill in the code to output the value of those dollars converted to euros,
	// pesos and yen
    cout <<"The amount of euros,pesos, and yen you have is " << euros <<" Euros and " << pesos <<" Pesos and " << yen <<" Yen" << endl;
	cout << "Please input the amount of American Dollars you want converted\n";
	cout << "to yen" << endl;
	cin >> dollars;

	// Fill in the code to call convertToYen
    convertToYen(dollars);
	// Fill in the code to output the value of those dollars converted to yen
    cout <<"The amount of yen you have is " << yen << endl;
	cout << "Please input the amount of American Dollars you want converted\n";
	cout << " to euros" << endl;
	cin >> dollars;
	// Fill in the code to call convert ToEuros
    convertToEuros(dollars);
	// Fill in the code to output the value of those dollars converted to euros
    cout <<"The amount of euros you have is " << euros << endl;
	cout << "Please input the amount of American Dollars you want converted\n";
	cout << " to pesos " << endl;
	cin >> dollars;

	// Fill in the code to call convertToPesos
    convertToPesos(dollars);
	// Fill in the code to output the value of those dollars converted to pesos
    cout <<"The amount of pesos you have is " << pesos << endl;
    return 0;
}

void convertMulti(float dollars, float& euros, float& pesos)
{
	cout << "The function convertMulti with dollars, euros and pesos "
		 << endl << " was called with " << dollars << " dollars" << endl << endl;
    euros = dollars * eurocon;
    pesos = dollars * pesoscon;
}
void convertMulti(float dollars, float& euros, float& pesos, float& yen)
{
	cout << "The function convertMulti with dollars, euros, pesos and yen"
		 << endl << " was called with " << dollars << " dollars" << endl << endl;
    euros = dollars * eurocon;
    pesos = dollars * pesoscon;
    yen = dollars * yencon;
}
float convertToYen(float dollars)
{
    float yen = 0;
	cout << "The function convertToYen was called with " << dollars << " dollars"
		 << endl << endl;
		 yen = dollars * yencon;

	return yen;
}
float convertToEuros(float dollars)
{
    float euros = 0;
	cout << "The function convertToEuros was called with " << dollars
		 << " dollars" << endl << endl;
    euros = dollars * eurocon;
	return euros;
}
float convertToPesos(float dollars)
{
    float pesos = 0;
	cout << "The function convertToPesos was called with " << dollars
		 << " dollars" << endl;
    pesos = dollars * pesoscon;
	return pesos;
}
