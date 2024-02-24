#include <iostream>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
void swap(int& t1, int& t2);
void randomQuickSort(int* arr, int left, int right);
int randomPartition(int* arr, int p, int r);
int Partition(int* arr, int p, int r);
void Printarr(int* arr, int heap_size);


void Printarr(int* arr, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
    {
        std::cout << arr[i] << " ";
    }
    cout << endl;
}

void swap(int& t1, int& t2)
{
    int temp = t1;
    t1 = t2;
    t2 = temp;
}

void randomQuickSort(int* arr,int left, int right) {
    if (left < right) {
        int q = randomPartition(arr,left,right);
        randomQuickSort(arr, left, q - 1);
        randomQuickSort(arr, q + 1, right);
    }
}

int randomPartition(int* arr, int p, int r) {
    int min = p;
    int max = r;
    int i = rand() % (max - min + 1) + min;
    swap(arr[r], arr[i]);
    return Partition(arr, p, r);
}

int Partition(int *arr,int p, int r){
    int x = arr[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (arr[j] <= x) {
            i = i + 1;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[r]);
    return i + 1;
}



int main()
{

    int arr_size;
    cout << "Please input the heap_size of the array:";
    cin >> arr_size;
    int* input = new int[arr_size];
    for (int i = 0; i < arr_size; i++)
    {
        int num = rand() % 1000;
        input[i] = num;
    }

    auto start_time = chrono::high_resolution_clock::now();
    randomQuickSort(input,0 ,arr_size-1);
    auto end_time = chrono::high_resolution_clock::now();
    Printarr(input, arr_size);
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    cout << "Execution time: " << duration.count() << " microseconds" << endl;

    delete[] input;

    return 0;
}