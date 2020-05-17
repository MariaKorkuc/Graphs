#include <iostream>
#include <climits>
#include <queue>
#include "utils.h"

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
    printAdjacencyMatrix(rGraph,n);
    printAdjacencyMatrix(flow, n);
    return result;
}


int main(){

    int n = 6;
    int** graph = makeAdjacencyMatrix(6);
    graph[0][1] = 10;
    graph[0][2] = 9;
    graph[1][2] = 6;
    graph[1][3] = 5;
    graph[2][4] = 8;
    graph[3][5] = 9;
    graph[4][1] = 4;
    graph[4][3] = 2;
    graph[4][5] = 7;
//    printAdjacencyMatrix(graph, n);
    std::cout << fordFulkerson(graph, 0, 5, n);

    return 0;
} 