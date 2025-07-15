#include <iostream>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;
using namespace std::chrono;

void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}

void print(int arr[], int size) {
    for (int i = 0; i < size; ++i)
        cout << arr[i] << " ";
    cout << "\n";
}

int binSearch(int arr[], int x, int n) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (arr[m] == x) return m;
        if (arr[m] < x) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

int expSearch(int arr[], int x, int n) {
    if (arr[0] == x) return 0;
    int bound = 1;
    while (bound < n && arr[bound] < x)
        bound *= 2;
    int l = bound / 2;
    int r = min(bound, n - 1);
    while (l <= r) {
        int m = (l + r) / 2;
        if (arr[m] == x) return m;
        if (arr[m] < x) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

int partition(int arr[], int l, int r) {
    int pivot = arr[r];
    int i = l - 1;
    for (int j = l; j < r; ++j)
        if (arr[j] <= pivot)
            swap(arr[++i], arr[j]);
    swap(arr[i + 1], arr[r]);
    return i + 1;
}

void quickSort(int arr[], int l, int r) {
    if (l < r) {
        int p = partition(arr, l, r);
        quickSort(arr, l, p - 1);
        quickSort(arr, p + 1, r);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];
    for (int i = 0; i < n1; ++i) L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main() {
    srand(time(0));
    int opt, N;
    cout << "Pick a sorting algorithm:\n1 - QuickSort\n2 - MergeSort\nChoice: ";
    cin >> opt;

    cout << "Enter how many numbers to generate: ";
    cin >> N;

    int* arr = new int[N];
    for (int i = 0; i < N; ++i)
        arr[i] = rand() % 10000;

    cout << "\nGenerated array:\n";
    print(arr, N);

    auto startSort = high_resolution_clock::now();

    if (opt == 1) {
        quickSort(arr, 0, N - 1);
        cout << "Sorted using QuickSort.\n";
    } else if (opt == 2) {
        mergeSort(arr, 0, N - 1);
        cout << "Sorted using MergeSort.\n";
    } else {
        cout << "Invalid sorting choice. Using built-in sort.\n";
        sort(arr, arr + N);
    }

    auto endSort = high_resolution_clock::now();

    cout << "\nSorted array:\n";
    print(arr, N);
    cout << "\nSorting Time: " << duration_cast<milliseconds>(endSort - startSort).count() << " ms\n";

    int searchOpt;
    cout << "\nPick search algorithm:\n1 - Binary Search\n2 - Exponential Search\nChoice: ";
    cin >> searchOpt;

    int x;
    cout << "Enter number to search: ";
    cin >> x;

    auto startSearch = high_resolution_clock::now();
    int pos = (searchOpt == 1) ? binSearch(arr, x, N) : expSearch(arr, x, N);
    auto endSearch = high_resolution_clock::now();

    if (pos == -1)
        cout << "Number not found.\n";
    else
        cout << "Number found at index " << pos << ".\n";

    cout << "Search Time: " << duration_cast<microseconds>(endSearch - startSearch).count() << " ms\n";

    delete[] arr;
    return 0;
}