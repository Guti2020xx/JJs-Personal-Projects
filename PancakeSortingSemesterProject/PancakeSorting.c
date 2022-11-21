// Pancake Sorting created by Juan Gutierrez
// CS 2315 Algorithms Fall 2022
// Problem Difficulty - Medium


#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include "Random.h" // acquired from Dr. Hannah
#include "Random.c" // acquired from Dr. Hannah

int main() 
{ 
    void buildRandomArray(int A[], const int n);
    void printArray(int arr[], int n);
    void printPancakes(int arr[], int n);
    int searchForLargest(int arr[], int n);
    int pSort(int *arr, int n);  
    
    int arrSize;
    
    SetRandomSeed();
    printf("\n Array Size? ");
    while( scanf("%d", &arrSize) != EOF)// ctrl - z to end the program
     {
     	   // dynamically allocating an array size of arrSize
     	   int *arr= (int *) malloc(sizeof(int)*(arrSize)); 
     	   buildRandomArray(arr, arrSize);
     	   
     	   // displaying random unsorted array
     	   printf("\n Unsorted Array: \n ");
     	   printArray(arr, arrSize);
     	   // displaying sorted array
           printf("\n Number of flips to sort the array: %d" ,  pSort(arr, arrSize) ); // sorts array with pancake sort
     	   printf("\n Sorted Array: \n ");
     	   printArray(arr, arrSize);
     	   
     	   free(arr);
     	   printf("\n Array Size? ");
	 }	
	system("PAUSE");
} 


void buildRandomArray(int A[], const int n)
{
	for(int i = 0; i < n; i++)
	{
	    RandomInt(1, 20);	
	}
}


void printArray(int arr[], int n) 
{ 
    for (int i = 0; i < n; i++)
	{ 
        printf("%d ", arr[i]); 
    }
} 


void printPancakes(int arr[], int n)
{
	for(int i = 0; i < n; i ++)
	{
		for(int x = 0; x < arr[i]; x++)
		{
			for(int j = 0; j < arr[i]; j ++)
			{
				printf("X ");
	 		}
	 		printf("\n");
	   }
	}
}

// searches all indexes of the array for the largest element and returns largest index
int searchForLargest(int arr[], int n) 
{ 
  int largestIndex = 0; 
  
  for (int i = 0; i < n; i++) 
  {
       if (arr[i] > arr[largestIndex]) 
       {
            largestIndex = i; 
       }
  }
  return largestIndex; 
} 

void reverseSort(int arr[], int i) // flipping function that is done in place instead of using another copy array
{ 
    int temp, j = 0; // j serves as the start of the array and i is the last index for the reverse sort 
    
    for(int j = 0; j < i ; j++) // start and "end" elements are switched correspondingly
    { 
        temp = arr[i]; 
        arr[i] = arr[j]; 
        arr[j] = temp; 
        i--;
    } 
}

int pSort(int *arr, int n) // pancake sorts an array of size n
{  
    int largest, arrSize = n, flips = 0;
    
    // ensuring that the size of the array is larger than 1 to perform a sort and avoid Out of bound errors
    while(arrSize > 1) 
    {
    	// first we find the index of the largest element inside the array
         largest = searchForLargest(arr, arrSize);
         if( largest != arrSize-1) // as long as the largest element is not in the last index
         {
         	// flip array up to the largest value to get it on top
         	reverseSort(arr, largest); 
         	// flip entire array to shift largest element towards the bottom of the "pancake stack"
         	reverseSort(arr, arrSize - 1);
         	flips = flips + 2;
		 }
    	arrSize--; // to ignore the last element which is already sorted
	}
	return flips;
}  
