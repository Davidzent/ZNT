// This program demonstrates the use of dynamic variables

// PLACE YOUR NAME HERE

#include <iostream>
#include <iomanip>
using namespace std;

void sort(float* score, int numScores);
void displayScore(float* score, int numScores);

int main()
{
	float *score = nullptr;
	int numScores;
	float average;
	int count;
	int total = 0;
	
	cout << fixed << showpoint << setprecision(2);
	
	cout << "Input the number of scores" << endl;;
	cin >> numScores;
	
	score = new float[numScores];
	
	if ( numScores <= 0)
	{
		cout << "invalid input!\n";
		return 1;
	}
	
	for (count = 0; count < numScores; count++)
	{
		cout << "Please enter a score" << endl;
        cin >> score[count];
        
	}
	
	for (count = 0; count < numScores; count++)
	{
		total = total + score[count];
	}
	
	average = total / numScores;
	
	cout << "The average of the scores is " 
	<< average << "\n" << endl;
	
	sort(score, numScores);
	
	cout << "Here are the scores in ascending order" << endl;
	displayScore(score, numScores);
    
	return 0;
}

void sort(float* score, int numScores)
{
    bool swap;
	int temp;
	int bottom = numScores - 1;	
    do
	{
        
		swap = false;
        
		for (int count = 0; count < bottom; count++)
		{
			if (score[count] > score[count + 1])
			{		
				temp = score[count];
				
				score[count] = score[count + 1];

				
				score[count + 1] = temp;

				swap = true; 
			}
		}	
               bottom--; 
	} while (swap != false);
}

void displayScore(float* score, int numScores)
{		
	for (int count = 0; count < numScores; count++)
		cout << score[count] << "	" << endl;
}
