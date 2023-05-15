#include <iostream>
#include <thread>
#include <fstream>
#include <time.h>
#include <thread>
using namespace std;

const int NUM_THREADS = 4;
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(int arr[], int x, int n)
{
    int i, j, min_idx;
    for (i = x; i < n - 1; i++)
    {
        min_idx = i;
        for (j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        if (min_idx != i)
            swap(&arr[min_idx], &arr[i]);
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
}

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
    int step = n / NUM_THREADS;
    int count = 0;
    start = clock();
    thread t(selectionSort, arr, 0, (step - 1));
    count += step;
    step += step;
    thread t2(selectionSort, arr, count, step - 1);
    count += step;
    step += step;
    thread t3(selectionSort, arr, count, step - 1);
    count += step;
    thread t4(selectionSort, arr, count, n - 1);
    t.join();
    t2.join();
    t3.join();
    t4.join();
    end = clock();
    cout << "Sorted array: \n";
    printArray(arr, n);
    printf("Time taken: %f", (end - start) / (double)CLOCKS_PER_SEC);
    return 0;
}

