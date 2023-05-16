#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;
#define size 100
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

void threaded_quicksort(vector<int> &data, int left, int right)
{
    if (left < right)
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

        thread left_thread(threaded_quicksort, ref(data), left, j);
        thread right_thread(threaded_quicksort, ref(data), i, right);
        left_thread.join();
        right_thread.join();
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

void mergesort(vector<int> &data, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;

        mergesort(data, left, mid);
        mergesort(data, mid + 1, right);

        merge(data, left, mid, right);
    }
}

int main()
{
    vector<int> data(size);

    ifstream file("file100.txt");

    if (!file)
    {
        cerr << "Failed to open file" << endl;
        return -1;
    }

    for (int i = 0; i < size; i++)
    {
        if (!(file >> data[i]))
        {
            cerr << "Failed to read number " << i << endl;
            return -1;
        }
    }

    file.close();
    clock_t start, end;
    start = clock();
    threaded_quicksort(data, 0, size - 1);
    end = clock();
    mergesort(data, 0, size - 1);
    for (int i = 0; i < size; i++)
    {
        cout << data[i] << " ";
    }

    cout << endl;
    printf("Time taken: %f\n", (end - start) / (double)CLOCKS_PER_SEC);
    return 0;
}
