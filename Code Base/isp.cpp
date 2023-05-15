#include <iostream>
#include <time.h>
#include <fstream>
using namespace std;
void printArray(int array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << array[i] << " ";
    }
    cout << endl;
}

void insertionSort(int array[], int size)
{
    for (int step = 1; step < size; step++)
    {
        int key = array[step];
        int j = step - 1;

        while (key < array[j] && j >= 0)
        {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}

int main()
{
    std::ifstream in;
    in.open("filemil.txt");//change to which file is needed
    // Fixed size array used to store the elements in the text file.
    // Change array type according to the type of the elements you want to read from the file
    int arr[1000000]; //change to whichever array size needed
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
    auto arr_size = sizeof(arr) / sizeof(arr[0]);
    clock_t start, end;
    start = clock();
    insertionSort(arr, arr_size);
    end = clock();
    cout << "Sorted array in ascending order:\n";
    printArray(arr, arr_size);
    cout << "\n";
    printf("Time taken: %f", (end - start) / (double)CLOCKS_PER_SEC);
}
