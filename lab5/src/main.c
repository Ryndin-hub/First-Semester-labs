#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

FILE *fin, *fout;

struct code{
    bool bits[32];
    int len;
};

struct tree_vertex{
    bool is_end;
    unsigned char symbol;
    int count;
    struct tree_vertex *o;
    struct tree_vertex *l;
};

void quickSort(int a, int b, struct tree_vertex *arr[256]){
    struct tree_vertex *tmp;
    int c = arr[(a+b) / 2]->count;
    int i = a;
    int j = b;
    do {
        while (arr[i]->count > c) i++;
        while (arr[j]->count < c) j--;
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

void freeTree(struct tree_vertex *tree){
    if(tree->is_end == 0) {
        freeTree(tree->o);
        freeTree(tree->l);
    }
    free(tree);
}

bool readBit(bool is_end){
    static unsigned char input;
    static int i = 0;
    if (is_end == 1) i = 1;
    if (i == 0){
        if (fscanf(fin,"%c",&input) != 1) return 1;
        i = 8;
    }
    i--;
    return input >> i & 1;
}

void writeBit(bool a, bool is_end){
    static unsigned char output = 0;
    static int i = 0;
    if (is_end == 1){
        for (;i<8;i++) output = output << 1;
        fprintf(fout,"%c",output);
        output = 0;
        i = 0;
        return;
    }
    if (i == 8){
        fprintf(fout,"%c",output);
        output = 0;
        i = 0;
    }
    output = output << 1;
    if (a == 1) output++;
    i++;
}

void createCodesRec(struct tree_vertex *tree, struct code code, struct code *codes){
    if (tree->is_end == 1){
        if (code.len == 0){
            code.len = 1;
            code.bits[0] = 0;
        }
        codes[(int) tree->symbol] = code;
        return;
    }
    code.len++;
    code.bits[code.len-1] = 0;
    createCodesRec(tree->o, code, codes);
    code.bits[code.len-1] = 1;
    createCodesRec(tree->l, code, codes);
}

struct code *createCodes(struct tree_vertex *tree){
    static struct code codes[256], code;
    code.len = 0;
    for (int i = 0; i < 256; i++) codes[i].len = 0;
    createCodesRec(tree, code, codes);
    return codes;
}

void zipTreePhase1(struct tree_vertex *tree){//рекурсивный проход по дереву, если
    if (tree->is_end == 1){                  //вершина имеет ветки -> печатает бит 0
        writeBit(1,0);                       //если вершина без веток -> печатает бит 1
        return;                              //например 01011 это дерево x
    }                                        //                         / \              %
    writeBit(0,0);                           //                        0   1
    zipTreePhase1(tree->o);                  //                           / \            %
    zipTreePhase1(tree->l);                  //                          0   1
}

void zipTreePhase2(struct tree_vertex *tree){//рекурсивный проход по дереву
    if (tree->is_end == 1){                  //печатает все символы на концах дерева которые встречает
        fprintf(fout,"%c",tree->symbol);
        return;
    }
    zipTreePhase2(tree->o);
    zipTreePhase2(tree->l);
}

void zipTree(struct tree_vertex *tree){
    zipTreePhase1(tree);
    writeBit(0,1);//дописывает нули чтобы получился байт
    zipTreePhase2(tree);//например код 01100000ab кодирует дерево с двумя ветками
}                       //левая вершина с символом 'a' , првавая с символом 'b'

void unzipTreePhase1(struct tree_vertex *tree){
    if (readBit(0) == 0){
        tree->is_end = 0;
        tree->o = (struct tree_vertex*)malloc(sizeof(struct tree_vertex));
        tree->l = (struct tree_vertex*)malloc(sizeof(struct tree_vertex));
        unzipTreePhase1(tree->o);
        unzipTreePhase1(tree->l);
    }
    else{
        tree->is_end = 1;
    }
}

void unzipTreePhase2(struct tree_vertex *tree){
    if (tree->is_end == 1){
        if (fscanf(fin,"%c",&tree->symbol) != 1) return;
        return;
    }
    unzipTreePhase2(tree->o);
    unzipTreePhase2(tree->l);
}

struct tree_vertex *unzipTree(){
    struct tree_vertex *tree = (struct tree_vertex*)malloc(sizeof(struct tree_vertex));
    unzipTreePhase1(tree);
    readBit(1);
    unzipTreePhase2(tree);
    return tree;
}

void zipLen(unsigned int count){
    for (int i = 31; i >= 0; i--) writeBit(count>>i&1,0);
}

int unzipLen(){
    int count = 0;
    for (int i = 31; i >= 0; i--) count = (count << 1) + readBit(0);
    return count;
}

void unzipTxt(struct tree_vertex *tree, int len){
    struct tree_vertex *tree_start = tree;
    int count = 0;
    while (count < len) {
        if (tree->is_end == 1){
            fprintf(fout,"%c",tree->symbol);
            count++;
            tree = tree_start;
        }
        else if (readBit(0) == 0) {
            tree = tree->o;
        } else {
            tree = tree->l;
        }
    }
}

void zipTxt(struct code *codes){
    unsigned char input;
    fseek(fin,3,SEEK_SET);
    while (fscanf(fin,"%c",&input) == 1){
        for (int j = 0; j < codes[(int) input].len; j++){
            writeBit(codes[(int) input].bits[j],0);
        }
    }
    writeBit(0,1);
}

struct tree_vertex *buildTree(){
    struct tree_vertex *symbols[256];
    for (int i = 0; i < 256; i++) symbols[i] = (struct tree_vertex*)malloc(sizeof(struct tree_vertex));
    unsigned char input;
    unsigned int count = 0;
    for (int i = 0; i < 256; i++){
        symbols[i]->is_end = 1;
        symbols[i]->symbol = (unsigned char) i;
        symbols[i]->count = 0;
    }
    while (fscanf(fin,"%c",&input) == 1){
        symbols[(int) input]->count++;
        count++;
    }
    zipLen(count);
    quickSort(0,255,symbols);
    int symbols_not_in_tree = 0;
    while (symbols_not_in_tree < 256 && symbols[symbols_not_in_tree]->count != 0) symbols_not_in_tree++;
    symbols_not_in_tree--;
    while (symbols_not_in_tree != 0){
        struct tree_vertex *tmp = (struct tree_vertex*)malloc(sizeof(struct tree_vertex));
        *tmp = *symbols[symbols_not_in_tree-1];
        symbols[symbols_not_in_tree-1]->o = tmp;
        symbols[symbols_not_in_tree-1]->l = symbols[symbols_not_in_tree];
        symbols[symbols_not_in_tree-1]->is_end = 0;
        symbols[symbols_not_in_tree-1]->count = tmp->count + symbols[symbols_not_in_tree]->count;
        quickSort(0,symbols_not_in_tree-1,symbols);
        symbols_not_in_tree--;
    }
    for (int i = 0; i < 256; i++) if (symbols[i]->count == 0) free(symbols[i]);
    return symbols[0];
}

int main(void) {
    fin = fopen("in.txt", "rb");
    fout = fopen("out.txt", "wb");
    unsigned char switcher;
    if (fscanf(fin,"%c",&switcher) != 1){
        fclose(fin);
        fclose(fout);
        return 1;
    }
    fseek(fin,3,SEEK_SET);
    unsigned char tmp;
    if (fscanf(fin,"%c",&tmp) != 1){
        fclose(fin);
        fclose(fout);
        return 0;
    }
    fseek(fin,3,SEEK_SET);
    if (switcher == 'c'){
        struct tree_vertex *tree = buildTree();
        struct code *codes = createCodes(tree);
        zipTree(tree);
        zipTxt(codes);
        freeTree(tree);
    }
    if (switcher == 'd'){
        int len = unzipLen();
        struct tree_vertex *tree = unzipTree();
        unzipTxt(tree,len);
        freeTree(tree);
    }
    fclose(fin);
    fclose(fout);
    return 0;
}
