// This program uses a bubble sort to arrange an array of integers in
// ascending order

// John Salisbury
//Cis 5 49258
//LMD (11/2/2020)

#include <iostream>
using namespace std;

// function prototypes
void bubbleSortArray(int[], int);
void displayArray(int[], int);

const int SIZE = 5;

int main()
{
	int values[SIZE] = { 9, 2, 0, 11, 5 };

	cout << "The values before the bubble sort is performed are:" << endl;
	displayArray(values, SIZE);

	bubbleSortArray(values, SIZE);

	cout << "The values after the bubble sort is performed are:" << endl;
	displayArray(values, SIZE);

	return 0;
}

//******************************************************************
//	displayArray
//
//  task:	  to print the array
//  data in:  the array to be printed, the array size
//  data out: none
//
//******************************************************************

void displayArray(int array[], int elems)	// function heading
{		
	// displays the array 
	for (int count = 0; count < elems; count++)
		cout << array[count] << "	" << endl;
}

//******************************************************************
//	bubbleSortArray
//
//  task:	  to sort values of an array in ascending order
//  data in:  the array, the array size
//  data out: the sorted array
//
//******************************************************************

void bubbleSortArray(int array[], int elems)
{
	bool swap;
	int temp;
	int top = elems + 1;	// bottom indicates the end part of the
							// array where the largest values have
							// settled in order 
	do
	{
		swap = false;

		for (int count = 0; count < top; count++)
		{
                    cout<<endl;
                    displayArray(array, SIZE);
			if (array[count] < array[count + 1])
			{		
				// the next three lines do a swap 
				temp = array[count];
				array[count] = array[count + 1];
				array[count + 1] = temp;

				swap = true; // indicates that a swap occurred
			}
		}

		top--;	// bottom is decremented by 1 since each pass through
					// the array adds one more value that is set in order

	} while (swap != false);
	// loop repeats until a pass through the array with
	// no swaps occurs
}