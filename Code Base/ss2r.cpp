#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
#include <time.h>
using namespace std;

const int NUM_THREADS = 2;
const int ARRAY_SIZE = 100;

void selectionSort(vector<int> &arr, int start, int end)
{
    for (int i = start; i < end; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < end; j++)
        {
            if (arr[j] < arr[min_idx])
            {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
}

void merge(vector<int> &arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (i = 0; i < n1; i++)
    {
        L[i] = arr[l + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[m + 1 + j];
    }

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int> &arr, int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main()
{
    vector<int> arr(ARRAY_SIZE);
    ifstream inputFile("file100.txt");

    if (!inputFile.is_open())
    {
        cout << "Error opening input file" << endl;
        return 1;
    }

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        inputFile >> arr[i];
    }

    inputFile.close();

    int chunkSize = ARRAY_SIZE / NUM_THREADS;
    vector<thread> threads(NUM_THREADS);
    clock_t start, end;
    start = clock();
    for (int i = 0; i < NUM_THREADS; i++)
    {
        int start = i * chunkSize;
        int end = (i == NUM_THREADS - 1) ? ARRAY_SIZE : start + chunkSize;
        threads[i] = thread(selectionSort, ref(arr), start, end);
    }

    for (auto &t : threads)
    {
        t.join();
    }
    end = clock();
    mergeSort(arr, 0, ARRAY_SIZE - 1);

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    printf("Time taken: %f\n", (end - start) / (double)CLOCKS_PER_SEC);
    return 0;
}

