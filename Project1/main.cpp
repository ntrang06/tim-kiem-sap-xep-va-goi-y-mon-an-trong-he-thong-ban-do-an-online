#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <chrono> 
#include <cstdlib>
#include <ctime>
#include "trie.h"
#include "food.h"
#include "recommend.h"

using namespace std;
using namespace chrono;
vector<Food> getFoodList();

void quickSort(vector<Food>&, int, int);
void mergeSort(vector<Food>&, int, int);
void quickSortRating(vector<Food>&, int, int);
void mergeSortPrice(vector<Food>&, int, int);
int binarySearch(vector<Food>&, string);

// Trie
TrieNode* createNode();
void insertTrie(TrieNode*, string);
vector<string> searchPrefix(TrieNode*, string);

// Recommend
vector<Food> recommendRuleBased(vector<Food>&, string);
vector<Food> recommendScoring(vector<Food>&, string);

// ===== IN DANH SÁCH =====
void printList(vector<Food>& arr) {
    for (auto f : arr) {
        cout << f.name
            << " | Gia: " << f.price
            << " | Rating: " << f.rating << endl;
    }
}

int main() {
    vector<Food> foods = getFoodList();
    srand(time(0));
    int choice;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Sap xep theo gia mon an (Quick vs Merge)\n";
        cout << "2. Tim kiem mon an (Binary vs Trie)\n";
        cout << "3. Goi y mot vai mon (Rule vs Scoring)\n";
        cout << "0. Thoat\n";
        cout << "Choose: ";
        cin >> choice;

        // ================= SORTING =================
        if (choice == 1) {
            int type;
            cout << "\n1. Sap xep theo gia\n";
            cout << "2. Sap xep theo danh gia\n";
            cout << "Chon: ";
            cin >> type;

            vector<Food> arr1 = foods;
            vector<Food> arr2 = foods;

            double timeQuick, timeMerge;

            if (type == 1) {
                // ===== SORT THEO PRICE =====

                auto start1 = high_resolution_clock::now();
                quickSort(arr1, 0, arr1.size() - 1);
                auto end1 = high_resolution_clock::now();
                timeQuick = duration<double, milli>(end1 - start1).count();

                auto start2 = high_resolution_clock::now();
                mergeSortPrice(arr2, 0, arr2.size() - 1);
                auto end2 = high_resolution_clock::now();
                timeMerge = duration<double, milli>(end2 - start2).count();

                cout << "\n===== SAP XEP THEO GIA =====\n";
                printList(arr1);
            }
            else if (type == 2) {
                // ===== SORT THEO RATING =====

                auto start1 = high_resolution_clock::now();
                quickSortRating(arr1, 0, arr1.size() - 1);
                auto end1 = high_resolution_clock::now();
                timeQuick = duration<double, milli>(end1 - start1).count();

                auto start2 = high_resolution_clock::now();
                mergeSort(arr2, 0, arr2.size() - 1);
                auto end2 = high_resolution_clock::now();
                timeMerge = duration<double, milli>(end2 - start2).count();

                cout << "\n===== SAP XEP THEO DANH GIA =====\n";
                printList(arr1);
            }
            else {
                cout << "Lua chon khong hop le!\n";
                continue;
            }
            cout << "\n--- THOI GIAN ---\n";
            cout << "Quick Sort: " << timeQuick << " ms\n";
            cout << "Merge Sort: " << timeMerge << " ms\n";
        }

        // ================= SEARCH =================
        else if (choice == 2) {
            string keyword;
            cout << "Nhap tu khoa: ";
            cin >> keyword;

            vector<Food> arrBinary = foods;
            sort(arrBinary.begin(), arrBinary.end(), [](Food a, Food b) {
                return a.name < b.name;
                });

            auto start1 = high_resolution_clock::now();
            int idx = binarySearch(arrBinary, keyword);
            auto end1 = high_resolution_clock::now();
            double timeBinary = duration<double, milli>(end1 - start1).count();

            TrieNode* root = createNode();
            for (auto f : foods)
                insertTrie(root, f.name);

            auto start2 = high_resolution_clock::now();
            vector<string> names = searchPrefix(root, keyword);
            auto end2 = high_resolution_clock::now();
            double timeTrie = duration<double, milli>(end2 - start2).count();

            cout << "\n===== KET QUA =====\n";

            bool found = false;

            for (auto name : names) {
                for (auto f : foods) {
                    if (f.name == name) {
                        cout << f.name
                            << " | Gia: " << f.price
                            << " | Rating: " << f.rating << endl;
                        found = true;
                    }
                }
            }

            if (!found && idx != -1) {
                cout << arrBinary[idx].name
                    << " | Gia: " << arrBinary[idx].price
                    << " | Rating: " << arrBinary[idx].rating << endl;
                found = true;
            }

            if (!found)
                cout << "Khong tim thay!\n";

            cout << "\n--- THOI GIAN ---\n";
            cout << "Binary Search: " << timeBinary << " ms\n";
            cout << "Trie Search: " << timeTrie << " ms\n";
        }

        // ================= RECOMMEND =================
        else if (choice == 3) {
            string keyword = foods[rand() % foods.size()].name;

            cout << "\nKeyword tu dong: " << keyword << endl;

            // ===== RULE =====
            auto start1 = high_resolution_clock::now();
            vector<Food> resRule = recommendRuleBased(foods, keyword);
            auto end1 = high_resolution_clock::now();
            double timeRule = duration<double, milli>(end1 - start1).count();

            // ===== SCORING =====
            auto start2 = high_resolution_clock::now();
            vector<Food> resScore = recommendScoring(foods, keyword);
            auto end2 = high_resolution_clock::now();
            double timeScore = duration<double, milli>(end2 - start2).count();
            cout << "\n===== GOI Y MON AN (TOP 10-15) =====\n";

            for (auto f : resScore) {
                cout << f.name
                    << " | Gia: " << f.price
                    << " | Rating: " << f.rating << endl;
            }
            cout << "\n--- THOI GIAN ---\n";
            cout << "Rule-based: " << timeRule << " ms\n";
            cout << "Scoring: " << timeScore << " ms\n";
        }

        else if (choice == 0) {
            cout << "Thoat chuong trinh...\n";
        }

        else {
            cout << "Lua chon khong hop le!\n";
        }

    } while (choice != 0);

    return 0;
}