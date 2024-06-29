#include <iostream>
#include <vector>
using namespace std;

void rearrangeAr(vector<int>& arr, int k, int start, int end) {
    if (start >= end) return;

    if (arr[start] > k && arr[end] <= k) {
        swap(arr[start], arr[end]);
        rearrangeAr(arr, k, start + 1, end - 1);
    } else if (arr[start] <= k) {
        rearrangeAr(arr, k, start + 1, end);
    } else if (arr[end] > k) {
        rearrangeAr(arr, k, start, end - 1);
    }
}

int main() {
    vector<int> arr = {4, 7, 2, 9, 5, 1, 8};
    int k = 5;

    rearrangeAr(arr, k, 0, arr.size() - 1);

    for (int num : arr) {
        cout << num << " ";
    }

    return 0;
}