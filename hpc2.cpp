#include <iostream>
#include <omp.h>
#include <chrono>
using namespace std;
using namespace chrono;

/* ---------- PRINT ---------- */
void printArray(int arr[], int n) {
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

/* ---------- SEQUENTIAL BUBBLE ---------- */
void bubbleSort(int arr[], int n) {
    for(int i = 0; i < n-1; i++)
        for(int j = 0; j < n-i-1; j++)
            if(arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
}

/* ---------- PARALLEL BUBBLE ---------- */
void parallelBubbleSort(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        int start = i % 2;

        #pragma omp parallel for
        for(int j = start; j < n-1; j += 2) {
            if(arr[j] > arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
}

/* ---------- MERGE ---------- */
void merge(int arr[], int l, int m, int r) {
    int temp[1000];
    int i=l, j=m+1, k=0;

    while(i<=m && j<=r)
        temp[k++] = (arr[i] < arr[j]) ? arr[i++] : arr[j++];

    while(i<=m) temp[k++] = arr[i++];
    while(j<=r) temp[k++] = arr[j++];

    for(int i=0; i<k; i++)
        arr[l+i] = temp[i];
}

/* ---------- MERGE SORT ---------- */
void mergeSort(int arr[], int l, int r) {
    if(l < r) {
        int m = (l+r)/2;
        mergeSort(arr, l, m);
        mergeSort(arr, m+1, r);
        merge(arr, l, m, r);
    }
}

/* ---------- PARALLEL MERGE SORT ---------- */
void parallelMergeSort(int arr[], int l, int r) {
    if(l < r) {
        int m = (l+r)/2;

        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, l, m);

            #pragma omp section
            parallelMergeSort(arr, m+1, r);
        }

        merge(arr, l, m, r);
    }
}

/* ---------- MAIN ---------- */
int main() {
    int n;
    cout << "Enter size: ";
    cin >> n;

    int original[1000];
    cout << "Enter elements:\n";
    for(int i=0;i<n;i++) cin >> original[i];

    int a[1000], b[1000];

    // -------- Bubble Sort --------
    for(int i=0;i<n;i++){ a[i]=original[i]; b[i]=original[i]; }

    auto t1 = high_resolution_clock::now();
    bubbleSort(a, n);
    auto t2 = high_resolution_clock::now();

    auto t3 = high_resolution_clock::now();
    parallelBubbleSort(b, n);
    auto t4 = high_resolution_clock::now();

    cout << "\nBubble Sort:\n";
    printArray(a, n);

    cout << "Sequential: "<< duration_cast<microseconds>(t2-t1).count() << " us\n";
    cout << "Parallel:   "<< duration_cast<microseconds>(t4-t3).count() << " us\n";

    // -------- Merge Sort --------
    for(int i=0;i<n;i++){ 
        a[i]=original[i]; b[i]=original[i];
    }

    auto t5 = high_resolution_clock::now();
    mergeSort(a, 0, n-1);
    auto t6 = high_resolution_clock::now();

    auto t7 = high_resolution_clock::now();
    parallelMergeSort(b, 0, n-1);
    auto t8 = high_resolution_clock::now();

    cout << "\nMerge Sort:\n";
    printArray(a, n);

    cout << "Sequential: " << duration_cast<microseconds>(t6-t5).count() << " us\n";
    cout << "Parallel:  " << duration_cast<microseconds>(t8-t7).count() << " us\n";

    return 0;
}