#include <stdio.h>
#include <stdlib.h>

struct Vertex{
    char color; //w,g,b
    short numOfConnections;
    short nextVertex[1000];
};

int topologicalSort(struct Vertex *vertex, int current, int *output, int *outputCurrent){
    if (vertex[current].color == 'b') return *outputCurrent;
    if (vertex[current].color == 'g') {
        printf("impossible to sort");
        exit(1);
    }
    if (vertex[current].color == 'w') vertex[current].color = 'g';
    for (int i = 0; i < vertex[current].numOfConnections; i++){
        topologicalSort(vertex, vertex[current].nextVertex[i], output, outputCurrent);
    }
    if (vertex[current].color != 'b') {
        *outputCurrent += 1;
        output[*outputCurrent] = current;
    }
    vertex[current].color = 'b';
    return *outputCurrent;
}

int main(void){
    int N,M,in,out,j = 0;
    if(scanf("%d%d", &N, &M) != 2){
        printf("bad number of lines");
        return 1;
    }
    if (N < 0 || N > 1000){
        printf("bad number of vertices");
        return 1;
    }
    if (M < 0 || M > N*(N+1)/2){
        printf("bad number of edges");
        return 1;
    }
    int output[N + 1];
    struct Vertex vertices[N + 1];
    for (int i = 1; i < N + 1; i++){
        vertices[i].color = 'w';
        vertices[i].numOfConnections = 0;
    }
    for (int i = 0; i < M; i++){
        if(scanf("%d%d", &in, &out) != 2){
            printf("bad number of lines");
            return 1;
        }
        if(in < 1 || in > N || out < 1 || out > N){
            printf("bad vertex");
            return 1;
        }
        vertices[in].nextVertex[vertices[in].numOfConnections] = out;
        vertices[in].numOfConnections++;
    }
    for (int i = 1; i < N + 1; i++){
        j = topologicalSort(vertices, i, output, &j);
    }
    for (int i = j; i > 0; i--){
        printf("%d ", output[i]);
    }
    return 0;
}
