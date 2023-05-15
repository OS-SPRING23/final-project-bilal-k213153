#include <iostream>
#include <thread>
#include <fstream>
#include <time.h>
using namespace std;

const int NUM_THREADS = 2;

int partition(int arr[], int start, int end)
{

    int pivot = arr[start];

    int count = 0;
    for (int i = start + 1; i <= end; i++)
    {
        if (arr[i] <= pivot)
            count++;
    }

    // Giving pivot element its correct position
    int pivotIndex = start + count;
    swap(arr[pivotIndex], arr[start]);

    // Sorting left and right parts of the pivot element
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

void quicksort(int arr[], int start, int end)
{

    if (start >= end)
        return;

    int p = partition(arr, start, end);

    quicksort(arr, start, p - 1);

    quicksort(arr, p + 1, end);
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
    int step = n / NUM_THREADS;
    int count = 0;
    start = clock();
    thread t(quicksort, arr, 0, step - 1);
    thread t2(quicksort, arr, step, n - 1);
    t.join();
    t2.join();
    end = clock();
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    printf("Time taken: %f", (end - start) / (double)CLOCKS_PER_SEC);
    return 0;
}

