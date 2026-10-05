#include "sorts.h"
#include <vector>

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSort(int arr[], int n) {
    // Loop through the array n-1 times
    for (int i = 0; i < n - 1; i++) {
        // Compare adjacent elements
        for (int j = 0; j < n - i - 1; j++) {
            // Swap if they are in the wrong order
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void optimizedBubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {

                // Swap arr[j] and arr[j+1]
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }
        // If no elements were swapped, the array is already sorted
        if (!swapped) break;
    }
}


void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        // find the smallest
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        
        // Swap with first element
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; ++i) {
        int key = arr[i];  // The element to be inserted
        int j = i - 1;

        // Move elements of arr[0..i-1], that are greater 
        // than key, to one position ahead of their 
        // current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        
        // Insert at the right spot
        arr[j + 1] = key;
    }
}


void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int leftArray[n1], rightArray[n2];

    // Copy data to temporary arrays leftArray[] and rightArray[]
    for (int i = 0; i < n1; i++)
        leftArray[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArray[j] = arr[mid + 1 + j];

    // Merge the temporary arrays back into arr[left..right]
    int i = 0; // Initial index of first subarray
    int j = 0; // Initial index of second subarray
    int k = left; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            i++;
        } else {
            arr[k] = rightArray[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of leftArray[], if any
    while (i < n1) {
        arr[k] = leftArray[i];
        i++;
        k++;
    }

    // Copy the remaining elements of rightArray[], if any
    while (j < n2) {
        arr[k] = rightArray[j];
        j++;
        k++;
    }
}


void mergeSort(int arr[], int left, int right) {
    if (left >= right)
        return; // Base case

    int mid = left + (right - left) / 2; 

    // Sort first and second halves
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // Merge the sorted halves
    merge(arr, left, mid, right);
}


int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Pivot is the last element
    int i = low - 1; // Index of the smaller element

    for (int j = low; j <= high - 1; j++) {
        // If the current element is smaller than or equal to the pivot
        if (arr[j] <= pivot) {
            i++; // Increment index of the smaller element
            swap(arr[i], arr[j]);
        }
    }
    // Swap the pivot element with the element at i + 1 so that the pivot is at its correct position
    swap(arr[i + 1], arr[high]);
    return (i + 1); // Return the partitioning index
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        // Partition and get the pivot index
        int pi = partition(arr, low, high);

        // Recursively sort the subarrays before and after the partition
        quickSort(arr, low, pi - 1); // Sort the left half
        quickSort(arr, pi + 1, high); // Sort the right half
    }
}


void shellSort(int arr[], int n) {
    // Start with a large gap, then reduce the gap
    for (int gap = n / 2; gap > 0; gap /= 2) {
        // Perform a gapped insertion sort
        for (int i = gap; i < n; i++) {
            int temp = arr[i];
            int j;
            // Shift earlier gap-sorted elements up until the correct location for arr[i] is found
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}

//Heap Sort
//Fixes the heap starting at index 1
static void heapify(int arr[], int size, int i){

    while(true){
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if(left < size && arr[left] > arr[largest])
            largest = left;
        if(right < size && arr[right] > arr[largest])
            largest = right;

        if(largest == i) 
            break;

        swap(arr[i], arr[largest]);
        i = largest;

    }
}

void heapSort(int arr[], int n){

    //Build a max-heap
    for(int i = n/2-1; i >= 0; i--)
        heapify(arr, n, i);

    //Repeatedly move the max to the end, then shrink the heap
    for(int end = n-1; end > 0; end--){
        swap(arr[0], arr[end]);
        heapify(arr, end, 0);
    }
}

//Counting Sort
void countingSort(int arr[], int n){

    if(n <= 1)
        return;

    //Find range of values
    int minVal = arr[0], maxVal = arr[0];

    for(int i = 1; i < n; i++){
        if(arr[i] < minVal)
            minVal = arr[i];
        if(arr[i] > maxVal)
            maxVal = arr[i];
    }

    int range = maxVal - minVal+1;

    //Count how many times each value appears
    std::vector<int> count(range, 0);

    for(int i = 0; i < n; i++)
        count[arr[i] - minVal]++;

    //Turn counts into running totals to find final position of each value
    for(int i = 1; i < range; i++)
        count[i] += count[i-1];

    //Place elements into output, going right to left so eqaul values keep order
    std::vector<int> output(n);
    for(int i = n - 1; i >= 0; i --){
        output[count[arr[i] - minVal] - 1] = arr[i];
        count[arr[i] - minVal]--;
    }

    //Copy Back to array

    for(int i = 0; i < n; i++)
        arr[i] = output[i];
}

//Radix Sort
//Sorts numbers one digit at a time
static void countingPass(int arr[], int n, long long exp){

    std::vector<int> output(n);
    int count[10] = {0};

    for(int i = 0; i < n; i++)
        count[(arr[i]/exp) % 10]++;

    for(int d = 1; d < 10; d++)
        count[d] += count[d-1];

    for(int i = n - 1; i >= 0 ; i--){
        int digit = (arr[i]/exp) % 10;
        output[--count[digit]] = arr[i];
    }

    for(int i = 0; i < n; i++){
        arr[i] = output[i];
    }
}

void radixSort(int arr[], int n){

    if(n <= 1)
        return;
    
        int maxVal = arr[0];
    
    for(int i = 1; i < n; i++){
            if(arr[i] > maxVal)
            maxVal = arr[i];
    }

    for(int exp = 1; maxVal/exp > 0; exp *= 10)
        countingPass(arr, n, exp);
    }

void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}