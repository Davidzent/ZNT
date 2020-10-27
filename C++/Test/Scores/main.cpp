// John Salisbury
// Cis 5 49258
//LMD (10/19/2020)

#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    int A_Score = 90;
    int B_Score = 80;
    int C_Score = 70;
    int D_Score = 60;
    int MAX_Score = 100;
    int MIN_Score = 0;
    
    int number, number2;
    
    
    double test, test2, test3, test4, test5;
    double average;
    cout <<"How many students are there?" << endl;
    cin >> number;
    cout <<"How many tests were there?" << endl;
    cin >> number2;
    	for (int t = 1; t <= number; t++)
	{
            average=0;
            for ( int tests = 1; tests <= number2; tests++)
            {
                    cout <<"What are the "<<number2<<" test scores for student " << t <<" ?" << endl;
                    cin >> test;
                    
                    if (test > MAX_Score)
                    {
                        cout << "Invalid input please run the program again and input values less than 100." << endl;
                        tests--;
                    }
                    else if (test < MIN_Score)
                    {
                        cout << "Invalid input please run the program again and input values greater than 0." << endl;
                        tests--;
                    }
                    else
                    {
                        average += test;
                    }
            }
            average /= number2;             //average = average/number2;
            if (average > MAX_Score)
            {
            cout << "invalid grade please try again by runing the program over." << endl;
            }
            else if (average >= A_Score)
            {
            cout <<"Student " << t <<" average is " << average <<" The grade is an A" << endl;
            }
            else if (average >= B_Score)
            {
            cout <<"Student " << t <<" average is " << average <<" The grade is an B" << endl;
            }
            else if (average >= C_Score)
            {
            cout <<"Student " << t <<" average is " << average <<" The grade is an C" << endl;
            }
            else if (average >= D_Score)
            {
            cout <<"Student " << t <<" average is " << average <<" The grade is an D" << endl;
            }
            else if (average >= MIN_Score)
            {
            cout <<"Student " << t <<" average is " << average <<" The grade is an F" << endl;
            }     
        }
		
     return 0;
}