#include <stdio.h>

void quickSort(int a, int b, int *arr){
    int tmp;
    int c = arr[(a+b) / 2];
    int i = a;
    int j = b;
    do {
        while (arr[i] < c) i++;
        while (arr[j] > c) j--;
        if (i <= j){
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);
    if (j > a) quickSort(a,j,arr);
    if (i < b) quickSort(i,b,arr);
}

int main(void) {
    int N, i, d;
    int scannedCount = scanf("%d", &N);
    if (scannedCount != 1) {
        printf("not enough input data\n");
        return 1;
    }
    if (N > 2000000 || N < 0) return 1;
    int arr[N];
    for (i = 0; i < N; i++){
        scannedCount += scanf("%d", &d);
        arr[i] = d;
    }
    if (scannedCount != N + 1) {
        printf("not enough input data\n");
        return 1;
    }
    quickSort(0,N-1,arr);
    for (i = 0; i < N; i++){
        printf("%d ", arr[i]);
    }
    return 0;
}
