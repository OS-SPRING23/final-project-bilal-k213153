#include <iostream>
#include<time.h>
#include <fstream>
using namespace std;

void merge(int array[], int const left, int const mid,
		int const right)
{
	auto const subArrayOne = mid - left + 1;
	auto const subArrayTwo = right - mid;

	auto *leftArray = new int[subArrayOne],
		*rightArray = new int[subArrayTwo];

	for (auto i = 0; i < subArrayOne; i++)
		leftArray[i] = array[left + i];
	for (auto j = 0; j < subArrayTwo; j++)
		rightArray[j] = array[mid + 1 + j];

	auto indexOfSubArrayOne
		= 0, 
		indexOfSubArrayTwo
		= 0; 
	int indexOfMergedArray
		= left; 

	while (indexOfSubArrayOne < subArrayOne
		&& indexOfSubArrayTwo < subArrayTwo) {
		if (leftArray[indexOfSubArrayOne]
			<= rightArray[indexOfSubArrayTwo]) {
			array[indexOfMergedArray]
				= leftArray[indexOfSubArrayOne];
			indexOfSubArrayOne++;
		}
		else {
			array[indexOfMergedArray]
				= rightArray[indexOfSubArrayTwo];
			indexOfSubArrayTwo++;
		}
		indexOfMergedArray++;
	}
	while (indexOfSubArrayOne < subArrayOne) {
		array[indexOfMergedArray]
			= leftArray[indexOfSubArrayOne];
		indexOfSubArrayOne++;
		indexOfMergedArray++;
	}
	while (indexOfSubArrayTwo < subArrayTwo) {
		array[indexOfMergedArray]
			= rightArray[indexOfSubArrayTwo];
		indexOfSubArrayTwo++;
		indexOfMergedArray++;
	}
	delete[] leftArray;
	delete[] rightArray;
}

void mergeSort(int array[], int const begin, int const end)
{
	if (begin >= end)
		return; // Returns recursively

	auto mid = begin + (end - begin) / 2;
	mergeSort(array, begin, mid);
	mergeSort(array, mid + 1, end);
	merge(array, begin, mid, end);
}

void printArray(int A[], int size)
{
	for (auto i = 0; i < size; i++)
		cout << A[i] << " ";
}

int main()
{
    std::ifstream in;
    in.open("file10000.txt");
    // Fixed size array used to store the elements in the text file.
    // Change array type according to the type of the elements you want to read from the file
    int arr[10000];
    int element;

    if (in.is_open()) {
        int i = 0;
        while (in >> element) {
            arr[i++] = element;
        }
    }

    in.close();
	auto arr_size = sizeof(arr) / sizeof(arr[0]);
	clock_t start,end;
	start=clock();

	mergeSort(arr, 0, arr_size - 1);
	end=clock();
	cout << "\nSorted array is \n";
	printArray(arr, 10000);
	printf("Time taken: %f",(end - start)/(double)CLOCKS_PER_SEC);
	return 0;
}


