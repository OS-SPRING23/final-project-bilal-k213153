#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <fstream>
#include <time.h>
std::vector<int> arr;
int num_threads = 4;
std::mutex mtx; // Mutex for synchronization

void bubble_sort(std::vector<int> &arr, int left, int right)
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
    int chunk_size = arr.size() / num_threads;

    for (int i = 0; i < num_threads; i++)
    {
        int left = i * chunk_size;
        int right = (i == num_threads - 1) ? arr.size() - 1 : (i + 1) * chunk_size - 1;
        threads[i] = std::thread(bubble_sort_thread, left, right);
    }

    for (auto &thread : threads)
    {
        thread.join();
    }
}


int main()
{
    std::ifstream in;
    in.open("file10000.txt");
    // Fixed size array used to store the elements in the text file.
    // Change array type according to the type of the elements you want to read from the file

    int element;
    if (in.is_open())
    {
        int i = 0;
        while (in >> element)
        {
            arr.push_back(element);
        }
    }
    in.close();
    clock_t start, end;
    start = clock();
    parallel_bubble_sort();
    end = clock();
    std::cout << "Sorted array: ";
    for (int num : arr)
        std::cout << num << " ";
    std::cout << std::endl;
    printf("Time taken: %f\n", (end - start) / (double)CLOCKS_PER_SEC);
    return 0;
}

