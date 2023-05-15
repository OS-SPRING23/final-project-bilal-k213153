#include <iostream>
#include <pthread.h>
#include <time.h>
#include<fstream>
#define size 1000000
#define thread_size 4
using namespace std;
int arr[size];
int temp_val = 0;
void combine_array(int first, int mid_val, int end){
   int* start = new int[mid_val - first + 1];
   int* last = new int[end - mid_val];
   int temp_1 = mid_val - first + 1;
   int temp_2 = end - mid_val;
   int i, j;
   int k = first;
   for(i = 0; i < temp_1; i++){
      start[i] = arr[i + first];
   }
   for (i = 0; i < temp_2; i++){
      last[i] = arr[i + mid_val + 1];
   }
   i = j = 0;
   while(i < temp_1 && j < temp_2){
      if(start[i] <= last[j]){
         arr[k++] = start[i++];
      }
      else{
         arr[k++] = last[j++];
      }
   }
   while (i < temp_1){
      arr[k++] = start[i++];
   }
   while (j < temp_2){
      arr[k++] = last[j++];
   }
}
void Sorting_Threading(int first, int end){
   int mid_val = first + (end - first) / 2;
   if(first < end){
      Sorting_Threading(first, mid_val);
      Sorting_Threading(mid_val + 1, end);
      combine_array(first, mid_val, end);
   }
}
void* Sorting_Threading(void* arg){
   int set_val = temp_val++;
   int first = set_val * (size / 4);
   int end = (set_val + 1) * (size / 4) - 1;
   int mid_val = first + (end - first) / 2;
   if (first < end){
      Sorting_Threading(first, mid_val);
      Sorting_Threading(mid_val + 1, end);
      combine_array(first, mid_val, end);
   }
   return NULL;
}
int main(){
    std::ifstream in;
    in.open("filemil.txt");
    // Fixed size array used to store the elements in the text file.
    // Change array type according to the type of the elements you want to read from the file
    int element;

    if (in.is_open()) {
        int i = 0;
        while (in >> element) {
            arr[i++] = element;
        }
    }
    in.close();
    clock_t start,end;
    
   pthread_t P_TH[thread_size];
   start=clock();
   for(int i = 0; i < thread_size; i++){
      pthread_create(&P_TH[i], NULL, Sorting_Threading, (void*)NULL);
   }
   for(int i = 0; i < thread_size; i++){
      pthread_join(P_TH[i], NULL);
   }
   
   combine_array(0, (size / 2 - 1) / 2, size / 2 - 1);
   combine_array(size / 2, size/2 + (size-1-size/2)/2, size - 1);
   combine_array(0, (size - 1)/2, size - 1);
   end=clock();
   cout<<"Merge Sort using Multi-threading: ";
   for (int i = 0; i < size; i++){
      cout << arr[i] << " ";
   }
   printf("Time taken: %f\n",(end - start)/(double)CLOCKS_PER_SEC);
   return 0;
}
