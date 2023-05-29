/*
  Windows does not support user defined reductions.
  This program may not run on MVSC++ compilers for Windows.
  Please use Linux Environment.[You can try using "windows subsystem for linux"]
*/

#include<iostream>
#include<omp.h>

using namespace std;
int minval(int arr[], int n){
  int minval = arr[0];
  #pragma omp parallel for reduction(min : minval)
    for(int i = 0; i < n; i++){
      if(arr[i] < minval) minval = arr[i];
    }
  return minval;
}

int maxval(int arr[], int n){
  int maxval = arr[0];
  #pragma omp parallel for reduction(max : maxval)
    for(int i = 0; i < n; i++){
      if(arr[i] > maxval) maxval = arr[i];
    }
  return maxval;
}

int sum(int arr[], int n){
  int sum = 0;
  #pragma omp parallel for reduction(+ : sum)
    for(int i = 0; i < n; i++){
      sum += arr[i];
    }
  return sum;
}

int average(int arr[], int n){
  return (double)sum(arr, n) / n;
}

int main(){
  int n = 5;
  int arr[] = {1,2,3,4,5};
  cout << "The minimum value is: " << minval(arr, n) << '\n';
  cout << "The maximum value is: " << maxval(arr, n) << '\n';
  cout << "The summation is: " << sum(arr, n) << '\n';
  cout << "The average is: " << average(arr, n) << '\n';
  return 0;
}


/*The function minval takes an array arr and its size n as input.
It initializes a variable minval with the first element of the array.
The #pragma omp parallel for reduction(min : minval) directive indicates that the following loop will be executed in parallel. Each thread will find the minimum value from its portion of the array, and then the minimum values found by each thread will be combined using the reduction operation min to obtain the overall minimum value.
Inside the loop, each thread compares the array element at index i with the current minval and updates minval if a smaller value is found.
Finally, the function returns the minimum value.
The explanations for the remaining functions (maxval, sum, and average) are similar. They use the reduction clause with different operators (max and +) to perform parallel reductions for finding the maximum value, sum, and average of the array, respectively.

The sum function takes an array arr and its size n as input.
It initializes an integer variable sum to store the sum of the array elements.
The #pragma omp parallel for reduction(+ : sum) directive indicates that the following loop will be executed in parallel. Each thread will compute the sum of its portion of the array, and then the partial sums computed by each thread will be combined using the reduction operation + to obtain the overall sum.
Inside the loop, each thread adds the value of arr[i] to its local sum variable.
Finally, the function returns the overall sum.
By using OpenMP's reduction clause with + operator, the work of summing the array elements is divided among multiple threads, allowing for parallel execution. The reduction operation ensures that the partial sums from each thread are correctly combined to produce the final sum.




Certainly! Here's an explanation of the average function in simple points:

The average function takes an array arr and its size n as input.
It calculates the sum of the array elements by calling the sum function, passing the array and its size as arguments.
The sum is divided by n to compute the average.
To ensure that the division is performed with floating-point precision, the result is cast to double using (double) before dividing.
The resulting average value is returned.
In summary, the average function calculates the average value of the elements in the array by dividing the sum of the elements by the number of elements.
In the main function:

An array arr is initialized with values.
The minimum value, maximum value, sum, and average of the array are computed by calling the respective functions.
The results are printed using cout.




Certainly! Here's an explanation of parallel reduction in simple points:

- Parallel reduction is a technique used in parallel computing to perform efficient and parallel computations on large datasets.
- It is particularly useful when the computation involves a reduction operation, such as summing elements, finding the minimum or maximum value, or computing the average.
- The goal of parallel reduction is to divide the computation among multiple threads or processes to achieve faster execution.
- Each thread or process works on a portion of the dataset independently, performing the reduction operation on that portion.
- After completing the local reduction, the partial results from each thread or process are combined or "reduced" together to obtain the final result.
- This reduction step typically involves combining the partial results using the same reduction operation that was applied locally.
- By parallelizing the reduction operation, parallel reduction can significantly speed up the computation compared to a sequential implementation.
- Parallel reduction is commonly implemented using constructs or directives provided by parallel programming frameworks, such as OpenMP or MPI, which allow for easy expression of parallelism and handling of the reduction operation.
- The reduction operation is specified using the reduction clause or directive, which indicates the operation to be performed and the variable that will hold the final result.
- The parallel framework automatically handles the distribution of work, synchronization, and reduction of the partial results, simplifying the parallelization process for the programmer.

In summary, parallel reduction is a technique that enables efficient parallel computation of reduction operations by distributing the work among multiple threads or processes and combining the partial results to obtain the final result. It can significantly improve the performance of computations involving reductions on large datasets.*/

