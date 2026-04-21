#include "food.h"
#include <vector>
#include <string>

using namespace std;

// Sửa lại chính xác theo những gì Linker đang tìm kiếm trong ảnh lỗi
int binarySearch(vector<Food>& arr, string target) {
    int left = 0;
    int right = (int)arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid].name == target)
            return mid;
        else if (arr[mid].name < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}