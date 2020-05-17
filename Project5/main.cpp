#include <iostream>
#include <climits>
#include <queue>
#include "utils.h"
#include <ctime>

bool bfs(int** graph, int s, int t, int parent[], int n){
    bool visited[n];
    for(int i = 0 ; i<n;++i){
        visited[i] = false;
        parent[i] = -1;
    }
    std::queue <int> q;
    q.push(s);
    visited[s] = true;

    while (!q.empty()){
        int v = q.front();
        q.pop();

        for (int u=0; u<n; u++){
            if (!visited[u] && graph[v][u] > 0){
                q.push(u);
                parent[u] = v;
                visited[u] = true;
            }
        }
    }
    return (visited[t]);
}

int fordFulkerson(int** graph, int s, int t, int n){
    int u, v;
    int** rGraph = makeAdjacencyMatrix(n);
    int** flow = makeAdjacencyMatrix(n);
    for (v = 0; v < n; v++)
        for (u = 0; u < n; u++)
            rGraph[u][v] = graph[u][v];

    int parent[n];
    int result = 0;

    while (bfs(rGraph, s, t, parent, n)){

        int cf = INT_MAX;
        for (u=t; u!=s; u=parent[u])
        {
            v = parent[u];
            cf = std::min(cf, rGraph[v][u]);
        }

        for (u=t; u != s; u=parent[u])
        {

            v = parent[u];
            if(graph[v][u])
                flow[u][v] += cf;
            else
                flow[u][v] -= cf;


            rGraph[v][u] -= cf;
            rGraph[u][v] += cf;
        }
        result += cf;
    }
    endl(std::cout);
    std::cout<<"Residual network";
    printAdjacencyMatrix(rGraph,n);
//    printAdjacencyMatrix(flow, n);
    return result;
}

int whichL(int v, int* L){
    int sum = 0;
    for(int i = 0; i < v; i++){
        sum += L[i];
        if(sum >= v) return i;
    }
    return 0;
}

void makeFlowNetwork(int**& graph, int& v, int N){
    int i,j;

    //iloscia wierzcholkow dla kazdej warstwy;
    int L[N];
    //ilosc wierzcholkow w sieci
    v = 2;


    for(i = 0; i < N; i++){
        L[i] = ((int)rand()%(N - 1)) + 2;
        v += L[i];
    }

    graph = makeAdjacencyMatrix(v);

    //krawędzie wychodzące ze źródła
    for(i = 0; i < L[0]; i++)
        graph[0][i + 1] = 1;

    //krawedzie wchodzące do ujścia
    for(i = 0; i < L[N - 1]; i++)
        graph[v - 2 - i][v - 1] = 1;

    int d = 1;
    //krawedzie miedzy warstwami posrednimi
    for(j = 0; j < N - 1; j++){
        int max, min, flag;
        if( L[j] > L[j + 1] ){
            max = L[j];
            min = L[j + 1];
            flag = -1;
        }
        else if(L[j] < L[j + 1]){
            max = L[j + 1];
            min = L[j];
            flag = 1;
        }
        else{
            max = min = L[j];
            flag = 0;
        }
        for(i = 0; i < min; i++){

            graph[d + i][d + i + L[j]] = 1;
        }
        if(flag == 1){
            for(int k = 0; k < max - min; k++){
                int r = (int)rand() % L[j];
                graph[d + r][d + L[j] + min + k] = 1;
            }
        }
        else if(flag == -1){
            for(int k = 0; k < max - min; k++){
                int r = (int)rand() % L[j + 1];
                graph[d + min + k][d + max + r] = 1; // mozliwe ze nalezy zamienic max na L[i]
            }
        }
        d += max;
    }

    // losowanie dodatkowych łuków w sieci
    int v1, v2, l1, l2;
    for(i = 0; i < (2 * N); i++){
        do{
            v1 = (int)rand()%(v - 2) + 1;
            v2 = (int)rand()%(v - 2) + 1;
            l1 = whichL(v1, L);
            l2 = whichL(v2, L);
        }while(!(v1 != v2 && graph[v1][v2] == 0 && graph[v2][v1] == 0  && abs(l1 - l2) <=1 ));
        graph[v1][v2] = 1;
    }
    for(i = 0; i < v; i++){
        for(j = 0; j < v; j++){
            if(graph[i][j] == 1)
                graph[i][j] = (int)rand()%10 + 1;
        }
    }
}


int main(){

    srand(time(NULL));
    int N = 0;
    std::cout << "Set the number of layers (at least 2)" << std::endl;
    std:: cin >> N;
    if(N < 2)
        std::cout<<"Not enough layers";
        EXIT_FAILURE;
    int** graph = nullptr;
    int v = 0;

    makeFlowNetwork(graph, v, N);

    endl(std::cout);
    operator<<(std::cout,"Random flow network");
    printAdjacencyMatrix(graph, v);
    int maxFlow = fordFulkerson(graph, 0, v - 1, v);
    endl(std::cout);
    std::cout <<"Maximum flow: "<<maxFlow;

    return 0;
}