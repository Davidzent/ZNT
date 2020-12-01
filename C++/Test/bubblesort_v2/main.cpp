/* 
This program will allow the user to enter and amount of number up to 50 
into an array. It will then ask the user to enter a number for the 
program to search for and the program will check the array for the
desired number. I will use binary search and a bubble sort to complete the 
program

Joseph Groves-Forbes
*/

#include <iostream>
using namespace std;

void bubbleSortArray(int[], int);
void displayArray(int[], int);
const int SIZE = 50;
int binarySearch(int[], int, int);

int main()
{
    int arrays;
    int values[SIZE];
    int found, value;
    int elems=0;
    
    
    cout << "Please input the numbers you want in the array, Max 50. input -99 to stop" << endl;
    cin >> value;
    values[elems++]=value;
    while(value!=-99&&elems<SIZE){
        cin >> value;
        values[elems++]=value;
    }
    if(values[elems-1]==-99)elems--;
	cout << "The values before the bubble sort is performed are:" << endl;
	displayArray(values, elems);

	bubbleSortArray(values, elems);

	cout << "The values after the bubble sort is performed are:" << endl;
	displayArray(values, elems);
	
	cout << "\nEnter an number to search for:" << endl;
	cin >> value;

	found = binarySearch(values, elems, value);

	if (found == -1)
		cout << "The number " << value << " cannot be found" << endl;
	else
		cout << "The number " << value << " is in position number "
		     << found + 1 << " of the list" << endl;

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
		cout << array[count] << " ";
        cout<<endl;
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
	int bottom = elems - 1;	// bottom indicates the end part of the
							// array where the largest values have
							// settled in order 
	do
	{
		swap = false;

		for (int count = 0; count < bottom; count++)
		{
			if (array[count] > array[count + 1])
			{		
				// the next three lines do a swap 
				temp = array[count];
				array[count] = array[count + 1];
				array[count + 1] = temp;

				swap = true; // indicates that a swap occurred
			}
		}

		bottom--;	// bottom is decremented by 1 since each pass through
					// the array adds one more value that is set in order

	} while (swap != false);
}	

int binarySearch(int array[], int elems, int value)	
{
	int first = 0;				
	int last = elems - 1;	
	int middle;					
							

	while (first <= last)
	{
		middle = first + (last - first) / 2;

		if (array[middle] == value)
			return middle;		

		else if (array[middle]<value)
			last = middle - 1;	

		else
			first = middle + 1;	
	}

	return -1;	
}	

