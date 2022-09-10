#include <string.h>
#include <stdio.h>
#define buf_size 1024

void setShifts(int *shifts, unsigned char *txt, int len){
    int i;
    for (i = 0; i < 256; i++) shifts[i] = len;
    for (i = 0; i < len - 1; i++) shifts[txt[i]] = len - i - 1;
}

int readPat(unsigned char *pat){
    if (scanf("%16[^\n]s", pat) != 1) return 1;
    unsigned char tmp;
    if (scanf("%c", &tmp) != 1) return 1;
    return 0;
}

void setBuf(unsigned char *buf){
    int i;
    for (i = 0; i < buf_size + 17; i++) buf[i] = 0;
}

int readBuf(unsigned char *buf, int len){
    int i, err = 0;
    for (i = 0; i < len; i++) buf[i] = buf[buf_size + i];
    if (scanf("%1023[^EOF]s", &buf[len]) != 1){
        err = 1;
        buf[len] = 0;
    }
    if ((int) strlen((char*) &buf[len]) != buf_size - 1) buf[len + (int) strlen((char*) &buf[len])] = 0;
    else if(scanf("%c", &buf[len + (int) strlen((char*) &buf[len])]) == EOF) err = 1;
    return err;
}

void boyerMoore(){
    unsigned char pat[17], buf[buf_size+17];
    int i, pat_len, pos_buf = 0, pos_text = 1, shifts[256], shift = 0;
    if (readPat(pat) == 1) return;
    pat_len = strlen((char*) pat);
    setShifts(shifts, pat, pat_len);
    setBuf(buf);
    if(readBuf(buf, pat_len) == 2) return;
    if((int) strlen((char*) &buf[pat_len]) == 0) return;
    pos_buf = pat_len * 2;
    while (1){
        if (pos_buf >= buf_size + pat_len) {
            readBuf(buf, pat_len);
            pos_buf -= buf_size;
        }
        for (i = pos_buf - shift; i < pos_buf; i++){
            if (buf[i] == 0) return;
        }
        for (i = pat_len - 1; i >= 0; i--){
            printf("%d ", pos_text + i);
            if (buf[pos_buf + i - pat_len] != pat[i]) break;
        }
        shift = shifts[buf[pos_buf - 1]];
        pos_buf += shift;
        pos_text += shift;
    }
}

int main(){
    boyerMoore();
    return 0;
}
