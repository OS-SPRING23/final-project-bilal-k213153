#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;
#define SIZE 100
void quicksort(vector<int> &data, int left, int right)
{
    int i = left, j = right;
    int pivot = data[(left + right) / 2];

    while (i <= j)
    {
        while (data[i] < pivot)
            i++;
        while (data[j] > pivot)
            j--;

        if (i <= j)
        {
            swap(data[i], data[j]);
            i++;
            j--;
        }
    }

    if (left < j)
        quicksort(data, left, j);
    if (i < right)
        quicksort(data, i, right);
}

void threaded_quicksort(vector<int> &data, int left, int right, int max_depth)
{
    if (left < right)
    {
        if (max_depth == 0)
        {
            quicksort(data, left, right);
        }
        else
        {
            int i = left, j = right;
            int pivot = data[(left + right) / 2];

            while (i <= j)
            {
                while (data[i] < pivot)
                    i++;
                while (data[j] > pivot)
                    j--;

                if (i <= j)
                {
                    swap(data[i], data[j]);
                    i++;
                    j--;
                }
            }

            thread left_thread(threaded_quicksort, ref(data), left, j, max_depth - 1);
            thread right_thread(threaded_quicksort, ref(data), i, right, max_depth - 1);
            left_thread.join();
            right_thread.join();
        }
    }
}

void merge(vector<int> &data, int left, int mid, int right)
{
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (i = 0; i < n1; i++)
        L[i] = data[left + i];
    for (j = 0; j < n2; j++)
        R[j] = data[mid + 1 + j];

    i = 0;
    j = 0;
    k = left;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            data[k] = L[i];
            i++;
        }
        else
        {
            data[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1)
    {
        data[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        data[k] = R[j];
        j++;
        k++;
    }
}

void mergesort(vector<int> &data, int left, int right, int max_depth)
{
    if (left < right)
    {
        if (max_depth == 0 || right - left < SIZE)
        {
            sort(data.begin() + left, data.begin() + right + 1);
        }
        else
        {
            int mid = left + (right - left) / 2;

            thread left_thread(mergesort, ref(data), left, mid, max_depth - 1);
            thread right_thread(mergesort, ref(data), mid + 1, right, max_depth - 1);
            left_thread.join();
            right_thread.join();

            merge(data, left, mid, right);
        }
    }
}

int main()
{
    vector<int> data(SIZE);

    // Open file for reading
    ifstream file("file100.txt");
    if (!file.is_open())
    {
        cerr << "Could not open file." << endl;
        return 1;
    }

    // Read data from file
    for (int i = 0; i < SIZE; i++)
    {
        file >> data[i];
    }
    clock_t start, end;
    start = clock();
    // Apply quicksort using 4 threads
    threaded_quicksort(data, 0, data.size() - 1, 2);
    end = clock();
    // Apply mergesort to completely sort the data
    mergesort(data, 0, data.size() - 1, 2);

    // Print the sorted data to console
    for (int i = 0; i < SIZE; i++)
    {
        cout << data[i] << " ";
    }

    cout << endl;
    printf("Time taken: %f\n", (end - start) / (double)CLOCKS_PER_SEC);
    return 0;
}

