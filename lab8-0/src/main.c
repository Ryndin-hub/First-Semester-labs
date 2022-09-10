#include <stdio.h>
#include <malloc.h>

struct Edge{
    unsigned long len;
    short in;
    short out;
};

void quickSort(long a, long b, struct Edge *edge){
    unsigned long c = edge[(a+b) / 2].len;
    long i = a;
    long j = b;
    do {
        while (edge[i].len < c) i++;
        while (edge[j].len > c) j--;
        if (i <= j){
            struct Edge tmp = edge[i];
            edge[i] = edge[j];
            edge[j] = tmp;
            i++;
            j--;
        }
    } while (i <= j);
    if (j > a) quickSort(a,j,edge);
    if (i < b) quickSort(i,b,edge);
}


int kruskal(struct Edge *edge, short *output, long N, long M){
    short vertexGroup[N+1];
    short numOfGroups = 0;
    for (int i = 1; i < N+1; i++){
        vertexGroup[i] = 0;
    }
    int outputCurrent = 0;
    for (int i = 0; i < M; i++){
        if (vertexGroup[edge[i].in] == 0 && vertexGroup[edge[i].out] == 0){
            numOfGroups += 1;
            vertexGroup[edge[i].in] = numOfGroups;
            vertexGroup[edge[i].out] = numOfGroups;
            output[outputCurrent] = edge[i].in;
            outputCurrent += 1;
            output[outputCurrent] = edge[i].out;
            outputCurrent += 1;
        } else if (vertexGroup[edge[i].in] != 0 && vertexGroup[edge[i].out] == 0){
            vertexGroup[edge[i].out] = vertexGroup[edge[i].in];
            output[outputCurrent] = edge[i].in;
            outputCurrent += 1;
            output[outputCurrent] = edge[i].out;
            outputCurrent += 1;
        } else if (vertexGroup[edge[i].in] == 0 && vertexGroup[edge[i].out] != 0){
            vertexGroup[edge[i].in] = vertexGroup[edge[i].out];
            output[outputCurrent] = edge[i].in;
            outputCurrent += 1;
            output[outputCurrent] = edge[i].out;
            outputCurrent += 1;
        } else if (vertexGroup[edge[i].in] != 0 && vertexGroup[edge[i].out] != 0 && vertexGroup[edge[i].in] != vertexGroup[edge[i].out]){
            short tmp = vertexGroup[edge[i].out];
            for (int j = 1; j < N+1; j++){
                if (vertexGroup[j] == tmp) vertexGroup[j] = vertexGroup[edge[i].in];
            }
            output[outputCurrent] = edge[i].in;
            outputCurrent += 1;
            output[outputCurrent] = edge[i].out;
            outputCurrent += 1;
        }
    }
    if (N == 1) return 0;
    for (int i = 1; i < N+1; i++){
        if (vertexGroup[i] == 0) return -1;
    }
    return outputCurrent;
}

int main(void){
    short in,out;
    long N, M;
    int outputlen;
    unsigned long len;
    if(scanf("%li%li", &N, &M) != 2){
        printf("bad number of lines");
        return 1;
    }
    if (N < 0 || N > 5000){
        printf("bad number of vertices");
        return 1;
    }
    if (M < 0 || M > N*(N+1)/2){
        printf("bad number of edges");
        return 1;
    }
    if (N == 0) {
        printf("no spanning tree");
        return 1;
    }
    short *output = malloc(2 * M * sizeof(short));
    //short output[M*2+2];
    struct Edge *edges = malloc(M * sizeof(struct Edge));
    //struct Edge edges[M+1];
    for (int i = 0; i < M; i++){
        if(scanf("%hi%hi%lu", &in, &out, &len) != 3){
            printf("bad number of lines");
            free(output);
            free(edges);
            return 1;
        }
        if(in < 1 || in > N || out < 1 || out > N){
            printf("bad vertex");
            free(output);
            free(edges);
            return 1;
        }
        if(len > 2147483647){
            printf("bad length");
            free(output);
            free(edges);
            return 1;
        }
        edges[i].in = in;
        edges[i].out = out;
        edges[i].len = len;
    }
    if (M > 0) quickSort(0,M-1,edges);
    outputlen = kruskal(edges, output, N, M);
    if (outputlen == -1) {
        printf("no spanning tree");
        free(output);
        free(edges);
        return 1;
    }
    for (int i = 0; i < outputlen; i+=2){
        printf("%hi %hi\n", output[i], output[i+1]);
    }
    free(output);
    free(edges);
    return 0;
}
