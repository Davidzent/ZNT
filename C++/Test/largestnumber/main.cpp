// This program will read in a group of test scores (positive integers from 1 to 100)
// from the keyboard and then calculate and output the average score
// as well as the highest and lowest score. There will be a maximum of 100 scores.

//John Salisbury
//CIs 5 49258
//LMD(10/26/2020)

#include <iostream>
using namespace std;

typedef int GradeType[100];		// declares a new data type:
								// an integer array of 100 elements

float findAverage(const GradeType, int);	// finds average of all grades 
int  findHighest(const GradeType, int);		// finds highest of all grades 
int  findLowest(const GradeType, int);		// finds lowest of all grades

int main()
{
	GradeType grades;	// the array holding the grades. 
	int numberOfGrades;	// the number of grades read.
	int pos;			// index to the array.
	float avgOfGrades;	// contains the average of the grades. 
	int highestGrade;	// contains the highest grade.
	int lowestGrade;	// contains the lowest grade.

	// Read in the values into the array 
	pos = 0;
	cout << "Please input a grade from 1 to 100, (or -99 to stop)" << endl;
	cin >> grades[pos];

	while (numberOfGrades != -99){
            // Fill in the code to read the grades
            pos ++; 
            cout << "Please input a grade or type -99 to stop: " << endl;
            cin >> numberOfGrades;
            grades[pos] = numberOfGrades; 
	}

	numberOfGrades = pos;	// Fill blank with appropriate identifier

	// call to the function to find average
	avgOfGrades = findAverage(grades, numberOfGrades);

	cout << endl << "The average of all the grades is " << avgOfGrades << endl;

	// Fill in the call to the function that calculates highest grade
    highestGrade = findHighest(grades, numberOfGrades);
	cout << endl << "The highest grade is " << highestGrade << endl;

	// Fill in the call to the function that calculates lowest grade
	// Fill in code to write the lowest to the screen
    lowestGrade = findLowest(grades, numberOfGrades);
    cout << endl << "The lowest grade is " << lowestGrade << endl;
	return 0;
}

//********************************************************************************
// findAverage
//
// task:	      This function receives an array of integers and its size.
//	              It finds and returns the average of the numbers in the array
// data in:	      array of floating point numbers
// data returned: average of the numbers in the array
//
//********************************************************************************

float findAverage(const GradeType	array, int size)
{
	float sum = 0;			// holds the sum of all the numbers

	for (int pos = 0; pos < size; pos++)
		sum += array[pos];

	return (sum / size);	// returns the average
}

//****************************************************************************
// findHighest
//
// task:	      This function receives an array of integers and its size.
//	              It finds and returns the highest value of the numbers in 
//                the array
// data in:	      array of floating point numbers
// data returned: highest value of the numbers in the array
//
//****************************************************************************

int	findHighest(const GradeType array, int size){
   
    int hight=array[0];
	// Fill in the code for this function
    for(int pos = 1;pos < size; ++pos){
       // Change < to > if you want to find the smallest element
       if(hight < array[pos])
        hight = array[pos];
    }
    return hight;
}

//****************************************************************************
// findLowest
//
// task:	      This function receives an array of integers and its size.
//	              It finds and returns the lowest value of the numbers in 
//                the array
// data in:	      array of floating point numbers
// data returned: lowest value of the numbers in the array
//
//****************************************************************************

int	findLowest(const GradeType array, int size){
    int low=array[0];
    // Fill in the code for this function
    for(int pos = 1;pos < size; ++pos)
    {
       // Change < to > if you want to find the smallest element
       if(low > array[pos])
        low = array[pos];
    }
    return low;
}