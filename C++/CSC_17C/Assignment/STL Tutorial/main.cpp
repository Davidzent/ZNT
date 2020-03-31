
/* 
 * File:   main.cpp
 * Author: david
 *
 * Created on April 7, 2019, 10:14 PM
 */
#include <iostream>
#include <cstdlib>
#include <algorithm> //every other formula
#include <vector> //vectors
#include <numeric> //for iota
#include <valarray>

using namespace std;

void show(int a[], int arraysize);
int main(int argc, char** argv) {
    // Initializing vector with array values 
    int arr[] = {10, 20, 5, 23 ,42 , 15}; 
    int n = sizeof(arr)/sizeof(arr[0]); 
    vector<int> vect(arr, arr+n); 
    int a[] = { 1, 5, 8, 9, 6, 7, 3, 4, 2, 0 }; 
    int asize = sizeof(a) / sizeof(a[0]); 
    
    cout << "Vector is: "; 
    for (int i=0; i<n; i++) 
        cout << vect[i] << " "; 
  
    // Sorting the Vector in Ascending order 
    sort(vect.begin(), vect.end()); 
  
    cout << "\nVector after sorting is: "; 
    for (int i=0; i<n; i++) 
       cout << vect[i] << " "; 
  
    // Reversing the Vector 
    reverse(vect.begin(), vect.end()); 
  
    cout << "\nVector after reversing is: "; 
    for (int i=0; i<6; i++) 
        cout << vect[i] << " "; 
  
    cout << "\nMaximum element of vector is: "; 
    cout << *max_element(vect.begin(), vect.end()); 
  
    cout << "\nMinimum element of vector is: "; 
    cout << *min_element(vect.begin(), vect.end()); 
  
    // Starting the summation from 0 
    cout << "\nThe summation of vector elements is: "; 
    cout << accumulate(vect.begin(), vect.end(), 0); 
  
    cout << "\n The array is : "; 
    show(a, asize); 
  
    cout << "\n\nLet's say we want to search for 2 in the array"; 
    cout << "\n So, we first sort the array"; 
    sort(a, a + asize); 
    cout << "\n\n The array after sorting is : "; 
    show(a, asize); 
    cout << "\n\nNow, we do the binary search"; 
    if (binary_search(a, a + 10, 2)) 
        cout << "\nElement found in the array"; 
    else
        cout << "\nElement not found in the array"; 
  
    cout << "\n\nNow, say we want to search for 10"; 
    if (binary_search(a, a + 10, 10)) 
        cout << "\nElement found in the array"; 
    else
        cout << "\nElement not found in the array"; 
  
    // Checking if all elements are positive 
    all_of(a, a+asize, [](int x) { return x>0; })? 
          cout << "All are positive elements" : 
          cout << "All are not positive elements"; 
    none_of(a, a+asize, [](int x){ return x<0; })? 
          cout << "No negative elements" : 
          cout << "There are negative elements"; 
   
    // Declaring second array 
    int ar1[asize]; 
  
    // Using copy_n() to copy contents 
    copy_n(a, asize, ar1); 
  
    // Displaying the copied array 
    cout << "The new array after copying is : "; 
    for (int i=0; i<asize ; i++) 
       cout << ar1[i] << " "; 
    // Initializing array with 0 values 
    int ar[6] =  {0}; 
  
    // Using iota() to assign values 
    iota(ar, ar+6, 20); 
  
    // Displaying the new array 
    cout << "The new array after assigning values is : "; 
    for (int i=0; i<6 ; i++) 
       cout << ar[i] << " "; 
    
    // Checking if vector is partitioned  
    // using is_partitioned() 
    is_partitioned(vect.begin(), vect.end(), [](int x) 
    { 
        return x%2==0; 
          
    })? 
      
    cout << "Vector is partitioned": 
    cout << "Vector is not partitioned"; 
    cout << endl; 
      
    // partitioning vector using partition() 
    partition(vect.begin(), vect.end(), [](int x) 
    { 
        return x%2==0; 
          
    }); 
      
    // Checking if vector is partitioned  
    // using is_partitioned() 
    is_partitioned(vect.begin(), vect.end(), [](int x) 
    { 
        return x%2==0; 
          
    })? 
      
    cout << "Now, vector is partitioned after partition operation": 
    cout << "Vector is still not partitioned after partition operation"; 
    cout << endl; 
      
    // Displaying partitioned Vector 
    cout << "The partitioned vector is : "; 
    for (int &x : vect) cout << x << " "; 

    // Initializing valarray 
    valarray<int> varr = { 10, 2, 20, 1, 30 }; 
      
    // Declaring new valarray 
    valarray<int> varr1 ; 
      
    // Using apply() to increment all elements by 5 
    varr1 = varr.apply([](int x){return x=x+5;}); 
      
    // Displaying new elements value 
    cout << "The new valarray with manipulated values is : "; 
    for (int &x: varr1) cout << x << " "; 
    cout << endl; 
      
    // Displaying sum of both old and new valarray 
    cout << "The sum of old valarray is : "; 
    cout << varr.sum() << endl; 
    cout << "The sum of new valarray is : "; 
    cout << varr1.sum() << endl; 
    // Displaying largest element of valarray 
    cout << "The largest element of valarray is : "; 
    cout << varr1.max() << endl; 
      
    // Displaying smallest element of valarray 
    cout << "The smallest element of valarray is : "; 
    cout << varr1.min() << endl; 
    
    // Declaring new valarray 
    valarray<int> varr2; 
      
    // using shift() to shift elements to left 
    // shifts valarray by 2 position 
    varr2 = varr1.shift(2); 
      
    // Displaying elements of valarray after shifting 
    cout << "The new valarray after shifting is : "; 
    for ( int&x : varr2) cout << x << " "; 
    cout << endl; 
      
    // using cshift() to circulary shift elements to right 
    // rotates valarray by 3 position 
    varr2 = varr1.cshift(-3); 
      
    // Displaying elements of valarray after circular shifting 
    cout << "The new valarray after circular shifting is : "; 
    for ( int&x : varr2) cout << x << " "; 
    cout << endl; 
  
    return 0; 
    
    return 0;
}

 
void show(int a[], int arraysize){ 
    for (int i = 0; i < arraysize; ++i) 
        cout << a[i] << " "; 
} 

