
#include <iostream>
#include <omp.h>

using namespace std;

void merge(int arr[], int low, int mid, int high) {
    // Create arrays of left and right partititons
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int left[n1];
    int right[n2];
    
    // Copy all left elements
    for (int i = 0; i < n1; i++) left[i] = arr[low + i];
    
    // Copy all right elements
    for (int j = 0; j < n2; j++) right[j] = arr[mid + 1 + j];
    
    // Compare and place elements
    int i = 0, j = 0, k = low;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j]){
            arr[k] = left[i];
            i++;
        } 
        else{
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    // If any elements are left out
    while (i < n1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void parallelMergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;

        #pragma omp parallel sections
        {
            #pragma omp section
            {
                parallelMergeSort(arr, low, mid);
            }

            #pragma omp section
            {
                parallelMergeSort(arr, mid + 1, high);
            }
        }
        merge(arr, low, mid, high);
    }
}

void mergeSort(int arr[], int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}

int main() {
    int n = 10;
    int arr[n];
    double start_time, end_time;

    // Create an array with numbers starting from n to 1.
    for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;
    
    // Measure Sequential Time
    start_time = omp_get_wtime(); 
    mergeSort(arr, 0, n - 1);
    end_time = omp_get_wtime(); 
    cout << "Time taken by sequential algorithm: " << end_time - start_time << " seconds\n";

    // Reset the array
    for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;
    
    //Measure Parallel time
    start_time = omp_get_wtime(); 
    parallelMergeSort(arr, 0, n - 1);
    end_time = omp_get_wtime(); 
    cout << "Time taken by parallel algorithm: " << end_time - start_time << " seconds";
    
    return 0;
}













/*
#include <iostream>: This line includes the input/output stream library, which provides functionality for reading and writing to the console.

#include <omp.h>: This line includes the OpenMP library, which enables parallel programming using shared memory multiprocessing.

using namespace std;: This line allows you to use standard library functions and objects without specifying the namespace.

void merge(int arr[], int low, int mid, int high): This line defines a function named merge that takes an array arr and three integers low, mid, and high as parameters. It implements the merge operation of the merge sort algorithm.

int n1 = mid - low + 1;: This line calculates the size of the left partition of the array during the merge operation.

int n2 = high - mid;: This line calculates the size of the right partition of the array during the merge operation.

int left[n1];: This line declares an integer array left with a size of n1 to store the elements of the left partition.

int right[n2];: This line declares an integer array right with a size of n2 to store the elements of the right partition.

for (int i = 0; i < n1; i++) left[i] = arr[low + i];: This loop copies the elements from the original array arr to the left array.

for (int j = 0; j < n2; j++) right[j] = arr[mid + 1 + j];: This loop copies the elements from the original array arr to the right array.

int i = 0, j = 0, k = low;: This line initializes three indices i, j, and k to track the positions in the left, right, and arr arrays during the merge operation.

25-32. This while loop compares the elements in the left and right arrays and places them in the correct order in the arr array.

35-40. These while loops handle the case where there are remaining elements in either the left or right array that have not been merged yet.

void parallelMergeSort(int arr[], int low, int high): This line defines a function named parallelMergeSort that takes an array arr and two integers low and high as parameters. It implements the parallel version of the merge sort algorithm using OpenMP.

if (low < high) {: This line checks if the partition size is greater than 1. If true, the array is divided into smaller partitions and sorted.

51-53. #pragma omp parallel sections and #pragma omp section are OpenMP directives that indicate that the following code should be executed in parallel.

parallelMergeSort(arr, low, mid);: This line recursively calls the parallelMergeSort function to sort the left partition of the array.

parallelMergeSort(arr, mid + 1, high);: This line recursively calls the parallelMergeSort function to sort the right partition of the array.

merge(arr, low, mid, high);: This line merges the sorted left and right partitions using the merge function.

void mergeSort(int arr[], int low, int high): This line defines a function named mergeSort that takes an array arr and two integers low and high as parameters. It implements the sequential version of the merge sort algorithm.

if (low < high) {: This line checks if the partition size is greater than 1. If true, the array is divided into smaller partitions and sorted.

int mid = (low + high) / 2;: This line calculates the middle index of the current partition.

73-74. These lines recursively call the mergeSort function to sort the left and right partitions of the array.

merge(arr, low, mid, high);: This line merges the sorted left and right partitions using the merge function.

int n = 10;: This line declares and initializes an integer variable n with a value of 10, representing the size of the array.

int arr[n];: This line declares an integer array arr with a size of n.

double start_time, end_time;: This line declares two double variables start_time and end_time to measure the execution time of the sorting algorithms.

86-92. This loop initializes the array arr with numbers in descending order from n to 1.

start_time = omp_get_wtime();: This line records the current time using the OpenMP function omp_get_wtime() and assigns it to the start_time variable.

mergeSort(arr, 0, n - 1);: This line calls the mergeSort function to sort the array arr in ascending order using the sequential merge sort algorithm.

end_time = omp_get_wtime();: This line records the current time using omp_get_wtime() and assigns it to the end_time variable.

cout << "Time taken by sequential algorithm: " << end_time - start_time << " seconds\n";: This line prints the execution time of the sequential merge sort algorithm.

101-105. These lines reset the array arr to its original descending order.

start_time = omp_get_wtime();: This line records the current time using omp_get_wtime() and assigns it to the start_time variable.

parallelMergeSort(arr, 0, n - 1);: This line calls the parallelMergeSort function to sort the array arr in ascending order using the parallel merge sort algorithm.

end_time = omp_get_wtime();: This line records the current time using omp_get_wtime() and assigns it to the end_time variable.

cout << "Time taken by parallel algorithm: " << end_time - start_time << " seconds";: This line prints the execution time of the parallel merge sort algorithm.

return 0;: This line indicates the end of the main function and returns 0 to the operating system, indicating successful program execution.


*/