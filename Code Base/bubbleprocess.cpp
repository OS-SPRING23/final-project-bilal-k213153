#include <iostream>
#include <time.h>
#include <fstream>
using namespace std;

void bubbleSort(int array[], int size)
{

    for (int step = 0; step < size; ++step)
    {

        for (int i = 0; i < size - step; ++i)
        {

            if (array[i] > array[i + 1])
            {

                int temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }
}

void printArray(int array[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << "  " << array[i];
    }
    cout << "\n";
}

int main()
{
    int data[10000];
    std::ifstream in;
    in.open("file10000.txt");
    int element;

    if (in.is_open())
    {
        int i = 0;
        while (in >> element)
        {
            data[i++] = element;
        }
    }
    in.close();

    int size = sizeof(data) / sizeof(data[0]);
    clock_t start, end;
    start = clock();
    bubbleSort(data, size);
    end = clock();
    cout << "Sorted Array in Ascending Order:\n";
    printArray(data, size);
    printf("Time taken: %f\n", (end - start) / (double)CLOCKS_PER_SEC);
}
