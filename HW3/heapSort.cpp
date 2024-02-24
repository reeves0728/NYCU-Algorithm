#include <iostream>
#include <chrono>
using namespace std;

void swap(int &t1, int &t2)
{
    int temp = t1;
    t1 = t2;
    t2 = temp;
}

void MaxHeapify(int *arr, int root, int heap_heap_size)
{

    int left = 2 * root + 1;
    int right = 2 * root + 2;
    int largest;

    if (left <= heap_heap_size && arr[left] > arr[root])
        largest = left;
    else
        largest = root;

    if (right <= heap_heap_size && arr[right] > arr[largest])
        largest = right;

    if (largest != root)
    {
        swap(arr[largest], arr[root]);
        MaxHeapify(arr, largest, heap_heap_size);
    }
}

void BuildMaxHeap(int *arr, int heap_size)
{

    for (int i = heap_size / 2 - 1; i >= 0; i--)
    {
        MaxHeapify(arr, i, heap_size - 1);
    }
}

void HeapSort(int *arr, int heap_size)
{

    BuildMaxHeap(arr, heap_size);

    for (int i = heap_size - 1; i >= 1; i--)
    {
        swap(arr[0], arr[i]);
        MaxHeapify(arr, 0, i - 1);
    }
}

void Printarr(int *arr, int heap_size)
{
    for (int i = 0; i < heap_size; i++)
    {
        std::cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{

    int arr_size;
    cout << "Please input the heap_size of the array:";
    cin >> arr_size;
    int *input = new int[arr_size];
    for (int i = 0; i < arr_size; i++)
    {
        int num = rand() % 1000;
        input[i] = num;
    }

    auto start_time = chrono::high_resolution_clock::now();
    HeapSort(input, arr_size);
    auto end_time = chrono::high_resolution_clock::now();
    // Printarr(input, arr_heap_size);
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    cout << "Execution time: " << duration.count() << " microseconds" << endl;

    delete[] input;

    return 0;
}