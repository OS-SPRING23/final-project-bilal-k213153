#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
#include <time.h>
using namespace std;

// Insertion sort function
void insertionSort(vector<int> &arr, int start, int end)
{
    int i, key, j;
    for (i = start + 1; i <= end; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= start && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// Merge function for merge sort
void merge(vector<int> &arr, int start, int mid, int end)
{
    int i, j, k;
    int n1 = mid - start + 1;
    int n2 = end - mid;

    vector<int> L(n1), R(n2);

    for (i = 0; i < n1; i++)
        L[i] = arr[start + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0;
    j = 0;
    k = start;
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

// Merge sort function
void mergeSort(vector<int> &arr, int start, int end)
{
    if (start < end)
    {
        int mid = start + (end - start) / 2;

        // Create four threads to sort the four quarters of the array in parallel
        thread t1(insertionSort, ref(arr), start, start + (end - start) / 4);
        thread t2(insertionSort, ref(arr), start + (end - start) / 4 + 1, start + (end - start) / 2);
        thread t3(insertionSort, ref(arr), start + (end - start) / 2 + 1, start + 3 * (end - start) / 4);
        thread t4(insertionSort, ref(arr), start + 3 * (end - start) / 4 + 1, end);

        // Wait for the four threads to finish
        t1.join();
        t2.join();
        t3.join();
        t4.join();

        // Merge the four sorted quarters
        merge(arr, start, start + (end - start) / 4, start + (end - start) / 2);
        merge(arr, start + (end - start) / 2 + 1, start + 3 * (end - start) / 4, end);
        merge(arr, start, start + (end - start) / 2, end);
    }
}

int main()
{
    ifstream file("file100.txt");
    if (!file)
    {
        cout << "Error: Unable to open file" << endl;
        return 0;
    }
    vector<int> arr;
    int x;
    while (file >> x)
    {
        arr.push_back(x);
    }

    file.close();

    // Get the size of the array
    int n = arr.size();
    clock_t start, end;
    start = clock();

    // Call merge sort on the entire array
    mergeSort(arr, 0, n - 1);
    end = clock();

    // Print the sorted array
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    printf("Time taken: %f\n", (end - start) / (double)CLOCKS_PER_SEC);
    return 0;
}

