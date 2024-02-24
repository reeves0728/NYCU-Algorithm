#include <iostream>
#include <chrono>
using namespace std;

void Merge_Sort(int arr[], int left, int right);
void Merge(int arr[], int left, int right, int middle);
void print_result(int arr[], int size);

int main()
{
    int array_size;
    cout << "Please input the size of the array:";
    cin >> array_size;
    //dynamic allocate memory space
    int* input = new int[array_size];
    //assign random value
    for (int i = 0; i < array_size; i++)
    {
        int num = rand() % 1000;
        input[i] = num;
    }
    //record starting time
    auto start_time = chrono::high_resolution_clock::now();
    Merge_Sort(input, 0, array_size - 1);
    //record ending time
    auto end_time = chrono::high_resolution_clock::now();

    //print result
    //cout << "Results after merge sort:\n";
    //print_result(input, array_size);

    //calulate merge sort duration
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    cout << "Execution time: " << duration.count() << " microseconds" << endl;
    //release memory
    delete[] input;
    return 0;
}

void Merge_Sort(int arr[], int left, int right)
{
    if (left < right)
    {
        int middle = (left + right) / 2;
        Merge_Sort(arr, left, middle);
        Merge_Sort(arr, middle + 1, right);
        Merge(arr, left, right, middle);
    }
}
void Merge(int arr[], int left, int right, int middle)
{
    int n1 = middle - left + 1;
    int n2 = right - middle;
    // create Left and right dynamic array
    int* L = new int[n1];
    int* R = new int[n2];

    // preventing the algorithm from going out of bounds or causing an error
    L[n1] = 2147483647;
    R[n2] = 2147483647;

    for (int i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++)
    {
        R[i] = arr[i + middle + 1];
    }

    int i = 0, j = 0;
    for (int k = left; k <= right; k++)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
    }
}

void print_result(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}