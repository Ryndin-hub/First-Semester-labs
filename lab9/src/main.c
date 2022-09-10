#include <stdio.h>
#include <malloc.h>

void freeGraph(int **graph, long N){
    for (int i = 0; i < N; i++) free(graph[i]);
    free(graph);
}

int dijkstra(long N, int **graph, short S, short F){
    unsigned long vertexLen[N];
    short vertexInfLen[N];
    short vertexNeedCheck[N];
    short parent[N];
    short vertexPaths[N];
    short vertexInQueue[N];
    short queue[N];
    unsigned long queueBot = 0, queueTop = 1;
    for (int i = 0; i < N; i++){
        vertexNeedCheck[i] = 1;
        vertexInfLen[i] = 1;
        vertexPaths[i] = 0;
        vertexInQueue[i] = 0;
    }
    vertexInfLen[S] = 0;
    vertexLen[S] = 0;
    queue[0] = S;
    while (queueBot != queueTop) {
        short currentVertex = queue[queueBot++];
        vertexInQueue[currentVertex] = 0;
        for (short nextVertex = 0; nextVertex < N; nextVertex++){
            if (graph[currentVertex][nextVertex] != -1 && nextVertex != currentVertex){
                vertexPaths[nextVertex] += 1;
                if (vertexInfLen[nextVertex] == 1 || vertexLen[currentVertex] + graph[currentVertex][nextVertex] < vertexLen[nextVertex]) {
                    parent[nextVertex] = currentVertex;
                    vertexInfLen[nextVertex] = 0;
                    vertexLen[nextVertex] = vertexLen[currentVertex] + graph[currentVertex][nextVertex];
                    if (vertexLen[nextVertex] > 2147483648) vertexLen[nextVertex] = 2147483648;
                }
                if (vertexNeedCheck[nextVertex] == 1 && vertexInQueue[nextVertex] == 0) {
                    queue[queueTop++] = nextVertex;
                    vertexInQueue[nextVertex] = 1;
                }
            }
        }
        vertexNeedCheck[currentVertex] = 0;
    }
    for (int i = 0; i < N; i++) {
        if (vertexInfLen[i] == 1) printf("oo ");
        else if (vertexLen[i] == 2147483648) printf("INT_MAX+ ");
        else printf("%lu ", vertexLen[i]);
    }
    if (vertexInfLen[F] == 1) printf("\nno path");
    else if (vertexLen[F] == 2147483648 && vertexPaths[F] >= 2) printf("\noverflow");
    else {
        printf("\n%d ",F + 1);
        while (F != S){
            F = parent[F];
            printf("%d ",F + 1);
        }
    }
    return 0;
}

int main(void){
    short in,out,S,F;
    long N, M;
    unsigned long len;
    if(scanf("%li%hi%hi%li", &N, &S, &F, &M) != 4){
        printf("bad number of lines");
        return 1;
    }
    S--; F--;
    if (N < 0 || N > 5000){
        printf("bad number of vertices");
        return 1;
    }
    if (M < 0 || M > N*(N+1)/2){
        printf("bad number of edges");
        return 1;
    }
    if (N == 0) {
        printf("bad vertex");
        return 1;
    }
    int **graph = (int**) malloc(N * sizeof(int*));
    for (int i = 0; i < N; i++){
        graph[i] = (int*) malloc(N * sizeof(int));
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++) graph[i][j] = -1;
    }
    for (int i = 0; i < M; i++){
        if(scanf("%hi%hi%lu", &in, &out, &len) != 3){
            printf("bad number of lines");
            freeGraph(graph,N);
            return 1;
        }
        if(in < 1 || in > N || out < 1 || out > N){
            printf("bad vertex");
            freeGraph(graph,N);
            return 1;
        }
        if(len > 2147483647){
            printf("bad length");
            freeGraph(graph,N);
            return 1;
        }
        graph[in-1][out-1] = (int) len;
        graph[out-1][in-1] = (int) len;
    }
    dijkstra(N, graph, S, F);
    freeGraph(graph,N);
    return 0;
}
