#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include "food.h"

using namespace std;
using namespace chrono;
void quickSort(vector<Food>&, int, int);
void mergeSort(vector<Food>&, int, int);
int binarySearch(vector<Food>& arr, string target);

// đo quick sort
double testQuick(vector<Food> arr) {
    auto start = high_resolution_clock::now();

    quickSort(arr, 0, arr.size() - 1);

    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();
}

// đo merge sort
double testMerge(vector<Food> arr) {
    auto start = high_resolution_clock::now();

    mergeSort(arr, 0, arr.size() - 1);

    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();
}

// đo binary search
double testBinary(vector<Food> arr, string key) {
    sort(arr.begin(), arr.end(), [](Food a, Food b) {
        return a.name < b.name;
        });

    auto start = high_resolution_clock::now();

    binarySearch(arr, key);

    auto end = high_resolution_clock::now();
    return duration<double, milli>(end - start).count();
}