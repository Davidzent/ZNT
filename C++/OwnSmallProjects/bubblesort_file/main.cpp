// This program  prompts the user to enter the number of elements and the
//numbers themselves to be placed in an integer array that holds a maximum of 50
//elements.

//Adli Garniwan
//CIS 5 49258
//10/31/2020

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

const int MAX_SIZE = 50;
void bubbleSort(int[], int); 
int searchBinary(int[], int, int); 
void displayArray(int[], int);


int main()
{
   
    int arraySize;
    int userAnswer;
    int sum=0;
    int average;
    ifstream inputFile;
    ofstream inputOut;
    
    inputFile.open("array.txt");
    inputOut.open("Output.txt");
    
    cout<<"Getting the number of elements on the array...." << endl;
    inputFile>> arraySize;
    int numArray[arraySize];
    
    cout<<"Getting the integer being searched..." << endl;
    inputFile >> userAnswer; 
    
    
    
    for (int i = 0; i <arraySize; i++)
    {
     
        inputFile>> numArray[i];
        sum =sum + numArray[i];
      
    }
  
    average = sum / 7;
    
    bubbleSort(numArray, arraySize); 
    cout<<"Sorting the array with bubble sort....."<<endl;
    
    cout<<"The array after sorting is "<< endl;
    displayArray(numArray, arraySize);
    
     
  
    cout<<"******************************************************"<<endl;
    inputOut<<"The size of the array is "<<arraySize<<endl;
    inputOut << "The value " << userAnswer << " is in position number " <<  (searchBinary(numArray, arraySize, userAnswer) + 1) << endl;
    inputOut << "The mean of the array is " << average << endl;
    
    
		     
    return 0;
    
    
}
void displayArray(int array[], int elems)	// function heading
{		
	// displays the array 
	for (int count = 0; count < elems; count++)
		cout << array[count] << "	" << endl;
}
void bubbleSort(int array[], int elems)
{
	bool swap;
	int temp;
	int bottom = elems - 1;	
	
						
	do
	{
		swap = false;

		for (int count = 0; count < bottom; count++)
		{
		    
			if (array[count] > array[count + 1])
			{		
				
				temp = array[count];
				array[count] = array[count+ 1];
				array[count + 1] = temp;

				swap = true; 
			}
		}
    bottom--;
		
	} while (swap != false);



}
int searchBinary(int array[], int numElems, int value)	// function heading
{
	int first = 0;				// First element of list
	int last = numElems - 1;	// last element of the list
	int middle;					// variable containing the current
								// middle value of the list

	while (first <= last)
	{
		middle = first + (last - first) / 2;

		if (array[middle] == value)
			return middle;		// if value is in the middle, we are done

		else if (array[middle]<value)
			first = middle + 1;	// toss out the second remaining half of

		else
			last = middle - 1;	// toss out the first remaining half of
								// the array and search the second
	}

	return -1;	// indicates that value is not in the array
}
