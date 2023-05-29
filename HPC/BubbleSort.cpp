#include<iostream>
#include<omp.h>

using namespace std;

void bubble(int array[], int n){
    for (int i = 0; i < n - 1; i++){
        for (int j = 0; j < n - i - 1; j++){
            if (array[j] > array[j + 1]) swap(array[j], array[j + 1]);
        }
    }
}

void pBubble(int array[], int n){
    //Sort odd indexed numbers
    for(int i = 0; i < n; ++i){    
        #pragma omp for
        for (int j = 1; j < n; j += 2){
        if (array[j] < array[j-1])
        {
          swap(array[j], array[j - 1]);
        }
    }

    // Synchronize
    #pragma omp barrier

    //Sort even indexed numbers
    #pragma omp for
    for (int j = 2; j < n; j += 2){
      if (array[j] < array[j-1])
      {
        swap(array[j], array[j - 1]);
      }
    }
  }
}

void printArray(int arr[], int n){
    for(int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n";
}

int main(){
    // Set up variables
    int n = 10;
    int arr[n];
    // int brr[n];
    double start_time, end_time;

    // Create an array with numbers starting from n to 1
    for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;
    
    // Sequential time
    start_time = omp_get_wtime();
    bubble(arr, n);
    end_time = omp_get_wtime();     
    cout << "Sequential Bubble Sort took : " << end_time - start_time << " seconds.\n";
    printArray(arr, n);
    
    // Reset the array
    for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;
    
    // Parallel time
    start_time = omp_get_wtime();
    pBubble(arr, n);
    end_time = omp_get_wtime();     
    cout << "Parallel Bubble Sort took : " << end_time - start_time << " seconds.\n";
    printArray(arr, n);
}   



/* 
#include<iostream>: This line includes the input/output stream library, which provides functionality for reading and writing to the console.

#include<omp.h>: This line includes the OpenMP library, which enables parallel programming using shared memory multiprocessing.

using namespace std;: This line allows you to use standard library functions and objects without specifying the namespace.

void bubble(int array[], int n): This line defines a function named bubble that takes an array of integers and the size of the array as parameters. It implements the bubble sort algorithm to sort the array in ascending order.

for (int i = 0; i < n - 1; i++): This line starts a loop that iterates from 0 to n - 1. It represents the number of passes needed to sort the array.

for (int j = 0; j < n - i - 1; j++): This line starts a nested loop that iterates from 0 to n - i - 1. It compares adjacent elements and swaps them if they are in the wrong order.

if (array[j] > array[j + 1]) swap(array[j], array[j + 1]);: This line checks if the current element is greater than the next element. If true, it swaps the elements using the swap function.

void pBubble(int array[], int n): This line defines a function named pBubble that takes an array of integers and the size of the array as parameters. It implements a parallel version of the bubble sort algorithm.

for(int i = 0; i < n; ++i): This line starts a loop that iterates from 0 to n - 1. It represents the number of passes needed to sort the array.

#pragma omp for: This line is an OpenMP directive that indicates that the following loop should be executed in parallel.

if (array[j] < array[j-1]) swap(array[j], array[j - 1]);: This line checks if the current element (odd index) is smaller than the previous element. If true, it swaps the elements using the swap function.

#pragma omp barrier: This line is an OpenMP directive that ensures that all threads have completed the previous loop before proceeding to the next section of code.

#pragma omp for: This line indicates that the following loop should be executed in parallel.

if (array[j] < array[j-1]) swap(array[j], array[j - 1]);: This line checks if the current element (even index) is smaller than the previous element. If true, it swaps the elements using the swap function.

void printArray(int arr[], int n): This line defines a function named printArray that takes an array of integers and the size of the array as parameters. It prints the elements of the array.

for(int i = 0; i < n; i++) cout << arr[i] << " ";: This line starts a loop that iterates from 0 to n - 1. It prints each element of the array separated by a space using the cout statement.

cout << "\n";: This line prints a newline character to start a new line after printing the array.

int main(): This line defines the starting point of the program. The main function is called when the program is executed.

int n = 10;: This line declares and initializes an integer variable n with a value of 10, representing the size of the array.

int arr[n];: This line declares an integer array named arr with a size of n.

int brr[n];: This line declares an integer array named brr with a size of n. However, brr is not used in the code.

double start_time, end_time;: This line declares two double variables start_time and end_time to measure the execution time of the sorting algorithms.

for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;: This loop initializes the array arr with numbers in descending order from n to 1. It uses two variables i and j to assign the values.

start_time = omp_get_wtime();: This line records the current time using the OpenMP function omp_get_wtime() and assigns it to the start_time variable.

bubble(arr, n);: This line calls the bubble function to sort the array arr in ascending order using the sequential bubble sort algorithm.

end_time = omp_get_wtime();: This line records the current time using omp_get_wtime() and assigns it to the end_time variable.

cout << "Sequential Bubble Sort took : " << end_time - start_time << " seconds.\n";: This line prints the execution time of the sequential bubble sort algorithm.

printArray(arr, n);: This line calls the printArray function to print the sorted array arr.

for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;: This loop reinitializes the array arr with numbers in descending order from n to 1.

start_time = omp_get_wtime();: This line records the current time using omp_get_wtime() and assigns it to the start_time variable.

pBubble(arr, n);: This line calls the pBubble function to sort the array arr in ascending order using the parallel bubble sort algorithm.

end_time = omp_get_wtime();: This line records the current time using omp_get_wtime() and assigns it to the end_time variable.

cout << "Parallel Bubble Sort took : " << end_time - start_time << " seconds.\n";: This line prints the execution time of the parallel bubble sort algorithm.

printArray(arr, n);: This line calls the printArray function to print the sorted array arr.



*/