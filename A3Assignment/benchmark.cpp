#include "sorts.h"
#include <chrono>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>


using namespace std;
using namespace chrono;

//Generate random array
void generateRandom(int arr[], int n){

    for(int i = 0; i < n; i++){
        arr[i] = rand() % n;
    }
}

//Generate already sorted array
void generateSorted(int arr[], int n){

    for(int i = 0; i < n; i++){
        arr[i] = i;
    }
}

//Generate reverse sorted array
void generateReverseSorted(int arr[], int n){

    for(int i = n; i <= 0; i++){
        arr[i] = n;
    }
}

//Generate nearly sorted array
void generateNearlySorted(int arr[], int n){

    generateSorted(arr, n);

    //Swap some elements in array
    
    int swaps = n/100; //A small percentage of the elements

    for(int i = 0; i < swaps; i++){
        int a = rand()%n;
        int b = rand()%n;

        swap(arr[a], arr[b]);
    }
}

//Get the median of the three runtimes
double median(double a, double b, double c){

    if((a <= b && b <= c) || (c <= b && b <= a))
        return b;
    if((b <= a && a <= c) || (c <= a && a <= b))
        return a;

    return c;
}

//Timing Bubble Sort
double timeBubbleSort(int original[], int n){

    double times[3];

    for(int run = 0; run < 3; run++){

        int* arr = new int[n];
        memcpy(arr, original, n * sizeof(int));

        auto start = high_resolution_clock::now();

        bubbleSort(arr,n);

        auto end = high_resolution_clock::now();

        times[run] = duration<double>(end-start).count();

        delete[]arr;
    }
        return median(times[0], times[1], times[2]);
}

//Timing Selection Sort
double timeSelectionSort(int original[], int n){

    double times[3];

    for(int run = 0; run < 3; run++){

        int* arr = new int[n];
        memcpy(arr, original, n * sizeof(int));

        auto start = high_resolution_clock::now();

        selectionSort(arr,n);

        auto end = high_resolution_clock::now();

        times[run] = duration<double>(end-start).count();

        delete[]arr;
    }
        return median(times[0], times[1], times[2]);
}

//Timing Insertion Sort
double timeInsertionSort(int original[], int n){

    double times[3];

    for(int run = 0; run < 3; run++){

        int* arr = new int[n];
        memcpy(arr, original, n * sizeof(int));

        auto start = high_resolution_clock::now();

        insertionSort(arr,n);

        auto end = high_resolution_clock::now();

        times[run] = duration<double>(end-start).count();

        delete[]arr;
    }
        return median(times[0], times[1], times[2]);
}

//Timing Merge Sort
double timeMergeSort(int original[], int n){

    double times[3];

    for(int run = 0; run < 3; run++){

        int* arr = new int[n];
        memcpy(arr, original, n * sizeof(int));

        auto start = high_resolution_clock::now();

        mergeSort(arr, 0, n-1);

        auto end = high_resolution_clock::now();

        times[run] = duration<double>(end-start).count();

        delete[]arr;
    }
        return median(times[0], times[1], times[2]);
}

//Timing Quick Sort
double timeQuickSort(int original[], int n){

    double times[3];

    for(int run = 0; run < 3; run++){

        int* arr = new int[n];
        memcpy(arr, original, n * sizeof(int));

        auto start = high_resolution_clock::now();

        quickSort(arr, 0, n-1);

        auto end = high_resolution_clock::now();

        times[run] = duration<double>(end-start).count();

        delete[]arr;
    }
        return median(times[0], times[1], times[2]);
}

//Timing Shell Sort
double timeShellSort(int original[], int n){

    double times[3];

    for(int run = 0; run < 3; run++){

        int* arr = new int[n];
        memcpy(arr, original, n * sizeof(int));

        auto start = high_resolution_clock::now();

        shellSort(arr,n);

        auto end = high_resolution_clock::now();

        times[run] = duration<double>(end-start).count();

        delete[]arr;
    }
        return median(times[0], times[1], times[2]);
}

//Timing Heap Sort
double timeHeapSort(int original[], int n){

    double times[3];

    for(int run = 0; run < 3; run++){

        int* arr = new int[n];
        memcpy(arr, original, n * sizeof(int));

        auto start = high_resolution_clock::now();

        heapSort(arr,n);

        auto end = high_resolution_clock::now();

        times[run] = duration<double>(end-start).count();

        delete[]arr;
    }
        return median(times[0], times[1], times[2]);
}

//Timing Counting Sort
double timeCountingSort(int original[], int n){

    double times[3];

    for(int run = 0; run < 3; run++){

        int* arr = new int[n];
        memcpy(arr, original, n * sizeof(int));

        auto start = high_resolution_clock::now();

        countingSort(arr,n);

        auto end = high_resolution_clock::now();

        times[run] = duration<double>(end-start).count();

        delete[]arr;
    }
        return median(times[0], times[1], times[2]);
}

//Timing Radix Sort
double timeRadixSort(int original[], int n){

    double times[3];

    for(int run = 0; run < 3; run++){

        int* arr = new int[n];
        memcpy(arr, original, n * sizeof(int));

        auto start = high_resolution_clock::now();

        radixSort(arr,n);

        auto end = high_resolution_clock::now();

        times[run] = duration<double>(end-start).count();

        delete[]arr;
    }
        return median(times[0], times[1], times[2]);
}

//Now we run all the six sorting algorithms on one dataset
void bench(const string& datasetName, int n){

    int* original = new int[n];

    //Create the datasets
    if(datasetName == "Random"){
        generateRandom(original, n);
    }
    else if(datasetName == "Sorted"){
        generateSorted(original, n);
    }
    else if(datasetName == "Reverse Sorted"){
        generateReverseSorted(original, n);
    }
    else if(datasetName == "Nearly Sorted"){
        generateNearlySorted(original, n);
    }

    cout << "\nDataset: " << datasetName << endl;
    cout << "Input Size: " << n << endl;

    cout << fixed << setprecision(6);

   /* cout << "Bubble Sort: " << timeBubbleSort(original, n) << " seconds\n";
    cout << "Selection Sort: " << timeSelectionSort(original, n) << " seconds\n";
    cout << "Insertion Sort: " << timeInsertionSort(original, n) << " seconds\n";
    cout << "Merge Sort: " << timeMergeSort(original, n) << " seconds\n";
    cout << "Quick Sort: " << timeQuickSort(original, n) << " seconds\n";
    cout << "Shell Sort: " << timeShellSort(original, n) << " seconds\n";
    */
    // cout << "Heap Sort: " << timeHeapSort(original, n) << " seconds\n";
    // cout << "Counting Sort: " << timeCountingSort(original, n) << " seconds\n";
    cout << "Radix Sort: " << timeRadixSort(original, n) << " seconds\n";

    delete[] original;
}

int main() {

    srand(42); //Allows us to reproduce our datasets

    //We will start with these sizes for the arrays
    int sizes[] = {1000, 10000, 100000};

    string datasets[] = {"Random","Sorted","Reverse Sorted","Nearly Sorted"};

    for(int n: sizes){

        for(string datasets : datasets){
            bench(datasets, n);
        }
    }


    return 0;

}