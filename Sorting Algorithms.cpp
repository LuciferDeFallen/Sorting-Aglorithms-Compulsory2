#include <iostream>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <stack>
#include <vector>

// Returns random number for list generation
int generateRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Returns a randomized list of provided length
void createRandomList(int size, int* list) {
    for (int i = 0; i < size; ++i) {
        list[i] = generateRandomNumber(1, 1000); // Generates random number between 1 and 1000
    }
}

// Display list
// Used for debugging
void printList(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// Check if a list is sorted
bool isSorted(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        // Check if current item is larger than the next item
        if (arr[i] > arr[i + 1]) {
            return false; // The list is not sorted
        }
    }
    return true; // The list is sorted in ascending order
}

// Display if a list is sorted
void validateList(int arr[], int size) {
    if (isSorted(arr, size)) std::cout << "List is sorted!\n"; else std::cout << "List is not sorted!\n";
}


//
// Sorting Algs
//


// Partition array
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Get pivot item
    int i = (low - 1); // store lower index

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }

    std::swap(arr[i + 1], arr[high]);
    return (i + 1); // return pivot index
}

// Recursive quicksort alg
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// QuickSort call
void quickSort(int arr[], int size) {
    quickSort(arr, 0, size - 1);
}


// Iterative quicksort alg
// Iterative implementation of the quicksort algorithm that uses the same partition function
void iQuickSort(int arr[], int low, int high) {
    std::stack<std::pair<int, int>> stack;
    stack.push(std::make_pair(low, high));

    while (!stack.empty()) { // Loop runs until stack is empty
        low = stack.top().first;
        high = stack.top().second;
        stack.pop();

        int pivotIndex = partition(arr, low, high);

        // Pushing items left of the pivot onto the stack
        if (pivotIndex - 1 > low) {
            stack.push(std::make_pair(low, pivotIndex - 1));
        }

        // Pushing items right of the pivot onto the stack
        if (pivotIndex + 1 < high) {
            stack.push(std::make_pair(pivotIndex + 1, high));
        }
    }
}

// iQuickSort call
void iQuickSort(int arr[], int size) {
    iQuickSort(arr, 0, size - 1);
}


// Merge sorted subs
void merge(int arr[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    // Create temporary arrays
    std::vector<int> L(n1);
    std::vector<int> R(n2);

    // Copy to temp arrays
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[middle + 1 + j];
    }

    // Merge temp arrays into main array
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements from left temp array
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements from right temp array
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// Recursive MergeSort implementation
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;

        // Divide array and sort each half using mergesort
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);

        // Merge sorted halves
        merge(arr, left, middle, right);
    }
}

// MergeSort call
void mergeSort(int arr[], int size) {
    mergeSort(arr, 0, size - 1);
}

// Sorts provided list using provided sorting function
// Displays sorting time in milliseconds and validates result
void sortList(int list[], int size, void (*sortingAlgorithm)(int[], int)) {

    std::cout << "Generating random list of size " << size << "...\n";
    createRandomList(size, list);
    std::cout << "Checking list: ";
    validateList(list, size);
    // printList(list1, size1); // Display original list

    std::cout << "Sorting list...\n";
    auto t0 = std::chrono::high_resolution_clock::now(); // Store current time
    sortingAlgorithm(list, size); // Sort the list
    auto t1 = std::chrono::high_resolution_clock::now(); // Store time after sorting
    std::chrono::duration<double> delta = t1 - t0; // Calculate elapsed time

    std::cout << "Finished in " << delta.count() * 1000 << "ms\n";
    std::cout << "Checking list: ";
    validateList(list, size); 
}

// I used this to display just the size and time to copy into the pdf
void sortList1(int list[], int size, void (*sortingAlgorithm)(int[], int)) {
    createRandomList(size, list);
    // printList(list1, size1); // Display original list

    auto t0 = std::chrono::high_resolution_clock::now(); // Store current time
    sortingAlgorithm(list, size); // Sort the list
    auto t1 = std::chrono::high_resolution_clock::now(); // Store time after sorting
    std::chrono::duration<double> delta = t1 - t0; // Calculate elapsed time

    std::cout << "Size: " << size << " Time: " << delta.count() * 1000 << "ms\n";
}


//
// Main function
//


int main() {
    // Use time as seed for random generator
    std::srand(std::time(0));

    // Create linear lists of different sizes
    const int size1 = 10;
    const int size2 = 100;
    const int size3 = 1000;
    const int size4 = 10000;

    int list1[size1];
    int list2[size2];
    int list3[size3];
    int list4[size4];

    std::cout << "Recursive Quicksort:\n\n";
    sortList(list1, size1, quickSort);
    std::cout << "\n";
    sortList(list2, size2, quickSort);
    std::cout << "\n";
    sortList(list3, size3, quickSort);
    std::cout << "\n";
    sortList(list4, size4, quickSort);
    std::cout << "\n\n\n\n";

    std::cout << "Iterative Quicksort:\n\n";
    sortList(list1, size1, iQuickSort);
    std::cout << "\n";
    sortList(list2, size2, iQuickSort);
    std::cout << "\n";
    sortList(list3, size3, iQuickSort);
    std::cout << "\n";
    sortList(list4, size4, iQuickSort);
    std::cout << "\n\n\n\n";

    std::cout << "Mergesort:\n\n";
    sortList(list1, size1, mergeSort);
    std::cout << "\n";
    sortList(list2, size2, mergeSort);
    std::cout << "\n";
    sortList(list3, size3, mergeSort);
    std::cout << "\n";
    sortList(list4, size4, mergeSort);
    std::cout << "\n\n\n\n";


    std::cout << "\n";

    return 0;
}
