
using namespace std;

#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
//standard heap sort algorithm
void heapify1 (int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify1(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify1 (arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify1(arr, i, 0);
    }
}
//in place heap sort
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void inPlaceHeapSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    int arrr[]={12, 11, 13, 5, 6, 7};
    int n = sizeof(arrr) / sizeof(arrr[0]);
    inPlaceHeapSort(arr);

    auto start = chrono::high_resolution_clock::now();
    // Call in-place heap-sort function here
    inPlaceHeapSort(arr);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    cout << "Time taken by in-place heap-sort: " << elapsed_seconds.count() << "s\n";

    start = chrono::high_resolution_clock::now();
    heapSort(arrr, n);
    end = chrono::high_resolution_clock::now();
    elapsed_seconds = end - start;
    cout << "Time taken by standard heap-sort: " << elapsed_seconds.count() << "s\n";

    return 0;
}