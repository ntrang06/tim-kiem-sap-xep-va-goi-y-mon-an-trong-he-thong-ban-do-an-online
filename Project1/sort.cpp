#include "food.h"
#include <vector>
using namespace std;

// QUICK SORT (theo price)
int partition(vector<Food>& arr, int low, int high) {
    int pivot = arr[high].price;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].price < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<Food>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
// QUICK SORT THEO RATING
int partitionRating(vector<Food>& arr, int low, int high) {
    float pivot = arr[high].rating;
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j].rating > pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortRating(vector<Food>& arr, int low, int high) {
    if (low < high) {
        int pi = partitionRating(arr, low, high);
        quickSortRating(arr, low, pi - 1);
        quickSortRating(arr, pi + 1, high);
    }
}
// MERGE SORT (theo rating)
void merge(vector<Food>& arr, int l, int m, int r) {
    vector<Food> temp;
    int i = l, j = m + 1;

    while (i <= m && j <= r) {
        if (arr[i].rating > arr[j].rating)
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    while (i <= m) temp.push_back(arr[i++]);
    while (j <= r) temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); k++)
        arr[l + k] = temp[k];
}

void mergeSort(vector<Food>& arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
// MERGE SORT THEO PRICE
void mergePrice(vector<Food>& arr, int l, int m, int r) {
    vector<Food> temp;
    int i = l, j = m + 1;

    while (i <= m && j <= r) {
        if (arr[i].price < arr[j].price)
            temp.push_back(arr[i++]);
        else
            temp.push_back(arr[j++]);
    }

    while (i <= m) temp.push_back(arr[i++]);
    while (j <= r) temp.push_back(arr[j++]);

    for (int k = 0; k < temp.size(); k++)
        arr[l + k] = temp[k];
}

void mergeSortPrice(vector<Food>& arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSortPrice(arr, l, m);
        mergeSortPrice(arr, m + 1, r);
        mergePrice(arr, l, m, r);
    }
}