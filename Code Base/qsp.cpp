#include <iostream>
#include <thread>
#include <fstream>
#include <time.h>
using namespace std;

int partition(int arr[], int start, int end)
{

    int pivot = arr[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++)
    {
        if (arr[i] <= pivot)
            count++;
    }

    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex)
    {

        while (arr[i] <= pivot)
        {
            i++;
        }

        while (arr[j] > pivot)
        {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex)
        {
            swap(arr[i++], arr[j--]);
        }
    }

    return pivotIndex;
}

void quickSort(int arr[], int start, int end)
{

    if (start >= end)
        return;

    int p = partition(arr, start, end);

    quickSort(arr, start, p - 1);

    quickSort(arr, p + 1, end);
}

int main()
{

    std::ifstream in;
    in.open("filehundredthou.txt");
    // Fixed size array used to store the elements in the text file.
    // Change array type according to the type of the elements you want to read from the file
    int arr[100000];
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
    quickSort(arr, 0, n - 1);
    end = clock();
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    printf("Time taken: %f", (end - start) / (double)CLOCKS_PER_SEC);

    return 0;
}

