#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define buf_size 1024

int setHash(unsigned char s[], int a, int b, int *p){
    int i, hash = 0;
    for (i = 0; i < b - a; i++){
        hash += ((int)s[i + a] % 3) * *p;
        *p *= 3;
    }
    *p /= 3;
    return hash;
}

void updateHash(int *hash, int p, unsigned char lastSym, unsigned char newSym){
    *hash = (*hash - (lastSym % 3)) / 3 + (newSym % 3) * p;
}

int readPat(unsigned char *pat){
    if (scanf("%16[^\n]s", pat) != 1) return 1;
    unsigned char tmp;
    if (scanf("%c", &tmp) != 1) return 1;
    return 0;
}

void readBuf(unsigned char *buf, int len){
    int i;
    for (i = 0; i < len; i++) buf[i] = buf[buf_size + i];
    if (scanf("%1024[^EOF]s", &buf[len]) != 1) exit(0);
}

void rabinKarp(){
    unsigned char pat[17], buf[buf_size+17];
    int i, pat_len, pat_hash, hash, p = 1, pos_buf = 0, pos_text = 2, tmp = 1;
    if (readPat(pat) == 1){
        printf("%d", setHash(pat,0,strlen((char*)pat),&p));
        return;
    }
    pat_len = strlen((char*) pat);
    pat_hash = setHash(pat, 0, pat_len, &p);
    printf("%d ", pat_hash);
    readBuf(buf, pat_len);
    hash = setHash(buf, pat_len, pat_len * 2, &tmp);
    pos_buf = pat_len * 2;
    if (hash == pat_hash){
        for(i = 0; i < pat_len; i++){
            printf("%d ", pos_text + i - 1);
            if (buf[pos_buf - pat_len + i] != pat[i]) break;
        }
    }
    while (1){
        if (pos_buf == buf_size + pat_len) {
            readBuf(buf, pat_len);
            pos_buf = pat_len;
        }
        if (buf[pos_buf] == '\0') return;
        updateHash(&hash, p, buf[pos_buf - pat_len], buf[pos_buf]);
        if (hash == pat_hash){
            for(i = 0; i < pat_len; i++){
                printf("%d ", pos_text + i);
                if (buf[pos_buf - pat_len + i + 1] != pat[i]) break;
            }
        }
        pos_buf++;
        pos_text++;
    }
}

int main(){
    rabinKarp();
    return 0;
}
