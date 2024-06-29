#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

bool checkEqualityOfArrays(const vector<int>& arr1, const vector<int>& arr2) {
    if (arr1.size() != arr2.size()) {
        return false;
    }

    unordered_set<int> set1(arr1.begin(), arr1.end());
    unordered_set<int> set2(arr2.begin(), arr2.end());

    return set1 == set2;
}

int main() {
    vector<int> array1 = {2, 4, 1, 3};
    vector<int> array2 = {3, 1, 4, 2};

    if (checkEqualityOfArrays(array1, array2)) {
        cout << "Both arrays have the same set of numbers." << std::endl;
    } else {
        cout << "Arrays have different sets of numbers." << std::endl;
    }

    return 0;
}