#include <stdio.h>
#include <string.h>
#include <math.h>

#define max_len 13
#define digits_after_comma 12

int converter(char const number[], int CC1, int CC2, int len, char result[]){
    char digits[] = "0123456789abcdef";
    int i, j, commaIndex;
    long long int beforeCommaCC10 = 0;
    double afterCommaCC10 = 0;
    for (commaIndex = 0; commaIndex < len; commaIndex++){
        if (number[commaIndex] == '.') break;
    }
    for (i = 0; i < commaIndex; i++){
        beforeCommaCC10 = beforeCommaCC10 * CC1 + number[i];
    }
    for (i = len - 1; i > commaIndex; i--){
        afterCommaCC10 = (afterCommaCC10 + number[i]) / CC1;
    }
    i = 0;
    if (beforeCommaCC10 == 0) result[i++] = digits[0];
    while (beforeCommaCC10 != 0){
        result[i++] = digits[(int) fmod(beforeCommaCC10, CC2)];
        beforeCommaCC10 = (beforeCommaCC10 - fmod(beforeCommaCC10, CC2)) / CC2;
    }
    for (j = 0; j < i / 2; j++){
        char tmp = result[j];
        result[j] = result[i - 1 - j];
        result[i - 1 - j] = tmp;
    }
    if (commaIndex == len) return i;
    result[i++] = '.';
    for (j = 0; j < digits_after_comma; j++){
        result[i++] = digits[(int)(afterCommaCC10 * CC2)];
        afterCommaCC10 = afterCommaCC10 * CC2 - (int)(afterCommaCC10 * CC2);
    }
    return i;
}

int charToIntInString(char x[], int len){
    int i;
    for (i = 0; i < len; i++){
        if (x[i] < '0' && x[i] != '.') return 1; //проверяет есть ли в исходной строке (0 - '0') т.к. после этой операции эту проверку больше невозможно будет выполнить
        else if (x[i] >= '0' && x[i] <= '9') x[i] -= '0';
        else if (x[i] >= 'a' && x[i] <= 'z') x[i] -= 'a' - 10;
        else if (x[i] >= 'A' && x[i] <= 'Z') x[i] -= 'A' - 10;
    }
    return 0;
}

int checkInputForErrors(char x[], int b1, int b2, int xLen){
    int i, countComma = 0;
    if (b1 < 2 || b1 > 16 || b2 < 2 || b2 > 16) return 1;
    if (xLen > max_len) return 1;
    if (x[0] == '.' || x[xLen - 1] == '.') return 1;
    for (i = 0; i < xLen; i++){
        if (x[i] == '.') countComma++;
        else if (x[i] < 0 || x[i] >= b1) return 1;
    }
    if (countComma > 1) return 1;
    return 0;
}

int main() {
    int b1, b2;
    char x[max_len + 1], result[100];
    if (scanf("%d%d%13s", &b1, &b2, x) != 3){
        printf("bad input");
        return 1;
    }
    int len = strlen(x);
    if (charToIntInString(x, len) == 1){
        printf("bad input");
        return 1;
    }
    if (checkInputForErrors(x, b1, b2, len) == 1){
        printf("bad input");
        return 1;
    }
    int resultLen = converter(x, b1, b2, len, result);
    int i;
    for (i = 0; i < resultLen; i++) printf("%c", result[i]);
    return 0;
}
