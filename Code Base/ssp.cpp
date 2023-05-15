#include <iostream>
#include <thread>
#include <fstream>
#include <time.h>
#include <thread>
using namespace std;

// Swap function
void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void selectionSort(int arr[], int n)
{
	int i, j, min_idx;
	// One by one move boundary of
	// unsorted subarray
	for (i = 0; i < n - 1; i++)
	{
		// Find the minimum element in
		// unsorted array
		min_idx = i;
		for (j = i + 1; j < n; j++)
		{
			if (arr[j] < arr[min_idx])
				min_idx = j;
		}
		// Swap the found minimum element
		// with the first element
		if (min_idx != i)
			swap(&arr[min_idx], &arr[i]);
	}
}

// Function to print an array
void printArray(int arr[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
}

// Driver program to test above functions
int main()
{
	std::ifstream in;
	in.open("filemil.txt");
	// Fixed size array used to store the elements in the text file.
	// Change array type according to the type of the elements you want to read from the file
	int arr[1000000];
	int element;

	if (in.is_open())
	{
		int i = 0;
		while (in >> element)
		{
			arr[i++] = element;
		}
	}
	in.close();
	auto n = sizeof(arr) / sizeof(arr[0]);
	clock_t start, end;
	start = clock();
	selectionSort(arr, n);
	end = clock();
	cout << "Sorted array: \n";
	printArray(arr, n);
	printf("Time taken: %f", (end - start) / (double)CLOCKS_PER_SEC);
	return 0;
}

