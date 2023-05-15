#include <iostream>
#include <thread>
#include <fstream>
#include <time.h>
using namespace std;

const int NUM_THREADS = 4;

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

    // base case
    if (start >= end)
        return;

    // partitioning the array
    int p = partition(arr, start, end);

    // Sorting the left part
    quicksort(arr, start, p - 1);

    // Sorting the right part
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
    start = clock();
    int step = n / NUM_THREADS;
    int count = 0;
    start = clock();
    thread t(quicksort, arr, 0, step - 1);
    count = step;
    thread t2(quicksort, arr, count, (count + step) - 1);
    count = count + step;
    thread t3(quicksort, arr, count, (count + step) - 1);
    count = count + step;
    thread t4(quicksort, arr, count, n - 1);
    t.join();
    t2.join();
    t3.join();
    t4.join();
    end = clock();
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    printf("Time taken: %f", (end - start) / (double)CLOCKS_PER_SEC);
    return 0;
}

