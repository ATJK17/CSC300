#include "heap.h"

HEAP::HEAP(int size) {
    capacity = size;
    heapSize = 0;
    isMax = true; // always starts out as a max heap
    array = new int[capacity];
}

HEAP::~HEAP() {
    delete[] array;
}

int HEAP::leftChild(int index) {
    return 2*index + 1;
}
int HEAP::rightChild(int index) {
    return 2*index + 2;
}
int HEAP::parent(int index) {
    return (index - 1) / 2;
}

void HEAP::insertH(int data) {
    if (heapSize == capacity) {
        cout << "Heap overflow - can't insert"<< endl;
        return;
    }

    array[heapSize] = data;
    heapifyUp(heapSize);
    heapSize++;
}

void HEAP::heapifyUp(int index) {
    while (index != 0) {
        int p = parent(index);
        // max heap: parent should be bigger, min heap: parent should be smaller
        // so "out of order" flips depending on which one we're in
        bool outOfOrder = isMax ? (array[p] < array[index])
                                : (array[p] > array[index]);
        if (!outOfOrder)
            break;
        swap(array[p], array[index]);
        index = p;
    }
}

int HEAP::peek() {
    if (heapSize <= 0) {
        cout << "Heap is empty" << endl;
        return -1;
    }

    return array[0];
}

void HEAP::deleteMax() {
    if (heapSize <= 0) {
        cout << "Heap is empty - nothing to delete" << endl;
        return;
    }

    if (heapSize == 1) {
        heapSize--;
        return;
    }

    // put the last element at the root, then push it back down
    array[0] = array[heapSize - 1];
    heapSize--;

    if (isMax) heapifyDown(0);
    else       heapifyDownMin(0);
}

void HEAP::deleteH(int data) {
    int index = -1;

    // search for data - linear search :( O(n)
    for (int i = 0; i < heapSize; i++) {
        if (array[i] == data) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Element not found - can't delete"  << endl;
        return;
    }

    array[index] = array[heapSize - 1];
    heapSize--;

    // the last element we moved here could belong higher up OR lower down,
    // so try both. whichever one isn't needed just does nothing
    // (also skip it if we just deleted the very last spot)
    if (index < heapSize) {
        if (isMax) heapifyDown(index);
        else       heapifyDownMin(index);
        heapifyUp(index);
    }
}


// Task 1 - bubble down for the max heap
void HEAP::heapifyDown(int index) 
{
    while (true) {
        int l = leftChild(index);
        int r = rightChild(index);
        int largest = index;

        // find the biggest out of the node and its two kids
        // (check l and r are inside the heap first)
        if (l < heapSize && array[l] > array[largest])
            largest = l;
        if (r < heapSize && array[r] > array[largest])
            largest = r;

        // node is already bigger than both kids so we're done
        if (largest == index)
            break;

        swap(array[index], array[largest]);
        index = largest; // keep going from where it landed
    }
}

// Task 5 helper - same as heapifyDown but for a min heap, so we look for the smallest
void HEAP::heapifyDownMin(int index)
{
    while (true) {
        int l = leftChild(index);
        int r = rightChild(index);
        int smallest = index;

        if (l < heapSize && array[l] < array[smallest])
            smallest = l;
        if (r < heapSize && array[r] < array[smallest])
            smallest = r;

        if (smallest == index)
            break;

        swap(array[index], array[smallest]);
        index = smallest;
    }
}

 
// Task 2 - Floyd's method. Instead of inserting one at a time (O(n log n))
// just dump everything in and fix it from the bottom up, which is O(n)
void HEAP::buildH(int arr[], int n) 
{
    if (n > capacity) {
        cout << "Array larger than heap capacity - can't build" << endl;
        return;
    }

    isMax = true;
    heapSize = n;
    for (int i = 0; i < n; i++)
        array[i] = arr[i];

    // leaves are already valid heaps, so start at the last parent (n/2 - 1)
    // and work back to the root
    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyDown(i);

    // copy it back so main can print the heapified array
    for (int i = 0; i < n; i++)
        arr[i] = array[i];
}

// Task 3 - swap a value for a new one
void HEAP::replace(int oldData, int newData)
{
    int index = -1;

    // linear search again, same as deleteH
    for (int i = 0; i < heapSize; i++) {
        if (array[i] == oldData) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        cout << "Element not found - can't replace" << endl;
        return;
    }

    array[index] = newData;

    // new value might be bigger or smaller than the old one so we don't
    // know which way it has to move - just try both
    if (isMax) heapifyDown(index);
    else       heapifyDownMin(index);
    heapifyUp(index);
}

// Task 4 - heap sort, sorts arr smallest to largest
void HEAP::heapSort(int arr[], int n)
{
    // heapifyDown uses the heap's own array/heapSize and I don't want to mess
    // that up, so this is a little standalone version that works on any array
    // and only looks at the first 'size' elements
    auto siftDown = [](int a[], int size, int i) {
        while (true) {
            int l = 2*i + 1, r = 2*i + 2, largest = i;
            if (l < size && a[l] > a[largest]) largest = l;
            if (r < size && a[r] > a[largest]) largest = r;
            if (largest == i) break;
            swap(a[i], a[largest]);
            i = largest;
        }
    };

    // step 1: turn arr into a max heap (Floyd again)
    for (int i = n / 2 - 1; i >= 0; i--)
        siftDown(arr, n, i);

    // step 2: biggest is always at the front, so move it to the end,
    // shrink the heap by one, and fix the root. repeat
    for (int end = n - 1; end > 0; end--) {
        swap(arr[0], arr[end]);
        siftDown(arr, end, 0);
    }

    // main doesn't print anything after this so print the sorted array here
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

// Task 5 - flip between max and min heap
void HEAP::switchMinMax()
{
    isMax = !isMax;

    // rebuild with Floyd's method using whichever heapify matches the new mode
    for (int i = heapSize / 2 - 1; i >= 0; i--) {
        if (isMax) heapifyDown(i);
        else       heapifyDownMin(i);
    }
}

void HEAP::printHeap(int index, int depth) {
    if (index >= heapSize)
        return;

    printHeap(rightChild(index), depth + 1);

    for (int i = 0; i < depth; i++) {
        cout << "  "; // indentation based on depth
    }

    cout << array[index] << endl;

    printHeap(leftChild(index), depth + 1);
}