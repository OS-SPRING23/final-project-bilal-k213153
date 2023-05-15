#include <iostream>
#include <time.h>
#include <pthread.h>
#include <fstream>
#define size 1000000
#define thread_size 4 //change threads as needed

using namespace std;

int arr[size];

void *insertion(void *arg)
{
    int start = (intptr_t)(arg);
    cout << start;
    int end = start + size / thread_size;
    for (int i = start + 1; i < end; i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= start && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
    return NULL;
}

int main()
{
    ifstream in;
    in.open("filemil.txt");
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

    pthread_t P_TH[thread_size];
    int start[thread_size], end[thread_size];
    int step = size / thread_size;
    int count = -step;
    clock_t s, e;
    s = clock();

    for (int i = 0; i < thread_size; i++)
    {
        count = count + step;
        pthread_create(&P_TH[i], NULL, insertion, (void *)(intptr_t)count);
    }
    for (int i = 0; i < thread_size; i++)
    {
        pthread_join(P_TH[i], NULL);
    }
    e = clock();
    cout << "Insertion Sort using Multi-threading: ";
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << "\n";
    printf("Time taken: %f", (e - s) / (double)CLOCKS_PER_SEC);
    return 0;
}
