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

        // Create two threads to sort the two halves of the array in parallel
        thread t1(mergeSort, ref(arr), start, mid);
        thread t2(mergeSort, ref(arr), mid + 1, end);

        // Wait for the two threads to finish
        t1.join();
        t2.join();

        // Merge the two sorted halves
        merge(arr, start, mid, end);
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
    clock_t start, end;
    start = clock();
    // Create two threads to sort the two halves of the array in parallel
    thread t1(insertionSort, ref(arr), 0, arr.size() / 2 - 1);
    thread t2(insertionSort, ref(arr), arr.size() / 2, arr.size() - 1);

    // Wait for the two threads to finish
    t1.join();
    t2.join();
    end = clock();
    // Merge the two partially sorted halves using merge sort
    mergeSort(arr, 0, arr.size() - 1);

    // Print the sorted array
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
    printf("Time taken: %f\n", (end - start) / (double)CLOCKS_PER_SEC);
    return 0;
}

