// C program for insertion sort
#include <math.h>
#include <stdio.h>

void sort_by_insertion(int arr[], int n)
{
	int i, key, j;
	// Assume first element is already sorted
	for (i = 1; i < n; i++)
	{
		// Make a copy of element to be inserted.
		key = arr[i];
		j = i - 1;
        // Move all elements are greater than key 
        // by one element.
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		// now do the insertion.
		arr[j + 1] = key;
	}
}

// A utility function to print
// an array of size n
void printArray(int arr[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

// Driver code
int main()
{
	int arr[] = {12, 11, 13, 5, 6};
	int n = sizeof(arr) / sizeof(arr[0]);

    printf("Input: \n");
    printArray(arr, n);
	sort_by_insertion(arr, n);
	printArray(arr, n);
	return 0;
}

