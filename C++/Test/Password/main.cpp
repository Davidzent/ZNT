// This program tests a password for the American Equities
// web page to see if the format is correct



#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

//function prototypes
bool testPassWord(char[]);
int countLetters(char*);
int countDigits(char*);

int main()
{
	char passWord[20];
	char occursL;
	int occursD;

	cout << "Enter a password consisting of exactly 5 "
		 << "letters and 3 digits:" << endl;

	cin.getline(passWord, 20);

	if (testPassWord(passWord))
		cout << "Please wait - your password is being verified" << endl;

	else
	{
		cout << "Invalid password. Please enter a password "
			 << "with exactly 5 letters and 3 digits" << endl;
		cout << "For example, my37RuN9 is valid" << endl;
	}
	
	// countDigits and will print to the screen both the number of
	// letters and digits contained in the password.
	
	cout<<"The number of letters in the password is "<<countLetters(passWord)<<endl;
	cout<<"The number of digits in the password is "<<countDigits(passWord)<<endl;

	return 0;
}

//**************************************************************
//	testPassWord
//
//  task:	       determines if the word in the
//	               character array passed to it, contains
//	               exactly 5 letters and 3 digits.
//  data in:	   a word contained in a character array
//  data returned: true if the word contains 5 letters & 3
//	               digits, false otherwise
//
//**************************************************************
bool testPassWord(char custPass[])
{
	int numLetters, numDigits, length;

	length = strlen(custPass);
	numLetters = countLetters(custPass);
	numDigits = countDigits(custPass);

	if (numLetters == 5 && numDigits == 3 && length == 8)
		return true;
	else
		return false;
}

// the next 2 functions are from Sample Program 10.5

//*******************************************************************
//	countLetters
//
//  task:	       This function counts the number of letters
//	               (both capital and lower case) in the string
//  data in:	   pointer that points to an array of characters
//  data returned: number of letters in the array of characters
//
//*******************************************************************

int countLetters(char *strPtr)
{
	int occursL = 0;

	while (*strPtr != '\0')	// loop is executed as long as
		// the pointer strPtr does not point
		// to the null character which
		// marks the end of the string
	{
		if (isalpha(*strPtr))	// isalpha determines if
			occursL++;			// the character is a letter

		strPtr++;
	}

	return occursL;
}

//*******************************************************************
//	countDigits
//
//  task:	       This function counts the number of digits
//	               in the string
//  data in:	   pointer that points to an array of characters
//  data returned: number of digits in the array of characters
//
//*******************************************************************

int countDigits(char *strPtr)
{
	int occursD = 0;

	while (*strPtr != '\0')
	{
		if (isdigit(*strPtr))	// isdigit determines if
			occursD++;			// the character is a digit

		strPtr++;
	}

	return occursD;
}

