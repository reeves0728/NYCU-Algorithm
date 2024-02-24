#include <iostream>
#include <chrono>
using namespace std;

void insertion_sort(int array[], int size);
void print_result(int array[], int size);

//print the sorted result
void print_result(int array[], int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

//insertion sort implementation
void insertion_sort(int array[], int size) {
    for (int step = 1; step < size; step++) {
        int key = array[step];
        int j = step - 1;
        while (key < array[j] && j >= 0) {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}


int main() {
    int array_size;
    cout << "Please input the size of the array:";
    cin >> array_size;
    //dynamic allocate memory space
    int* input = new int[array_size];
    //create a random unsorted array
    for (int i = 0; i < array_size; i++)
    {
        int num = rand() % 1000;
        input[i] = num;
    }
    //record insertion sort starting time
    auto start_time = chrono::high_resolution_clock::now();
    //insertion sort
    insertion_sort(input, array_size);
    //record insertion sort ending time
    auto end_time = chrono::high_resolution_clock::now();
    //calculate duration
    auto duration = chrono::duration_cast<chrono::microseconds>(end_time - start_time);
    //print result
    //cout << "Results after insertion sort:\n";
    //print_result(input, array_size);
    //print execution time
    cout << "Execution time: " << duration.count() << " microseconds" << endl;
    return 0;
}
