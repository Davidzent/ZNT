#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>

using namespace std;


typedef struct student
{
    char name[10];
    int age;
    int age2;
    int age3;
    int age4;
    int age5;
    int age6;
    int age7;
    
    vector<int> grades;
}student_t;

int main()
{
    student_t apprentice[3];  
    strcpy(apprentice[0].name, "john");
    apprentice[0].age = 21;
    apprentice[0].age2 = 21;
    apprentice[0].age3 = 21;
    apprentice[0].age4 = 21;
    apprentice[0].age5 = 21;
    apprentice[0].age6 = 21;
    apprentice[0].age7 = 21;
    
    apprentice[0].grades.push_back(1);
    apprentice[0].grades.push_back(3);
    apprentice[0].grades.push_back(5);    

    strcpy(apprentice[1].name, "jerry");
    apprentice[1].age = 22;
    apprentice[1].age2 = 21;
    apprentice[1].age3 = 21;
    apprentice[1].age4 = 21;
    apprentice[1].age5 = 21;
    apprentice[1].age6 = 21;
    apprentice[1].age7 = 21;
    apprentice[1].grades.push_back(2);
    apprentice[1].grades.push_back(4);
    apprentice[1].grades.push_back(6);

    strcpy(apprentice[2].name, "jimmy");
    apprentice[2].age = 23;
    apprentice[2].age2 = 21;
    apprentice[2].age3 = 21;
    apprentice[2].age4 = 21;
    apprentice[2].age5 = 21;
    apprentice[2].age6 = 21;
    apprentice[2].age7 = 21;
    apprentice[2].grades.push_back(8);
    apprentice[2].grades.push_back(9);
    apprentice[2].grades.push_back(10);

    // Serializing struct to student.data
    ofstream output_file("students.dat", ios::binary);
    output_file.write((char*)&apprentice, sizeof(apprentice));
    output_file.close();

    // Reading from it
    ifstream input_file("students.dat", ios::binary);
    //student_t master[3];
    input_file.read((char*)&apprentice, sizeof(apprentice));         
    input_file.close();
    for (size_t idx = 0; idx < 3; idx++)
    {
        // If you wanted to search for specific records, 
        // you should do it here! if (idx == 2) ...

        cout << "Record #" << idx << endl;
        cout << "Name: " << apprentice[idx].name << endl;
        cout << "Age: " << apprentice[idx].age << endl;
        cout << "Age: " << apprentice[idx].age2 << endl;
        cout << "Age: " << apprentice[idx].age3 << endl;
        cout << "Age: " << apprentice[idx].age4 << endl;
        cout << "Age: " << apprentice[idx].age5 << endl;
        cout << "Age: " << apprentice[idx].age6 << endl;
        cout << "Age: " << apprentice[idx].age7 << endl;
        
        cout << "Grades: " << endl;
        for (size_t i = 0; i < apprentice[idx].grades.size(); i++)
           cout << apprentice[idx].grades[i] << " ";
        cout << endl << endl;
    }

    return 0;
}