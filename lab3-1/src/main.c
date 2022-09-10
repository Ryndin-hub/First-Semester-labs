#include <stdio.h>

void heapify(int *arr, int n, int p){
    int max = p;
    int c1 = p * 2 + 1;
    int c2 = p * 2 + 2;
    if (c1 < n && arr[max] < arr[c1]) max = c1;
    if (c2 < n && arr[max] < arr[c2]) max = c2;
    if (max != p){
        int tmp = arr[max];
        arr[max] = arr[p];
        arr[p] = tmp;
        heapify(arr,n,max);
    }
}

void heapSort(int *arr, int n){
    int i;
    for (i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (i = n - 1; i >= 0; i--){
        int tmp = arr[i];
        arr[i] = arr[0];
        arr[0] = tmp;
        heapify(arr, i, 0);
    }
}

int main(void){
    int i, n;
    int scannedCount = scanf("%d", &n);
    if (scannedCount != 1) return 1;
    if (n > 2000000 || n < 0) return 1;
    int arr[n];
    for (i = 0; i < n; i++) scannedCount += scanf("%d", &arr[i]);
    if (scannedCount != n + 1) return 1;
    heapSort(arr, n);
    for (i = 0; i < n; i++) printf("%d ", arr[i]);
    return 0;
}
