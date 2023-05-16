#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <fstream>
#include <time.h>
int arr[100];
int num_threads = 2;
#define size 10
std::mutex mtx; // Mutex for synchronization
using namespace std;
// Bubble Sort function
void bubble_sort(int arr[], int left, int right)
{
    for (int i = left; i < right; i++)
    {
        for (int j = left; j < right - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                std::lock_guard<std::mutex> lock(mtx); // Lock the critical section
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Thread function for parallel bubble sort
void bubble_sort_thread(int left, int right)
{
    bubble_sort(arr, left, right);
}

// Parallel Bubble Sort function
void parallel_bubble_sort()
{
    std::vector<std::thread> threads(num_threads);
    int chunk_size = size / num_threads;

    for (int i = 0; i < num_threads; i++)
    {
        int left = i * chunk_size;
        int right = (i == num_threads - 1) ? size - 1 : (i + 1) * chunk_size - 1;
        threads[i] = std::thread(bubble_sort_thread, left, right);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }
}

// Merge sorted subarrays
void merge_sorted_subarrays(int arr[], int left, int mid, int right)
{
    std::vector<int> temp(right - left + 1);
    int i = left;
    int j = mid + 1;
    int k = 0;

    while (i <= mid && j <= right)
    {
        if (arr[i] <= arr[j])
            temp[k++] = arr[i++];
        else
            temp[k++] = arr[j++];
    }

    while (i <= mid)
        temp[k++] = arr[i++];

    while (j <= right)
        temp[k++] = arr[j++];

    for (i = left, k = 0; i <= right; i++, k++)
        arr[i] = temp[k];
}

// Merge Sort function
void merge_sort(int arr[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge_sorted_subarrays(arr, left, mid, right);
    }
}

int main()
{
    ifstream in;
    in.open("file100.txt");
    // Fixed size array used to store the elements in the text file.
    // Change array type according to the type of the elements you want to read from the file
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
    clock_t start, end;
    start = clock();
    parallel_bubble_sort();

    merge_sort(arr, 0, size - 1);
    end = clock();
    std::cout << "Sorted array: ";
    for (int num : arr)
        std::cout << num << " ";
    std::cout << std::endl;
    printf("Time taken: %f\n", (end - start) / (double)CLOCKS_PER_SEC);
    return 0;
}

