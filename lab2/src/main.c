#include <string.h>
#include <stdio.h>

void quickSort(int a, int b, char *arr){
    int c = arr[(a+b) / 2];
    int i = a;
    int j = b;
    do {
        while (arr[i] < c) i++;
        while (arr[j] > c) j--;
        if (i <= j){
            char tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);
    if (j > a) quickSort(a,j,arr);
    if (i < b) quickSort(i,b,arr);
}

char f(char *arr, int l){
    int i, j, stop = 0;
    for (j = l - 2; j >= 0 && stop != 1; j--){
        for (i = l - 1; i > j && stop != 1; i--){
            if (arr[i] > arr[j]){
                char tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
                stop = 1;
            }
        }
    }
    if (stop == 0) return 1;
    quickSort(j+2,l-1,arr);
    return 0;
}

int main(void) {
    int i, j, len, count;
    char input[12];
    if (scanf("%11s%d", input, &count) != 2) {
        printf("bad input");
        return 0;
    }
    len = strlen(input);
    for (i = 0; i < len; i++){
        if (input[i] < '0' || input[i] > '9'){
            printf("bad input");
            return 0;
        }
        for (j = i + 1; j < len; j++){
            if (input[i] == input[j] || input[i] < '0' || input[i] > '9'){
                printf("bad input");
                return 0;
            }
        }
    }
    while (f(input, len) == 0 && count > 0){
        for (i = 0; i < len; i++){
            printf("%c", input[i]);
        }
        printf("\n");
        count--;
    }
    return 0;
}
